#include <SFML/Graphics.hpp>

#include "player.h"
#include "../graphic/util.h"
#include <sstream>

Player::Player(PlayerController &controller, World &world, sf::Color baseCol, sf::Color selectedCol, sf::Color chargingCol, sf::Color selectedChargingCol) :
        m_controller(controller),
        m_world(world),
        m_baseCol(baseCol),
        m_selectedCol(selectedCol),
        m_chargingCol(chargingCol),
        m_selectedChargingCol(selectedChargingCol),
        m_selecting(false),
        m_zooms(new double[4]),
        m_gui(new GuiIngame(&m_selection))
{
    m_zooms[0] = 1.3;
    m_zooms[1] = 1;
    m_zooms[2] = 0.7;
    m_zooms[3] = 0.5;
}

Player::~Player()
{
    delete[] m_zooms;
    delete m_gui;
}

sf::Color Player::getBaseColor() const
{
    return m_baseCol;
}

sf::Color Player::getSelectedColor() const
{
    return m_selectedCol;
}

PlayerController& Player::getController() const
{
    return m_controller;
}

std::vector<Entity*> Player::getSelection() const
{
    return m_selection;
}

void Player::setSelection(std::vector<Entity*> selection)
{
    m_selection = selection;
}

void Player::unselect(Entity *entity)
{
    for(std::vector<Entity*>::iterator it = m_selection.begin(); it<m_selection.end(); it++)
    {
        if((*it) == entity)
            m_selection.erase(it);
    }
}

void Player::sendOrder()
{
    if(m_selection.size() > 0)
    {
        if(m_selection[0]->getType() == BALL)
        {
            if(m_controller.pressed(ORDER))
            {
                std::vector<Ball*> balls;
                for(int i=0; i<m_selection.size(); i++)
                {
                    Ball* ball = (Ball*)m_selection[i];
                    balls.push_back(ball);
                    m_world.stopMovement(ball);
                }
                MovementHandler *handler = new MovementHandler(balls, m_controller);
                m_world.addMovement(handler);
            }
            else if(m_controller.down(ORDER))
            {
                m_world.updateTarget((Ball*)m_selection[0], screenToWorld(mousePos()));
            }
        }
        else if(m_selection[0]->getType() == BUILDING)
        {
            Building* building = (Building*)m_selection[0];
            building->receiveOrder(m_controller);
        }
    }
}

void Player::update()
{
    m_controller.update();
    m_gui->updateChildren(m_controller, Vec(0, 0), m_drawDim);

    if(m_controller.pressed(SELECT) && !m_gui->isInside(m_controller.mousePos()))
    {
        m_A = screenToWorld(mousePos());
        m_selecting = true;
    }
    if(m_controller.down(SELECT))
        m_B = screenToWorld(mousePos());
    else
    {
        m_A = m_B;
        m_selecting = false;
    }
    if(m_selecting)
    {
        m_selection = m_world.selectEntitiesInRect(this, m_A, m_B);
    }
    if(!m_gui->isInside(m_controller.mousePos()) && m_selection.size() > 0)
        sendOrder();
}

void Player::draw(sf::RenderWindow &render) const
{
    View view(sf::FloatRect(0, 0, m_drawDim.x*(m_zooms[m_controller.getZoom()]), m_drawDim.y*m_zooms[m_controller.getZoom()]));
    view.setCenter(m_controller.getViewCenter());
    view.setViewport(sf::FloatRect(m_drawPos.x/m_resolution.x, m_drawPos.y/m_resolution.y, m_drawDim.x/m_resolution.x, m_drawDim.y/m_resolution.y));
    render.setView(view);
    std::vector<Entity*> toDraw = m_world.getEntitiesInRect(screenToWorld(Vec(0, 0)), screenToWorld(m_drawDim));
    //m_world.draw(render);
    for(int i=0; i<toDraw.size(); i++)
    {
        toDraw[i]->draw(render);
    }
    for(int i=0; i<m_selection.size(); i++)
    {
        m_selection[i]->drawSelected(render);
    }
    draw::drawRect(render, Vec(0, 0), Vec(m_world.getDim()), sf::Color::White);

    for(int i=0; i<toDraw.size(); i++)
    {
        toDraw[i]->drawForeground(render, screenToWorld(mousePos()));
    }
    view.reset(sf::FloatRect(0, 0, m_drawDim.x, m_drawDim.y));
    render.setView(view);
    if(m_selecting)
    {
        draw::drawRect(render, worldToScreen(m_A), worldToScreen(m_B)-worldToScreen(m_A), sf::Color(50, 100, 255, 100), 3);
        draw::drawRect(render, worldToScreen(m_A), worldToScreen(m_B)-worldToScreen(m_A), sf::Color(50, 100, 255, 100));
    }
    m_gui->drawChildren(render, Vec(0, 0), m_drawDim);


    Displayer::instance.draw(render);
    draw::drawRect(render, Vec(1, 1), m_drawDim-Vec(1, 1)*2, sf::Color::White);
}

void Player::setResolution(Vec drawPos, Vec drawDim, Vec resolution)
{
    m_drawPos = drawPos;
    m_drawDim = drawDim;
    m_resolution = resolution;
    m_controller.setScreenDim(drawDim);
    m_controller.setMousePos(drawDim/2);
}

Vec Player::mousePos() const
{
    return m_controller.mousePos();
}

Vec Player::screenToWorld(Vec pos) const
{
    return (pos-m_drawDim/2)*m_zooms[m_controller.getZoom()]+m_controller.getViewCenter();
}

Vec Player::worldToScreen(Vec pos) const
{
    return (pos-m_controller.getViewCenter())/m_zooms[m_controller.getZoom()]+m_drawDim/2;
}
