#include <SFML/Graphics.hpp>
#include <sstream>

#include "../graphic/util.h"
#include "button_gui.h"

GuiButton::GuiButton(int id, Vec dim, sf::Color baseColor, sf::Color hoveredColor) : m_id(id), m_dim(dim), m_baseColor(baseColor), m_hoveredColor(hoveredColor)
{

}

void GuiButton::drawBefore(sf::RenderTarget &render, Vec pos, Vec dim) const
{
    draw::drawRect(render, pos, dim, sf::Color::Black, 1, m_hovered ? m_hoveredColor:m_baseColor);
}

void GuiButton::update(const PlayerController &controller, Vec pos, Vec dim)
{
    m_hovered = controller.mousePos().insideRect(pos, dim);
}

Vec GuiButton::getPreferredSize() const
{
    return m_dim;
}

int GuiButton::getId() const
{
    return m_id;
}
