#include <SFML/Graphics.hpp>

/*#include "select_tool.h"
#include "../graphic/util.h"

SelectTool::SelectTool(World &world, std::vector<Player*> Players, Vec pos, Vec dim, std::vector<Tool*> *others) : Tool(world, Players, pos, dim, others), m_A(0, 0), m_B(0, 0), m_select(false)
{

}

SelectTool::~SelectTool()
{

}

void SelectTool::useTool(World &world, const PlayerController &event)
{
    if(event.pressed(SELECT))
    {
        m_select = true;
        m_A = event.mousePos();
        m_B = event.mousePos();
    }
}

void SelectTool::updateTool(const PlayerController &event)
{
    if(event.down(SELECT))
        m_B = event.mousePos();
    else m_select = false;
    if(m_select)
        getPlayer()->setSelection(getWorld().getEntitiesInRect(getPlayer(), m_A.screenToWorld(), m_B.screenToWorld()));
    if(isSelected())
        getPlayer()->sendOrder();
}

void SelectTool::draw(sf::RenderTarget &render, const PlayerController &event) const
{
    Tool::draw(render, event);
    if(m_select)
        draw::drawRect(render, m_A, m_B-m_A, getPlayer()->getBaseColor());
}
*/
