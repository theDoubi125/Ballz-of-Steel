#ifndef EVENT_HANDLER_H_INCLUDED
#define EVENT_HANDLER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../math/vec.h"

class EventHandler
{
    public:
    EventHandler(sf::RenderWindow &app);
    ~EventHandler();

    void updateEvents();
    bool keyPressed(int key) const;
    bool keyReleased(int key) const;
    bool keyDown(int key) const;
    bool keyUp(int key) const;
    bool buttonPressed(int button) const;
    bool buttonReleased(int button) const;
    bool buttonDown(int button) const;
    bool buttonUp(int button) const;

    bool isJoystickConnected(int joystick) const;
    bool buttonPressed(int joystick, int button) const;
    bool buttonReleased(int joystick, int button) const;
    bool buttonDown(int joystick, int button) const;
    bool buttonUp(int joystick, int button) const;
    float joystickPosition(int joystick, int axis) const;

    bool closed() const;
    int xMouse() const;
    int yMouse() const;
    Vec mousePos() const;
    int mouseWheel() const;

    private:
    sf::RenderWindow &m_app;
    int *m_keys, *m_buttons, *m_joystickButtons;
    float *m_joystickAxes;
    int m_time, m_xMouse, m_yMouse, m_mouseWheel;
    bool m_quit;
};

#endif // EVENT_HANDLER_H_INCLUDED
