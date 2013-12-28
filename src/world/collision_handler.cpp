#include <SFML/Graphics.hpp>

#include "world.h"
#include "collision_handler.h"
#include "../graphic/util.h"
#include "../graphic/counter.h"

CollisionHandler::CollisionHandler(World &world, int clipsX, int clipsY) : m_world(world), m_clipsX(clipsX), m_clipsY(clipsY)
{
    m_clips = new std::vector<Entity*>[clipsX*clipsY];
}

CollisionHandler::~CollisionHandler()
{
    //for(int i=0; i<m_clipsX*m_clipsY; i++)
    //    for(int j=0; j<m_clips[i].size(); j++)
    //        delete m_clips[i][j];
    //delete[] m_clips;
}

void CollisionHandler::update()
{
    double clipDimX = m_world.getDim().x/m_clipsX;
    double clipDimY = m_world.getDim().y/m_clipsY;
    std::vector<Entity*> *temp = new std::vector<Entity*>[m_clipsX*m_clipsY];
    for(int i=0; i<m_clipsX; i++)
    {
        for(int j=0; j<m_clipsY; j++)
        {
            std::vector<Entity*> &clip = getClip(i, j);
            for(std::vector<Entity*>::iterator it = clip.begin(); it < clip.end(); it++)
            {
                (*it)->update();
                if(!(*it)->isAlive())
                {
                    if((*it)->getType() == BALL)
                        ((Ball*)*it)->stopMoving();
                    delete *it;
                    clip.erase(it);
                }
            }
            for(int k=0; k<clip.size(); k++)
            {

                for(int n=k; n<clip.size(); n++)
                    clip[k]->handleInteraction(clip[n]);
                if(i>0)
                {
                    for(int n=k; n<getClip(i-1, j).size(); n++)
                        clip[k]->handleInteraction(getClip(i-1, j)[n]);
                    if(j>0)
                    {
                        for(int n=k; n<getClip(i-1, j-1).size(); n++)
                            clip[k]->handleInteraction(getClip(i-1, j-1)[n]);
                    }
                    if(j<m_clipsY-1)
                    {
                        for(int n=k; n<getClip(i-1, j+1).size(); n++)
                            clip[k]->handleInteraction(getClip(i-1, j+1)[n]);
                    }
                }
                if(i<m_clipsX-1)
                {
                    for(int n=k; n<getClip(i+1, j).size(); n++)
                        clip[k]->handleInteraction(getClip(i+1, j)[n]);
                    if(j>0)
                    {
                        for(int n=k; n<getClip(i+1, j-1).size(); n++)
                            clip[k]->handleInteraction(getClip(i+1, j-1)[n]);
                    }
                    if(j<m_clipsY-1)
                    {
                        for(int n=k; n<getClip(i+1, j+1).size(); n++)
                            clip[k]->handleInteraction(getClip(i+1, j+1)[n]);
                    }
                }
                if(j>0)
                {
                    for(int n=k; n<getClip(i, j-1).size(); n++)
                        clip[k]->handleInteraction(getClip(i, j-1)[n]);
                }
                if(j<m_clipsY-1)
                {
                    for(int n=k; n<getClip(i, j+1).size(); n++)
                        clip[k]->handleInteraction(getClip(i, j+1)[n]);
                }
                int x = std::min(m_clipsX-1, std::max(0, (int)(clip[k]->x/clipDimX)));
                int y = std::min(m_clipsX-1, std::max(0, (int)(clip[k]->y/clipDimY)));
                temp[x+y*m_clipsX].push_back(clip[k]);

            }
        }
    }
    delete[] m_clips;
    m_clips = temp;
}

void CollisionHandler::addEntity(Entity *entity)
{
    double clipDimX = m_world.getDim().x/m_clipsX;
    double clipDimY = m_world.getDim().y/m_clipsY;
    int x = (int)(entity->x/clipDimX);
    int y = (int)(entity->y/clipDimY);
    addEntity(entity, x, y);
}

void CollisionHandler::erase(Entity *entity)
{
    double clipDimX = m_world.getDim().x/m_clipsX;
    double clipDimY = m_world.getDim().y/m_clipsY;
    int x = (int)(entity->x/clipDimX);
    int y = (int)(entity->y/clipDimY);
    std::vector<Entity*>& entities = getClip(x, y);
    for(std::vector<Entity*>::iterator it = entities.begin(); it < entities.end(); it++)
    {
        if(entity == *it)
            entities.erase(it);
    }
}

std::vector<Entity*>& CollisionHandler::getClip(int x, int y)
{
    return m_clips[std::min(x, m_clipsX-1)+m_clipsX*std::min(y, m_clipsY-1)];
}

std::vector<Entity*> CollisionHandler::getEntitiesInRect(Vec A, Vec B)
{
    double clipDimX = m_world.getDim().x/m_clipsX;
    double clipDimY = m_world.getDim().y/m_clipsY;
    int Ax = (int)(A.x/clipDimX);
    int Ay = (int)(A.y/clipDimY);
    int Bx = (int)(B.x/clipDimX);
    int By = (int)(B.y/clipDimY);
    std::vector<Entity*> result;
    for(int x = std::max(0, Ax-1); x<std::min(m_clipsX, Bx+2); x++)
    {
        for(int y = std::max(0, Ay-1); y<std::min(m_clipsY, By+2); y++)
        {
            std::vector<Entity*> clip = getClip(x, y);
            for(int i=0; i<clip.size(); i++)
            {
                result.push_back(clip[i]);
            }
        }
    }
    return result;
}

std::vector<Entity*> CollisionHandler::selectEntitiesInRect(const Player *player, Vec A, Vec B)
{
    std::vector<Entity*> selected;
    entityType type = BUILDING;
    double clipDimX = m_world.getDim().x/m_clipsX;
    double clipDimY = m_world.getDim().y/m_clipsY;
    int Ax = (int)(A.x/clipDimX);
    int Ay = (int)(A.y/clipDimY);
    int Bx = (int)(B.x/clipDimX);
    int By = (int)(B.y/clipDimY);

    std::vector<Entity*> result;
    for(int x = std::max(0, Ax-1); x<std::min(m_clipsX, Bx+2); x++)
    {
        for(int y = std::max(0, Ay-1); y<std::min(m_clipsY, By+2); y++)
        {
            std::vector<Entity*> clip = getClip(x, y);
            for(int i=0; i<clip.size(); i++)
            {
                if(&(clip[i]->getPlayer()) == player && clip[i]->colRect(A, B))
                {
                    if(clip[i]->getType() == BALL && type == BUILDING)
                    {
                        selected.clear();
                        type = BALL;
                    }
                    if(clip[i]->getType() == type && ((A == B && selected.size() == 0) || A != B))
                    {
                        selected.push_back(clip[i]);
                    }
                }
            }
        }
    }
    return selected;
}

void CollisionHandler::addEntity(Entity *entity, int x, int y)
{
    m_clips[std::min(x, m_clipsX-1)+m_clipsX*std::min(y, m_clipsY-1)].push_back(entity);
}
