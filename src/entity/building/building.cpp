#include <SFML/Graphics.hpp>

#include "building.h"

Building::Building(Player &player, Vec pos, int maxHealth) : Entity(player, pos, BUILDING, maxHealth)
{

}

Building::Building(const Building &model) : Entity(model)
{

}

RoundBuilding::RoundBuilding(Player &player, Vec pos, double r, int maxHealth) : Building(player, pos, maxHealth), m_r(r)
{

}

RoundBuilding::RoundBuilding(const RoundBuilding &model) : Building((Building&)model), m_r(model.m_r)
{

}

double RoundBuilding::r() const
{
    return m_r;
}

bool RoundBuilding::doesBallCollide(const Ball &ball) const
{
    return distSquared(*this, ball) < m_r*m_r;
}
