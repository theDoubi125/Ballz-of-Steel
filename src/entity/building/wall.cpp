#include <SFML/Graphics.hpp>

#include "wall.h"
#include "../../world/world.h"

Wall::Wall(Player &Player, Vec A, Vec B, double thickness, int maxHealth) : Building(Player, (A+B)/2, maxHealth), m_A(A), m_B(B), m_thickness(thickness)
{
    m_shape.setSize(sf::Vector2f(dist(A, B), thickness));
    m_shape.setFillColor(sf::Color::Black);

    m_shape.setPosition(A);
    m_shape.setOrigin(0, thickness/2);
    m_cornerA.setRadius(m_thickness/2);
    m_cornerB.setRadius(m_thickness/2);
    m_cornerA.setPosition(A-Vec(thickness/2, thickness/2));
    m_cornerB.setPosition(B-Vec(thickness/2, thickness/2));
    m_cornerA.setFillColor(sf::Color::Black);
    m_cornerB.setFillColor(sf::Color::Black);
}

void Wall::handleInteraction(Entity *entity)
{
    if(entity->getType() != BALL)
        return;
    Ball* ball = (Ball*)entity;
    Vec ortho = (m_B-m_A).ortho();
    if((*ball-m_A)*ortho<0)
        ortho*=-1;
    if((*ball-m_A).proj(ortho).normSquared() < (ball->r()+m_thickness/2)*(ball->r()+m_thickness/2) && (*ball-m_A)*(m_B-m_A) > 0 && (*ball-m_B)*(m_A-m_B) > 0)
    {
        ball->bounce(ortho);
        ball->setPos(m_A+(*ball-m_A).proj(m_B-m_A) + ortho.getVectWithNorm(ball->r()+m_thickness/2));
    }
    else if((*ball-m_A).normSquared() < (ball->r()+m_thickness/2)*(ball->r()+m_thickness/2))
    {
        ball->bounce(m_A-*ball);
        ball->setPos(m_A+(*ball-m_A).getVectWithNorm(ball->r()+m_thickness/2));
    }
    else if((*ball-m_B).normSquared() < (ball->r()+m_thickness/2)*(ball->r()+m_thickness/2))
    {
        ball->bounce(m_B-*ball);
        ball->setPos(m_B+(*ball-m_B).getVectWithNorm(ball->r()+m_thickness/2));
    }
}

void Wall::receiveOrder(const EventHandler &event)
{

}

void Wall::draw(sf::RenderTarget &render)
{
    m_shape.setRotation((m_B-m_A).angle()*180/3.14);
    render.draw(m_shape);
    render.draw(m_cornerA);
    render.draw(m_cornerB);
}

void Wall::update()
{

}

bool Wall::colRect(Vec A, Vec B) const
{
    return false;
}

bool Wall::isInside(Vec vec) const
{
    return distSquared(m_A, vec) < m_thickness*m_thickness || distSquared(m_B, vec) < m_thickness*m_thickness;
}
