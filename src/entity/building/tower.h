#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include "building.h"

class Tower : public RoundBuilding
{
public:
    Tower(Player &Player, Vec pos, double r, int stock, int shootRate, int maxHealth);
    Tower(const Tower &model);
    virtual ~Tower();

    virtual void handleInteraction(Entity *ball);
    virtual void receiveOrder(const PlayerController &event);
    virtual void draw(sf::RenderTarget &render);
    virtual void update();

    virtual bool colRect(Vec A, Vec B) const;
    virtual bool isInside(Vec vec) const;

private:
    int m_capacity, m_shootRate, m_timeShot;
    std::vector<Ball*> m_stock;
    sf::CircleShape m_shape;
};

#endif // TOWER_H_INCLUDED
