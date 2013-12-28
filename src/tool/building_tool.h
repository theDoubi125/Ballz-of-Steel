#ifndef BUILDING_TOOL_H_INCLUDED
#define BUILDING_TOOL_H_INCLUDED

#include "tool.h"

class BuildingTool : public Tool
{
public:
    BuildingTool(World &world, std::vector<Player*> Players, Vec pos, Vec dim, std::vector<Tool*> *others, int type, int health);
    virtual ~BuildingTool();

    virtual void useTool(World &world, const PlayerController &event);

private:
    int m_type, m_health;
};

#endif // BUILDING_TOOL_H_INCLUDED
