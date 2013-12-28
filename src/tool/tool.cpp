#include <SFML/Graphics.hpp>

#include "tool.h"
#include "../graphic/util.h"

Tool::Tool(World &world, std::vector<Player*> players, Vec pos, Vec dim, std::vector<Tool*> *others) :
    Gui(pos),
    m_dim(dim),
    m_selected(false),
    m_player(0),
    m_others(others),
    m_world(world),
    m_players(players)
{

}

Tool::~Tool()
{

}

void Tool::draw(sf::RenderTarget &render, const PlayerController &event) const
{
    drawRect(render, getPos(), m_dim, sf::Color::Black, 1, m_selected ? getPlayer()->getBaseColor() : (isInside(event.mousePos()) ? sf::Color(150, 150, 150, 255) : sf::Color(100, 100, 100, 255)));
}

bool Tool::isInside(Vec mousePos) const
{
    return mousePos.x > getPos().x && mousePos.y > getPos().y && mousePos.x < getPos().x+m_dim.x && mousePos.y < getPos().y+m_dim.y;
}

void Tool::unselect()
{
    m_selected = 0;
}

void Tool::select()
{
    m_selected = true;
    for(int i=0; i<m_others->size(); i++)
    {
        if((*m_others)[i] != this)
            (*m_others)[i]->unselect();
    }
}

bool Tool::isSelected() const
{
    return m_selected;
}

World& Tool::getWorld() const
{
    return m_world;
}

Player* Tool::getPlayer() const
{
    return m_players[m_player];
}

void Tool::update(const PlayerController &event)
{
    updateTool(event);
    if(event.pressed(SELECT) && isInside(event.mousePos()))
    {
        if(m_selected)
            m_player = (m_player+1)%m_players.size();
        else
        {
            select();
        }
    }
}

void Tool::updateTool(const PlayerController &event)
{

}
