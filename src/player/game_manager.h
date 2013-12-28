#ifndef GAME_MANAGER_H_INCLUDED
#define GAME_MANAGER_H_INCLUDED

#include "../event/player_controller.h"
#include "../entity/entity.h"

class World;
class Entity;

class GameManager
{
public:
    GameManager(Vec screenDim, World &world, std::vector<Player*> players);
    ~GameManager();

    void update();
    void draw(sf::RenderWindow &render) const;

private:
    World &m_world;
    std::vector<Player*> m_players;
    Vec *m_screenPos, *m_screenDim, m_totalScreenDim;
};

#endif // GAME_MANAGER_H_INCLUDED
