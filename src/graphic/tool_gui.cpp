#include <SFML/Graphics.hpp>

#include "../math/vec.h"
#include "ingame_gui.h"
#include "util.h"
#include "tool_gui.h"
#include "../tool/select_tool.h"
#include "../tool/building_tool.h"

ToolGui::ToolGui(World &world, std::vector<Player*> Players, Vec pos, Vec dim) : Gui(pos), m_dim(dim)
{
    m_selectTool = new SelectTool(world, Players, Vec(10, 20), Vec(60, 60), &m_tools);
    m_tools.push_back(m_selectTool);
    m_tools.push_back(new BallTool(world, Players, Vec(80, 20), Vec(60, 60), &m_tools, 0, 20, 3, 500));
    m_tools.push_back(new BallTool(world, Players, Vec(150, 20), Vec(60, 60), &m_tools, 0, 40, 10, 2500));
    m_tools.push_back(new BallTool(world, Players, Vec(220, 20), Vec(60, 60), &m_tools, 1, 10, 1, 300));
    m_tools.push_back(new BuildingTool(world, Players, Vec(290, 20), Vec(60, 60), &m_tools, 0, 5000));
    for(int i=0; i<m_tools.size(); i++)
        addChild(m_tools[i]);
}

ToolGui::~ToolGui()
{

}

void ToolGui::draw(sf::RenderTarget &render, const PlayerController &event) const
{
    drawRect(render, getPos(), m_dim, sf::Color::Black, 1, sf::Color(100, 100, 100, 255));
}

bool ToolGui::isInside(Vec pos) const
{
    return pos.x > getPos().x && pos.x < getPos().x + m_dim.x && pos.y > getPos().y && pos.y < getPos().y + m_dim.y;
}

void ToolGui::update(const PlayerController &event)
{
    /*if(event.keyPressed(sf::Keyboard::Escape))
        for(int i=0; i<m_tools.size(); i++)
            m_tools[i]->unselect();*/
}

Tool* ToolGui::getSelectedTool() const
{
    for(int i=0; i<m_tools.size(); i++)
    {
        if(m_tools[i]->isSelected())
            return m_tools[i];
    }
    m_tools[0]->select();
    return m_tools[0];
}
