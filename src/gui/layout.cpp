#include <SFML/Graphics.hpp>

#include "../graphic/util.h"
#include "layout.h"
#include <sstream>

StackLayout::StackLayout(Dir dir) : m_dir(dir), m_drawPos(NULL), col(std::rand()%255, std::rand()%255, std::rand()%255)
{

}

StackLayout::~StackLayout()
{
    delete[] m_drawPos;
}

void StackLayout::drawChildren(sf::RenderTarget &render, Vec pos, Vec dim) const
{
    if(m_drawPos != NULL)
    {
        for(int i=0; i<m_children.size(); i++)
        {
            m_children[i]->drawChildren(render, m_drawPos[i], m_drawPos[i+m_children.size()]);
        }
    }
}

void StackLayout::updateChildren(const PlayerController &controller, Vec pos, Vec dim)
{
    m_drawPos = getDrawPos(pos, dim);
    for(int i=0; i<m_children.size(); i++)
        m_children[i]->updateChildren(controller, m_drawPos[i], m_drawPos[i+m_children.size()]);
}

Vec* StackLayout::getDrawPos(Vec pos, Vec dim) const
{
    Vec *result = new Vec[m_children.size()*2];
    std::vector<int> unknownSize;
    double usedSize = 0;
    double *finalSize = new double[m_children.size()];
    for(int i=0; i<m_children.size(); i++)
    {
        if(m_dir == VTOP || m_dir == VBOTTOM)
        {
            usedSize += m_children[i]->getPreferredSize().y;
            if(m_children[i]->getPreferredSize().y == 0)
                unknownSize.push_back(i);
        }
        else
        {
            usedSize += m_children[i]->getPreferredSize().x;
            if(m_children[i]->getPreferredSize().x == 0)
                unknownSize.push_back(i);
        }
    }
    double emptySize;
    if(m_dir == VTOP || m_dir == VBOTTOM)
        emptySize = dim.y-usedSize;
    else emptySize = dim.x-usedSize;

    if(emptySize < 0)
    {
        double ratio;
        if(m_dir == VTOP || m_dir == VBOTTOM)
            ratio = dim.y/usedSize;
        else ratio = dim.x/usedSize;
        for(int i=0; i<m_children.size(); i++)
        {
            if(m_dir == VTOP || m_dir == VBOTTOM)
                finalSize[i] = m_children[i]->getPreferredSize().y*ratio;
            else finalSize[i] = m_children[i]->getPreferredSize().x*ratio;
        }
    }
    else
    {
        for(int i=0; i<m_children.size(); i++)
        {
            if(m_dir == VTOP || m_dir == VBOTTOM)
            {
                finalSize[i] = m_children[i]->getPreferredSize().y;
                if(m_children[i]->getPreferredSize().y == 0)
                    finalSize[i] = emptySize/unknownSize.size();
            }
            else
            {
                finalSize[i] = m_children[i]->getPreferredSize().x;
                if(m_children[i]->getPreferredSize().x == 0)
                    finalSize[i] = emptySize/unknownSize.size();
            }
        }
    }

    double drawOffset = 0;
    for(int i=0; i<m_children.size(); i++)
    {
        Vec finalDim, finalPos;
        double dimX, dimY;
        switch(m_dir)
        {
        case VTOP:
            dimX = m_children[i]->getPreferredSize().x;
            if(dimX == 0)
                dimX = dim.x;
            if(dimX > dim.x)
                dimX = dim.x;
            finalDim = Vec(dimX, finalSize[i]);
            finalPos = pos+Vec((dim.x-dimX)/2, drawOffset);
            break;
        case VBOTTOM:
            dimX = m_children[i]->getPreferredSize().x;
            if(dimX > dim.x)
                dimX = dim.x;
            if(dimX == 0)
                dimX = dim.x;
            finalDim = Vec(dimX, finalSize[i]);
            finalPos = pos+Vec((dim.x-dimX)/2, dim.y-drawOffset-finalSize[i]);
            break;
        case HRIGHT:
            dimY = m_children[i]->getPreferredSize().y;
            if(dimY == 0)
                dimY = dim.y;
            if(dimY > dim.y)
                dimY = dim.y;
            finalDim = Vec(finalSize[i], dimY);
            finalPos = pos+Vec(dim.x-drawOffset-finalSize[i], (dim.y-dimY)/2);
            break;
        case HLEFT:
            dimY = m_children[i]->getPreferredSize().y;
            if(dimY == 0)
                dimY = dim.y;
            if(dimY > dim.y)
                dimY = dim.y;
            finalDim = Vec(finalSize[i], dimY);
            finalPos = pos+Vec(drawOffset, (dim.y-dimY)/2);
            break;
        }
        result[i] = finalPos;
        result[i+m_children.size()] = finalDim;
        drawOffset += finalSize[i];
    }
    return result;
}

Vec StackLayout::getPreferredSize() const
{
    return Vec(0, 0);
}

Vec LayoutFiller::getPreferredSize() const
{
    return Vec(0, 0);
}

bool StackLayout::hasComponentAt(Vec pos) const
{
    for(int i=0; i<m_children.size(); i++)
        if(pos.insideRect(m_drawPos[i], m_drawPos[i+m_children.size()]))
            return true;
    return false;
}
