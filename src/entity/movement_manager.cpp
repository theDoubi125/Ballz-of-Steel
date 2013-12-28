#include <SFML/Graphics.hpp>

#include "movement_manager.h"

MovementHandler::MovementHandler(std::vector<Ball*> balls, const PlayerController &controller) : m_balls(balls), m_target(controller.mousePos()), m_isOver(false), m_endTime(0), m_ctrl(false)
{
    for(int i=0; i<m_balls.size(); i++)
        m_balls[i]->setMovement(this);
}

MovementHandler::~MovementHandler()
{
    for(int i=0; i<m_balls.size(); i++)
        m_balls[i]->stopMovement();
}

bool MovementHandler::isOver() const
{
    return m_balls.size() == 0 || m_isOver;
}

void MovementHandler::update()
{
    if(m_balls.size() == 0)
        return;
    Vec bary = Vec(0, 0);
    double medR = 0;
    for(int i=0; i<m_balls.size(); i++)
    {
        if(!m_ctrl)
            m_balls[i]->applyOrder(m_target);
        bary += *m_balls[i];
        medR += m_balls[i]->r();
    }
    if(m_ctrl)
    {
        for(int i=0; i<m_balls.size(); i++)
            m_balls[i]->applyOrder(m_target+*m_balls[i]-bary/m_balls.size());
    }
    if(!m_isOver && dist(bary/m_balls.size(), m_target) < medR/m_balls.size())
        m_isOver = true;

}

void MovementHandler::stopMovement(Ball* ball)
{
    ball->stopMovement();
    for(std::vector<Ball*>::iterator it = m_balls.begin(); it<m_balls.end(); it++)
    {
        if(*it == ball)
        {
            m_balls.erase(it);
            return;
        }
    }
}

void MovementHandler::updateTarget(Ball *ball, Vec target)
{
    for(int i=0; i<m_balls.size(); i++)
    {
        if(ball == m_balls[i])
        {
            m_target = target;
            return;
        }
    }
}

MovementManager::MovementManager()
{

}

MovementManager::~MovementManager()
{
    for(int i=0; i<m_handlers.size(); i++)
        delete m_handlers[i];
}

void MovementManager::addMovement(MovementHandler *handler)
{
    m_handlers.push_back(handler);
}

void MovementManager::stopMovement(Ball *ball)
{
    for(int i=0; i<m_handlers.size(); i++)
        m_handlers[i]->stopMovement(ball);
}

void MovementManager::update()
{
    for(std::vector<MovementHandler*>::iterator it = m_handlers.begin(); it<m_handlers.end(); it++)
    {
        (*it)->update();
        if((*it)->isOver())
        {
            delete *it;
            m_handlers.erase(it);
        }
    }
}

void MovementManager::updateTarget(Ball *ball, Vec target)
{
    for(int i=0; i<m_handlers.size(); i++)
        m_handlers[i]->updateTarget(ball, target);
}
