#include <SFML/Graphics.hpp>

#include "world.h"
#include "../graphic/counter.h"

#include "../entity/movement_manager.h"

World::World(Vec dim) : m_dim(dim)
{
    m_colHandler = new CollisionHandler(*this, 10, 10);
}

World::~World()
{
    delete m_colHandler;
}

void World::update()
{
    m_movements.update();
    m_colHandler->update();
}

void World::draw(sf::RenderTarget &render) const
{
    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(m_dim.x, m_dim.y));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(5);
    render.draw(rect);
}

void World::addEntity(Entity *entity)
{
    entity->setWorld(this);
    m_colHandler->addEntity(entity);
}



std::vector<Entity*> World::getEntitiesInRect(Vec A, Vec B)
{
    return m_colHandler->getEntitiesInRect(A, B);
}

Vec World::getDim() const
{
    return m_dim;
}

void World::remove(Entity *toRemove)
{
    m_colHandler->erase(toRemove);
}

void World::stopMovement(Ball *ball)
{
    m_movements.stopMovement(ball);
}

void World::addMovement(MovementHandler *movement)
{
    m_movements.addMovement(movement);
}

std::vector<Entity*> World::selectEntitiesInRect(const Player *player, Vec A, Vec B)
{
    return m_colHandler->selectEntitiesInRect(player, A, B);
}

void World::updateTarget(Ball* ball, Vec target)
{
    m_movements.updateTarget(ball, target);
}
