#ifndef MOVEMENT_MANAGER_H_INCLUDED
#define MOVEMENT_MANAGER_H_INCLUDED

#include "../math/vec.h"
class Ball;
class PlayerController;

class MovementHandler
{
public:
    MovementHandler(std::vector<Ball*> m_balls, const PlayerController &event);
    virtual ~MovementHandler();
    void stopMovement(Ball *ball);
    virtual void update();
    virtual bool isOver() const;
    void updateTarget(Ball *ball, Vec target);

protected:
    std::vector<Ball*> m_balls;
    Vec m_target;
    int m_endTime;
    bool m_isOver, m_ctrl;
};

class MovementManager
{
public:
    MovementManager();
    virtual ~MovementManager();

    virtual void update();
    void addMovement(MovementHandler *handler);
    void stopMovement(Ball* ball);
    void updateTarget(Ball *ball, Vec target);

private:
    std::vector<MovementHandler*> m_handlers;
    Vec *m_lastPos;
};
#include "ball.h"

#endif // MOVEMENT_MANAGER_H_INCLUDED
