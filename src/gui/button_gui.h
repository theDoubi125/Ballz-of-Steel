#ifndef BUTTON_GUI_H_INCLUDED
#define BUTTON_GUI_H_INCLUDED

#include "gui.h"

class GuiButton : public Gui
{
public:
    GuiButton(int id, Vec dim, sf::Color baseColor, sf::Color hoveredColor);
    virtual void drawBefore(sf::RenderTarget &render, Vec pos, Vec dim) const;
    virtual void update(const PlayerController &event, Vec pos, Vec dim);

    virtual Vec getPreferredSize() const;

    int getId() const;
private:
    Vec m_dim;
    bool m_hovered;
    sf::Color m_baseColor, m_hoveredColor;
    int m_id;
};

#endif // BUTTON_GUI_H_INCLUDED
