#ifndef PLAYER_CONTROLLER_H_INCLUDED
#define PLAYER_CONTROLLER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "event_handler.h"
#include "../math/vec.h"

enum KEY
{
    SELECT, ORDER, UP, DOWN, LEFT, RIGHT, ZOOM, DEZOOM
};

class PlayerController
{
    public:
    PlayerController(const EventHandler &event, Vec worldDim, Vec initViewCenter);
    virtual ~PlayerController();

    virtual void update();
    virtual bool pressed(int button) const = 0;
    virtual bool down(int button) const = 0;
    virtual bool released(int button) const = 0;
    Vec mousePos() const;
    void setMousePos(Vec pos);
    void setSpeed(double speed);
    void setScreenDim(Vec dim);
    Vec getScreenDim() const;
    Vec getViewCenter() const;
    int getZoom() const;

    protected:
    Vec m_mousePos, m_viewCenter;
    int m_zoom;
    Vec m_screenDim, m_worldDim;
    double m_speed;
    const EventHandler &m_event;
};

class MousePlayerController : public PlayerController
{
public:
    MousePlayerController(const EventHandler &event, Vec worldDim, Vec initViewCenter);
    virtual ~MousePlayerController();

    virtual void update();
    virtual bool pressed(int button) const;
    virtual bool down(int button) const;
    virtual bool released(int button) const;

private:
    Vec m_lastMousePos;
};

class KeyboardPlayerController : public PlayerController
{
    public:
    KeyboardPlayerController(const EventHandler &event, int* keys, Vec worldDim, Vec initViewCenter);
    virtual ~KeyboardPlayerController();

    virtual void update();
    virtual bool pressed(int button) const;
    virtual bool down(int button) const;
    virtual bool released(int button) const;

private:
    int *m_keys;
};

class JoypadPlayerController : public PlayerController
{
public:
    JoypadPlayerController(const EventHandler &event, int id, Vec worldDim, Vec initViewCenter);
    virtual ~JoypadPlayerController();

    virtual void update();
    virtual bool pressed(int button) const;
    virtual bool down(int button) const;
    virtual bool released(int button) const;

private:
    int m_id;
};

#endif // PLAYER_CONTROLLER_H_INCLUDED
