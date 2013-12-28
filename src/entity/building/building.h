#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include "../entity.h"

class Ball;

class Building : public Entity
{
public:
    Building(Player &player, Vec pos, int maxHealth);
    Building(const Building &model);
    virtual void receiveOrder(const PlayerController &event) = 0;
};

class RoundBuilding : public Building
{
public:
    RoundBuilding(Player &Player, Vec pos, double r, int maxHealth);
    RoundBuilding(const RoundBuilding &model);

    virtual bool doesBallCollide(const Ball &ball) const;

    double r() const;

private:
    double m_r;
};

#include "../ball.h"

#endif // BUILDING_H_INCLUDED
