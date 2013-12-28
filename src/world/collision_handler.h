#ifndef COLLISION_HANDLER_H_INCLUDED
#define COLLISION_HANDLER_H_INCLUDED

#include "../entity/entity.h"

class World;
class Entity;

class CollisionHandler
{
public:
    CollisionHandler(World &world, int wClip, int hClip);
    ~CollisionHandler();
    void update();
    void addEntity(Entity* entity);
    void erase(Entity *entity);
    std::vector<Entity*>& getClip(int x, int y);
    std::vector<Entity*> selectEntitiesInRect(const Player *Player, Vec A, Vec B);
    std::vector<Entity*> getEntitiesInRect(Vec A, Vec B);

private:
    void addEntity(Entity* entity, int x, int y);


private:
    World &m_world;
    std::vector<Entity*> *m_clips;
    int m_clipsX, m_clipsY;
};

#endif // COLLISION_HANDLER_H_INCLUDED
