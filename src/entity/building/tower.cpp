#include <SFML/Graphics.hpp>

#include "tower.h"
#include "../../world/world.h"

Tower::Tower(Player &Player, Vec pos, double r, int capacity, int shootRate, int maxHealth) : RoundBuilding(Player, pos, r, maxHealth), m_capacity(capacity), m_stock(), m_shape(), m_shootRate(shootRate), m_timeShot(shootRate)
{
    m_shape.setRadius(r);
    m_shape.setPosition(x-r, y-r);
    m_shape.setOutlineColor(Player.getBaseColor());
    m_shape.setOutlineThickness(1);
    m_shape.setFillColor(sf::Color::Transparent);
}

Tower::~Tower()
{
    for(int i=0; i<m_stock.size(); i++)
        delete m_stock[i];
}

void Tower::handleInteraction(Entity *other)
{
    if(other->getType() == BALL)
    {
        Ball* ball = (Ball*)other;
        if(dist(*ball, *this) < (r()-ball->r()) && (*ball-*this)*ball->getSpeed() <= 0)
        {
            ball->update();
            ball->stopMoving();
            m_stock.push_back(ball);
            ball->getWorld()->remove(ball);
        }
    }
}

void Tower::receiveOrder(const PlayerController &event)
{
    /*if(event.buttonDown(1) && m_timeShot >= m_shootRate)
    {
        if(m_stock.size() > 0)
        {
            m_stock[0]->throwBall(getPos()+(event.mousePos().screenToWorld() - *this).getVectWithNorm(1), event.mousePos().screenToWorld() - *this);
            getWorld()->addEntity(m_stock[0]);
            m_stock.erase(m_stock.begin());
            m_timeShot = 0;
        }
    }*/
}

void Tower::draw(sf::RenderTarget &render)
{
    m_shape.setPosition(x-r(), y-r());
    m_shape.setOutlineColor(sf::Color::Blue);
    render.draw(m_shape);
}

void Tower::update()
{
    m_timeShot++;
}

bool Tower::colRect(Vec A, Vec B) const
{
    double minX = std::min(A.x, B.x);
    double minY = std::min(A.y, B.y);
    double maxX = std::max(A.x, B.x);
    double maxY = std::max(A.y, B.y);
    return (x > minX && x < maxX && (y + r() > minY && y - r() < maxY))
            || (y > minY && y < maxY && (x + r() > minX && x - r() < maxX))
            || distSquared(getPos(), A) < r()*r()
            || distSquared(getPos(), B) < r()*r()
            || distSquared(getPos(), Vec(A.x, B.y)) < r()*r()
            || distSquared(getPos(), Vec(B.x, A.y)) < r()*r();
}

bool Tower::isInside(Vec vec) const
{
    return distSquared(getPos(), vec) < r()*r();
}
