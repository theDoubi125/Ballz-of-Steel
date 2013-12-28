#ifndef TOOL_GUI_H_INCLUDED
#define TOOL_GUI_H_INCLUDED

#include "../tool/select_tool.h"

class ToolGui : public Gui
{
public:
    ToolGui(World &world, std::vector<Player*> Players, Vec pos, Vec dim);
    virtual ~ToolGui();
    virtual void draw(sf::RenderTarget &window, const PlayerController &event) const;
    virtual bool isInside(Vec pos) const;
    virtual void update(const PlayerController &event);

    Tool* getSelectedTool() const;
private:
    Vec m_dim;
    std::vector<Tool*> m_tools;
    //SelectTool *m_selectTool;
};

#endif // TOOL_GUI_H_INCLUDED
