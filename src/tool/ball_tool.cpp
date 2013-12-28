#include <SFML/Graphics.hpp>

#include "ball_tool.h"
#include "../graphic/util.h"
#include "../entity/ball/charging_ball.h"

BallTool::BallTool(World &world, std::vector<Player*> Players, Vec pos, Vec dim, std::vector<Tool*> *others, int type, double r, double m, int health) : Tool(world, Players, pos, dim, others), m_type(type), m_r(r), m_m(m), m_health(health)
{

}

BallTool::~BallTool()
{

}

void BallTool::useTool(World &world, const PlayerController &event)
{
    Entity *entity;
    if(m_type == 0)
        entity = new Ball(*getPlayer(), event.mousePos().screenToWorld(), m_r, m_m, Vec(0, 0), m_health);
    else if(m_type == 1)
        entity = new ChargingBall(*getPlayer(), event.mousePos().screenToWorld(), m_r, m_m, Vec(0, 0), 40, m_health);
    world.addEntity(entity);
    /*if(!event.keyDown(sf::Keyboard::LShift))
        unselect();*/
}
