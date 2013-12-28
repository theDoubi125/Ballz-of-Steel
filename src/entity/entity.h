#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "../math/vec.h"
#include "../gui/gui.h"

class Player;
class World;

enum entityType
{
    UNDEFINED, BALL, BUILDING
};

class Entity : public Vec
{
public:
    Entity(Player &player, Vec pos, entityType type, int m_maxHealth);
    Entity(const Entity &model);
    virtual ~Entity();

    void move(Vec m);
    Vec getPos() const;
    void setPos(Vec pos);

    bool isAlive() const;
    void kill();

    virtual void draw(sf::RenderTarget &render) = 0;
    virtual void drawSelected(sf::RenderTarget &render) = 0;
    virtual void drawForeground(sf::RenderTarget &render, Vec mousePos) = 0;
    void drawGui(sf::RenderTarget &render, Vec drawPos, Vec drawDim) const;
    virtual void update();

    virtual bool colRect(Vec A, Vec B) const = 0;

    entityType getType() const;

    void setWorld(World *world);
    World *getWorld() const;

    virtual void handleInteraction(Entity *other) = 0;

    Player& getPlayer() const;

    int getMaxHealth() const;
    int getHealth() const;
    void setHealth(int PVs);
    void damage(int damage);

    virtual Gui* getGui() const;

    void drawHealthBar(sf::RenderTarget &render, Vec pos, Vec dim, double alpha);

    virtual bool isInside(Vec vec) const = 0;

    void showHealthBar();
    bool mustDrawHealth() const;
    double getHealthAlpha() const;

    void setMouseDist(double dist);

    int getLastHitTime() const;

private:
    World *m_world;
    entityType m_type;
    Player &m_player;
    int m_health, m_maxHealth;
    double m_mouseDist;
    int m_timeCol;
    int m_lastHitTime;
protected:
    Gui *m_gui;
};

class MovingEntity : public Entity
{
public:
    MovingEntity(Player &player, Vec pos, Vec speed, entityType type, int maxHealth);
    virtual ~MovingEntity();
    void setSpeed(Vec speed);

    void setSpeedX(double vx);
    void setSpeedY(double vy);

    void mulSpeed(double f);
    void applyForce(Vec f);
    void centralForce(double f, Vec C);
    Vec getSpeed() const;

    virtual void update();

private:
    Vec m_speed;
};

#include "../player/player.h"
#include "../world/world.h"

#endif // ENTITY_H_INCLUDED
