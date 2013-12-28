#ifndef BALL_TOOL_H_INCLUDED
#define BALL_TOOL_H_INCLUDED

#include "tool.h"

class BallTool : public Tool
{
public:
    BallTool(World &world, std::vector<Player*> Players, Vec pos, Vec dim, std::vector<Tool*> *others, int type, double r, double m, int health);
    virtual ~BallTool();

    virtual void useTool(World &world, const PlayerController &event);

private:
    double m_r, m_m;
    int m_type, m_health;
};

#endif // BALL_TOOL_H_INCLUDED
