#include <SDL2/SDL.h>
#include "player_controller.h"
#include "../graphic/counter.h"
#include "../graphic/util.h"

PlayerController::PlayerController(const EventHandler &event, Vec worldDim, Vec initViewCenter) :
    m_mousePos(0, 0),
    m_speed(1),
    m_event(event),
    m_screenDim(Vec(100000, 100000)),
    m_viewCenter(initViewCenter),
    m_worldDim(worldDim),
    m_zoom(1)
{

}

PlayerController::~PlayerController()
{

}

void PlayerController::update()
{
    if(m_mousePos.x < 0)
    {
        m_mousePos.x = 0;
        m_viewCenter.x -= 5;
    }
    if(m_mousePos.y < 0)
    {
        m_mousePos.y = 0;
        m_viewCenter.y -= 5;
    }
    if(m_mousePos.x > m_screenDim.x)
    {
        m_mousePos.x = m_screenDim.x;
        m_viewCenter.x += 5;
    }
    if(m_mousePos.y > m_screenDim.y)
    {
        m_mousePos.y = m_screenDim.y;
        m_viewCenter.y += 5;
    }
}

Vec PlayerController::mousePos() const
{
    return m_mousePos;
}

void PlayerController::setMousePos(Vec pos)
{
    m_mousePos = pos;
}

void PlayerController::setSpeed(double speed)
{
    m_speed = speed;
}

void PlayerController::setScreenDim(Vec dim)
{
    m_screenDim = dim;
}

Vec PlayerController::getScreenDim() const
{
    return m_screenDim;
}

Vec PlayerController::getViewCenter() const
{
    return m_viewCenter;
}

int PlayerController::getZoom() const
{
    return m_zoom;
}

MousePlayerController::MousePlayerController(const EventHandler &event, Vec worldDim, Vec initViewCenter) : PlayerController(event, worldDim, initViewCenter)
{

}

MousePlayerController::~MousePlayerController()
{

}

void MousePlayerController::update()
{
    m_mousePos += (m_event.mousePos()-m_lastMousePos)*m_speed;
    m_lastMousePos = m_event.mousePos();
    PlayerController::update();
}

bool MousePlayerController::pressed(int button) const
{
    if(button == SELECT)
        return m_event.buttonPressed(0);
    if(button == ORDER)
        return m_event.buttonPressed(1);
    return false;
}

bool MousePlayerController::down(int button) const
{
    if(button == SELECT)
        return m_event.buttonDown(0);
    if(button == ORDER)
        return m_event.buttonDown(1);
    return false;
}

bool MousePlayerController::released(int button) const
{
    if(button == SELECT)
        return m_event.buttonReleased(0);
    if(button == ORDER)
        return m_event.buttonReleased(1);
    return false;
}

KeyboardPlayerController::KeyboardPlayerController(const EventHandler &event, int *keys, Vec worldDim, Vec initViewCenter)
    : PlayerController(event, worldDim, initViewCenter), m_keys(keys)
{

}

KeyboardPlayerController::~KeyboardPlayerController()
{
    delete[] m_keys;
}

void KeyboardPlayerController::update()
{
    if(down(RIGHT))
        m_mousePos += Vec(m_speed, 0);
    if(down(LEFT))
        m_mousePos -= Vec(m_speed, 0);
    if(down(UP))
        m_mousePos -= Vec(0, m_speed);
    if(down(DOWN))
        m_mousePos += Vec(0, m_speed);
    if(pressed(ZOOM))
        m_zoom++;
    if(pressed(DEZOOM))
        m_zoom--;
    if(m_zoom < 0)
        m_zoom = 0;
    if(m_zoom > 3)
        m_zoom = 3;
    PlayerController::update();
}

bool KeyboardPlayerController::pressed(int button) const
{
    return m_event.keyPressed(m_keys[button]);
}

bool KeyboardPlayerController::down(int button) const
{
    return m_event.keyDown(m_keys[button]);
}

bool KeyboardPlayerController::released(int button) const
{
    return m_event.keyReleased(m_keys[button]);
}

JoypadPlayerController::JoypadPlayerController(const EventHandler &event, int id, Vec worldDim, Vec initViewCenter) : PlayerController(event, worldDim, initViewCenter), m_id(id)
{

}

JoypadPlayerController::~JoypadPlayerController()
{

}

void JoypadPlayerController::update()
{
    m_mousePos += Vec(abs(m_event.joystickPosition(0, 0))>10?m_event.joystickPosition(0, 0):0, abs(m_event.joystickPosition(0, 1))>10?m_event.joystickPosition(0, 1):0)*m_speed;
    Displayer::instance.addValue(Vec(0, 200), "joypos", draw::to_string(m_event.joystickPosition(0, 0))+", "+draw::to_string(draw::to_string(m_event.joystickPosition(0, 1))));
    PlayerController::update();
}

bool JoypadPlayerController::pressed(int button) const
{
    return m_event.buttonPressed(m_id, button);
}

bool JoypadPlayerController::down(int button) const
{
    return m_event.buttonDown(m_id, button);
}

bool JoypadPlayerController::released(int button) const
{
    return m_event.buttonReleased(m_id, button);
}
