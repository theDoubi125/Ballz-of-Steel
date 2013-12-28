#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "../math/vec.h"
#include "../event/player_controller.h"
#include "listener.h"

class Gui
{
public:
    Gui();
    virtual ~Gui();
    virtual void drawBefore(sf::RenderTarget &render, Vec pos, Vec dim) const;
    virtual void drawAfter(sf::RenderTarget &render, Vec pos, Vec dim) const;
    virtual void drawChildren(sf::RenderTarget &render, Vec pos, Vec dim) const;
    virtual void update(const PlayerController &event, Vec pos, Vec dim);
    virtual void updateChildren(const PlayerController &event, Vec pos, Vec dim);

    virtual Vec getPreferredSize() const = 0;

    void addChild(Gui* child);

    void addListener(Listener *listener);

protected:
    Vec m_dim;
    std::vector<Gui*> m_children;
    std::vector<Listener*> m_listeners;
};

#endif // GUI_H_INCLUDED
