#include <SFML/Graphics.hpp>

#include "building_tool.h"
#include "../graphic/util.h"
#include "../entity/building/tower.h"

BuildingTool::BuildingTool(World &world, std::vector<Player*> Players, Vec pos, Vec dim, std::vector<Tool*> *others, int type, int health) : Tool(world, Players, pos, dim, others), m_type(type), m_health(health)
{

}

BuildingTool::~BuildingTool()
{

}

void BuildingTool::useTool(World &world, const PlayerController &event)
{
    if(m_type == 0 && event.pressed(SELECT))
        world.addEntity(new Tower(*getPlayer(), event.mousePos().screenToWorld(), 100, 100, 10, m_health));
}
