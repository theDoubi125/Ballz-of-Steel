#include <SFML/Graphics.hpp>

#include "../graphic/util.h"
#include "tool_gui.h"

#include "layout.h"
#include "button_gui.h"

GuiTool::GuiTool(std::vector<Entity*> *selection) : m_selection(selection)
{

}

void GuiTool::drawBefore(sf::RenderTarget &render, Vec pos, Vec dim) const
{
    draw::drawRect(render, pos, dim, sf::Color::Red, 1, sf::Color::Green);
}

void GuiTool::update(const PlayerController &event, Vec pos, Vec dim)
{

}

Vec GuiTool::getPreferredSize() const
{
    return Vec(0, 100);
}
