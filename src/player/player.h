#ifndef Player_H_INCLUDED
#define Player_H_INCLUDED

#include "../event/player_controller.h"
#include "../entity/entity.h"
#include "../gui/ingame_gui.h"

class World;
class Entity;
class GuiIngame;

class Player
{
public:
    Player(PlayerController &controller, World &world, sf::Color baseCol, sf::Color selectedCol, sf::Color chargingCol, sf::Color selectedChargingCol);
    ~Player();
    sf::Color getBaseColor() const;
    sf::Color getSelectedColor() const;
    sf::Color getChargingColor() const;
    sf::Color getSelectedChargingColor() const;
    PlayerController& getController() const;
    std::vector<Entity*> getSelection() const;

    void setResolution(Vec drawPos, Vec drawDim, Vec resolution);

    void update();
    void draw(sf::RenderWindow &render) const;
    void setSelection(std::vector<Entity*> selection);
    void unselect(Entity *entity);
    void sendOrder();

    Vec mousePos() const;
    Vec screenToWorld(Vec pos) const;
    Vec worldToScreen(Vec pos) const;

private:
    sf::Color m_baseCol, m_selectedCol, m_chargingCol, m_selectedChargingCol;
    PlayerController &m_controller;
    World &m_world;
    std::vector<Entity*> m_selection;
    double *m_zooms;

    GuiIngame *m_gui;

    Vec m_A, m_B; //coordonnées du rectangle de sélection
    bool m_selecting;

    Vec m_drawPos, m_drawDim, m_resolution;
};

#endif // Player_H_INCLUDED
