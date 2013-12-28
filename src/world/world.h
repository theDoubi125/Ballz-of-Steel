#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "../math/vec.h"
#include "../entity/movement_manager.h"
#include "../entity/building/building.h"
#include "collision_handler.h"

class MovementManager;
class MovementHandler;
class Player;

class World
{
public:
    World(Vec dim);
    ~World();

    void update();
    void draw(sf::RenderTarget &render) const;

    void addEntity(Entity *entity);

    std::vector<Entity*> getEntitiesAt(Vec pos) const;

    std::vector<Entity*> getEntitiesInRect(Vec A, Vec B);

    std::vector<Entity*> selectEntitiesInRect(const Player *player, Vec A, Vec B);

    void remove(Entity* toRemove);

    Vec getDim() const;

    void addMovement(MovementHandler *handler);
    void stopMovement(Ball *entity);

    void updateTarget(Ball* ball, Vec target);

private:
    MovementManager m_movements;
    Vec m_dim;
    CollisionHandler *m_colHandler;
};

#endif // WORLD_H_INCLUDED
