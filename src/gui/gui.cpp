#include <SFML/Graphics.hpp>

#include "gui.h"
#include "../graphic/util.h"

Gui::Gui()
{

}

Gui::~Gui()
{
    //for(int i=0; i<m_children.size(); i++)
        //delete m_children[i];
}

void Gui::drawChildren(sf::RenderTarget &render, Vec pos, Vec dim) const
{
    drawBefore(render, pos, dim);
    for(int i=0; i<m_children.size(); i++)
        m_children[i]->drawChildren(render, pos, dim);
    drawAfter(render, pos, dim);
}

void Gui::drawBefore(sf::RenderTarget &render, Vec pos, Vec dim) const
{

}

void Gui::drawAfter(sf::RenderTarget &render, Vec pos, Vec dim) const
{

}

void Gui::updateChildren(const PlayerController &controller, Vec pos, Vec dim)
{
    update(controller, pos, dim);
    for(int i=0; i<m_children.size(); i++)
        m_children[i]->updateChildren(controller, pos, dim);
    if(controller.pressed(SELECT) && controller.mousePos().x >= pos.x && controller.mousePos().y >= pos.y && controller.mousePos().x < (pos+dim).x && controller.mousePos().y < (pos+dim).y)
    {
        for(int i=0; i<m_listeners.size(); i++)
            m_listeners[i]->actionPerformed(controller, pos, dim, this);
    }
}

void Gui::update(const PlayerController &controller, Vec pos, Vec dim)
{

}

void Gui::addChild(Gui *child)
{
    m_children.push_back(child);
}

void Gui::addListener(Listener *listener)
{
    m_listeners.push_back(listener);
}
