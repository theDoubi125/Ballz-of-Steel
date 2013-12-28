#include <SFML/Graphics.hpp>
#include <cmath>

#include "game_manager.h"
#include "../graphic/util.h"

GameManager::GameManager(Vec screenDim, World &world, std::vector<Player*> players) : m_world(world), m_players(players)
{
    int playersCount = players.size();

    m_screenPos = new Vec[playersCount];
    m_screenDim = new Vec[playersCount];
    m_totalScreenDim = screenDim;

    int w = ceil(std::sqrt(playersCount));
    int h = round(std::sqrt(playersCount));
    int emptySpace = w*h-playersCount;
    Vec cellDim = Vec(screenDim.x/w, screenDim.y/h);
    int x = 0, y = 0;
    for(int i=0; i<players.size(); i++)
    {
        m_screenPos[i] = Vec(cellDim.x*x, cellDim.y*y);
        m_screenDim[i] = cellDim;
        if(x+1 < w && emptySpace > 0)
        {
            emptySpace--;
            x++;
            m_screenDim[i].x += cellDim.x;
        }
        players[i]->setResolution(m_screenPos[i], m_screenDim[i], m_totalScreenDim);
        x++;
        if(x >= w)
        {
            x = 0;
            y++;
        }
    }
}

GameManager::~GameManager()
{
    for(int i=0; i<m_players.size(); i++)
        delete m_players[i];
    delete[] m_screenDim;
    delete[] m_screenPos;
}

void GameManager::update()
{
    for(int i=0; i<m_players.size(); i++)
    {
        m_players[i]->update();
    }
}

void GameManager::draw(sf::RenderWindow &render) const
{
    for(int i=0; i<m_players.size(); i++)
    {
        m_players[i]->draw(render);
    }
}
