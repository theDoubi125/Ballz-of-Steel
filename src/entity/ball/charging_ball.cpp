#include <SFML/Graphics.hpp>
#include <cmath>

#include "../ball.h"
#include "charging_ball.h"
#include "../../world/world.h"

ChargingBall::ChargingBall(Player &Player, Vec pos, double r, double m, Vec speed, int chargingTime, int maxHealth) : Ball(Player, pos, r, m, speed, maxHealth), m_movingTime(0), m_chargingTime(chargingTime)
{

}

sf::Color ChargingBall::getColor() const
{
    sf::Color col = Ball::getColor();
    double ratio = std::min(1.0, (double)m_movingTime/m_chargingTime);
    col.r = Ball::getColor().r*(1-ratio)+m_chargingCol.r*ratio;
    col.g = Ball::getColor().g*(1-ratio)+m_chargingCol.g*ratio;
    col.b = Ball::getColor().b*(1-ratio)+m_chargingCol.b*ratio;
    col.a = Ball::getColor().a*(1-ratio)+m_chargingCol.a*ratio;
    return col;
}

sf::Color ChargingBall::getSelectedColor() const
{
    sf::Color col = Ball::getSelectedColor();
    double ratio = std::min(1.0, (double)m_movingTime/m_chargingTime);
    col.r = Ball::getSelectedColor().r*(1-ratio)+m_selectedChargingCol.r*ratio;
    col.g = Ball::getSelectedColor().g*(1-ratio)+m_selectedChargingCol.g*ratio;
    col.b = Ball::getSelectedColor().b*(1-ratio)+m_selectedChargingCol.b*ratio;
    col.a = Ball::getSelectedColor().a*(1-ratio)+m_selectedChargingCol.a*ratio;
    return col;
}

void ChargingBall::updateBall()
{
    if(m_movingTime > m_chargingTime)
    {
        m_movingTime = m_chargingTime;
        mulSpeed(1.03);
    }
    if(isMoving() && getSpeed().normSquared() > 20)
    {
        m_movingTime++;
    }
    else
    {
        if(m_movingTime > 0)
            m_movingTime -= 2;
        if(m_movingTime < 0)
            m_movingTime = 0;
    }
}


void ChargingBall::throwBall(Vec pos, Vec dir)
{
    setPos(pos);
    setSpeed(dir.getVectWithNorm(20));
    m_movingTime = m_chargingTime;
}
