#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "building.h"

class Wall : public Building
{
public:
    Wall(Player &Player, Vec A, Vec B, double thickness, int maxHealth);

    virtual void handleInteraction(Entity *ball);
    virtual void receiveOrder(const EventHandler &event);
    virtual void draw(sf::RenderTarget &render);
    virtual void update();

    virtual bool colRect(Vec A, Vec B) const;
    virtual bool isInside(Vec vec) const;

private:
    Vec m_A, m_B;
    double m_thickness;
    sf::RectangleShape m_shape;
    sf::CircleShape m_cornerA, m_cornerB;
};

#endif // WALL_H_INCLUDED
