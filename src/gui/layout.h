#ifndef LAYOUT_H_INCLUDED
#define LAYOUT_H_INCLUDED

#include "gui.h"
#include <sstream>

enum Dir
{
    VTOP, VBOTTOM, HRIGHT, HLEFT
};

class StackLayout : public Gui
{
public:
    StackLayout(Dir dir);
    virtual ~StackLayout();
    virtual void drawChildren(sf::RenderTarget &render, Vec pos, Vec dim) const;
    virtual void updateChildren(const PlayerController &controller, Vec pos, Vec dim);
    virtual Vec getPreferredSize() const;

    Vec* getDrawPos(Vec pos, Vec dim) const;

    bool hasComponentAt(Vec pos) const;
private:
    Dir m_dir;
    Vec *m_drawPos;
    sf::Color col;
    Font font;
};

class LayoutFiller : public Gui
{
public:
    virtual Vec getPreferredSize() const;
};

#endif // LAYOUT_H_INCLUDED
