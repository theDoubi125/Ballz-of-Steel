#include <SDL2/SDL.h>
#include "event_handler.h"

EventHandler::EventHandler(sf::RenderWindow &app) : m_app(app)
{
    m_keys = new int[SDL_NUM_SCANCODES];
    for(int i=0; i<SDL_NUM_SCANCODES; i++)
        m_keys[i] = -1;
    m_buttons = new int[4];
    for(int i=0; i<4; i++)
        m_buttons[i] = -1;
    m_time = 1;
    m_quit = false;

    m_joystickButtons = new int[32*8];
    for(int i=0; i<32*8; i++)
        m_joystickButtons[i] = -1;
    m_joystickAxes = new float[8*8];
}

EventHandler::~EventHandler()
{
    delete[] m_keys;
    delete[] m_buttons;
    delete[] m_joystickButtons;
    delete[] m_joystickAxes;
}

void EventHandler::updateEvents()
{
    m_time++;
    sf::Event event;
    m_mouseWheel = 0;
    while(m_app.pollEvent(event))
    {
        if(event.type == sf::Event::KeyPressed && m_keys[event.key.code] < 0)
            m_keys[event.key.code] = m_time;
        else if(event.type == sf::Event::KeyReleased)
            m_keys[event.key.code] = -m_time;
        else if(event.type == sf::Event::Closed)
            m_quit = true;
        else if(event.type == sf::Event::MouseButtonPressed && m_buttons[event.mouseButton.button] < 0)
            m_buttons[event.mouseButton.button] = m_time;
        else if(event.type == sf::Event::MouseButtonReleased)
            m_buttons[event.mouseButton.button] = -m_time;
		else if(event.type == sf::Event::MouseMoved)
		{
			m_xMouse = event.mouseMove.x;
			m_yMouse = event.mouseMove.y;
		}
		else if(event.type == sf::Event::MouseWheelMoved)
        {
            m_mouseWheel += event.mouseWheel.delta;
        }
        else if(event.type == sf::Event::JoystickButtonPressed)
        {
            m_joystickButtons[event.joystickButton.joystickId*32+event.joystickButton.button] = m_time;
        }
        else if(event.type == sf::Event::JoystickButtonReleased)
        {
            m_joystickButtons[event.joystickButton.joystickId*32+event.joystickButton.button] = -m_time;
        }
        else if(event.type == sf::Event::JoystickMoved)
        {
            m_joystickAxes[event.joystickMove.joystickId*8+event.joystickMove.axis] = event.joystickMove.position;
        }
    }
}

bool EventHandler::keyDown(int key) const
{
    return m_keys[key] >= 0;
}

bool EventHandler::keyUp(int key) const
{
    return m_keys[key] < 0;
}

bool EventHandler::keyPressed(int key) const
{
    return m_keys[key] == m_time;
}

bool EventHandler::keyReleased(int key) const
{
    return m_keys[key] == -m_time;
}

bool EventHandler::closed() const
{
    return m_quit;
}

bool EventHandler::buttonPressed(int button) const
{
    return m_buttons[button] == m_time;
}

bool EventHandler::buttonReleased(int button) const
{
    return m_buttons[button] == -m_time;
}

bool EventHandler::buttonDown(int button) const
{
    return m_buttons[button] >= 0;
}

bool EventHandler::buttonUp(int button) const
{
    return m_buttons[button] < 0;
}

int EventHandler::xMouse() const
{
    return m_xMouse;
}

int EventHandler::yMouse() const
{
    return m_yMouse;
}

Vec EventHandler::mousePos() const
{
    return Vec(m_xMouse, m_yMouse);
}

int EventHandler::mouseWheel() const
{
    return m_mouseWheel;
}

bool EventHandler::isJoystickConnected(int joystick) const
{
    return sf::Joystick::isConnected(joystick);
}

bool EventHandler::buttonPressed(int joystick, int button) const
{
    return m_joystickButtons[joystick*32+button] == m_time;
}

bool EventHandler::buttonReleased(int joystick, int button) const
{
    return m_joystickButtons[joystick*32+button] == -m_time;
}

bool EventHandler::buttonDown(int joystick, int button) const
{
    return m_joystickButtons[joystick*32+button] >= 0;
}

bool EventHandler::buttonUp(int joystick, int button) const
{
    return m_joystickButtons[joystick*32+button] < 0;
}

float EventHandler::joystickPosition(int joystick, int axis) const
{
    return m_joystickAxes[joystick*8+axis];
}
