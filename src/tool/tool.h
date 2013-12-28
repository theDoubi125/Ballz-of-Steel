#ifndef TOOL_H_INCLUDED
#define TOOL_H_INCLUDED

#include "../graphic/gui.h"
#include "../world/world.h"

class Tool : public Gui
{
public:
    Tool(World &world, std::vector<Player*> Players, Vec pos, Vec dim, std::vector<Tool*> *others);
    virtual ~Tool();
    virtual void draw(sf::RenderTarget &window, const PlayerController &event) const;
    virtual bool isInside(Vec pos) const;
    virtual void update(const PlayerController &event);
    virtual void updateTool(const PlayerController &event);

    void unselect();
    void select();
    bool isSelected() const;

    World& getWorld() const;

    Player* getPlayer() const;

    virtual void useTool(World &world, const PlayerController &event) = 0;

private:
    bool m_selected;
    int m_player;
    Vec m_dim;
    World &m_world;
    std::vector<Tool*> *m_others;
    std::vector<Player*> m_players;
};

#endif // TOOL_H_INCLUDED
