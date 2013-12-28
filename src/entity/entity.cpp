#include <SFML/Graphics.hpp>

#include "entity.h"
#include "../graphic/util.h"

Entity::Entity(Player &player, Vec pos, entityType type, int maxHealth) :
        Vec(pos),
        m_world(NULL),
        m_type(type),
        m_player(player),
        m_maxHealth(maxHealth),
        m_health(maxHealth),
        m_timeCol(0),
        m_lastHitTime(0),
        m_gui(NULL)
{
}

Entity::Entity(const Entity &model) : Vec(model.getPos()), m_world(NULL), m_type(model.m_type), m_player(model.m_player), m_maxHealth(model.m_maxHealth), m_health(model.m_maxHealth), m_timeCol(0), m_lastHitTime(0)
{
}

void Entity::setWorld(World *world)
{
    m_world = world;
}

World *Entity::getWorld() const
{
    return m_world;
}

Entity::~Entity()
{
    m_player.unselect(this);
}

void Entity::move(Vec m)
{
    operator+=(m);
}

Vec Entity::getPos() const
{
    return *this;
}

bool Entity::isAlive() const
{
    return m_health > 0;
}

void Entity::kill()
{
    m_health = 0;
}

entityType Entity::getType() const
{
    return m_type;
}

void Entity::setPos(Vec pos)
{
    Vec::operator=(pos);
}

Player& Entity::getPlayer() const
{
    return m_player;
}

int Entity::getHealth() const
{
    return m_health;
}

int Entity::getMaxHealth() const
{
    return m_maxHealth;
}

void Entity::setHealth(int health)
{
    m_health = health;
}

void Entity::damage(int damage)
{
    m_health -= damage;
    m_timeCol = 0;
    m_lastHitTime = 0;
}

Gui* Entity::getGui() const
{
    return m_gui;
}

void Entity::drawHealthBar(sf::RenderTarget &render, Vec pos, Vec dim, double alpha)
{
    draw::drawRect(render, pos, dim, sf::Color(255, 0, 0, alpha*255), 1, sf::Color(0, 0, 0, alpha*255));
    draw::drawRect(render, pos, Vec((dim.x*getHealth()/getMaxHealth()), dim.y), sf::Color(0, 0, 0, alpha*255), 1, sf::Color(0, 255, 0, alpha*255));
}

bool Entity::mustDrawHealth() const
{
    return false;//m_mouseDist < 100*100 || m_timeCol < 50;
}

double Entity::getHealthAlpha() const
{
    return std::max(1-m_mouseDist/100/100, 1.0-(double)m_timeCol/50);
}

void Entity::setMouseDist(double dist)
{
    m_mouseDist = dist;
}

void Entity::update()
{
    m_timeCol++;
    m_lastHitTime++;
}

int Entity::getLastHitTime() const
{
    return m_lastHitTime;
}

void Entity::drawGui(sf::RenderTarget &render, Vec drawPos, Vec drawDim) const
{
    if(m_gui != NULL)
        m_gui->drawChildren(render, drawPos, drawDim);
}

MovingEntity::MovingEntity(Player &player, Vec pos, Vec speed, entityType type, int maxHealth) : Entity(player, pos, type, maxHealth), m_speed(speed)
{

}

MovingEntity::~MovingEntity()
{

}

void MovingEntity::setSpeed(Vec speed)
{
    m_speed = speed;
}

void MovingEntity::setSpeedX(double vx)
{
    m_speed.x = vx;
}

void MovingEntity::setSpeedY(double vy)
{
    m_speed.y = vy;
}

Vec MovingEntity::getSpeed() const
{
    return m_speed;
}

void MovingEntity::mulSpeed(double f)
{
    m_speed *= f;
}

void MovingEntity::applyForce(Vec f)
{
    m_speed += f;
}

void MovingEntity::centralForce(double f, Vec C)
{
    Vec force = (C-getPos()).getVectWithNorm(f);
    m_speed += force;
}

void MovingEntity::update()
{
    Entity::update();
    move(m_speed);
}
