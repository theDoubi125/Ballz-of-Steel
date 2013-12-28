#include <SFML/Graphics.hpp>

#include "../graphic/util.h"
#include "ingame_gui.h"
#include "layout.h"
#include "tool_gui.h"
#include "button_gui.h"

GuiIngame::GuiIngame(std::vector<Entity*> *selection) : m_guiTool(new GuiTool(selection))
{

}

GuiIngame::~GuiIngame()
{
    delete m_layout;
    delete m_guiTool;
}

void GuiIngame::drawBefore(sf::RenderTarget &render, Vec pos, Vec dim) const
{
    //draw::drawRect(render, pos+Vec(0, dim.y-150), Vec(dim.x, 150), sf::Color::Red, 1, sf::Color::Green);

}

void GuiIngame::drawAfter(sf::RenderTarget &render, Vec pos, Vec dim) const
{
    draw::drawRect(render, pos+m_mousePos, Vec(3, 3), sf::Color::Red, 1, sf::Color::Green);
    m_guiTool->drawChildren(render, pos+Vec(0, dim.y-HGUI), Vec(dim.x, HGUI));
}

void GuiIngame::update(const PlayerController &event, Vec pos, Vec dim)
{
    m_mousePos = event.mousePos();
}

Vec GuiIngame::getPreferredSize() const
{
    return Vec(0, 0);
}

bool GuiIngame::isInside(Vec pos) const
{
    return false;
}
