#include <SFML/Graphics.hpp>
#include "counter.h"

Displayer Displayer::instance;

void Displayer::addValue(Vec pos, std::string valueName, std::string val)
{
    if(m_vals[valueName] == "")
    {
        m_pos.push_back(pos);
        m_valNames.push_back(valueName);
    }
    m_vals[valueName] = val;
}

void Displayer::draw(sf::RenderTarget &render) const
{
    for(int i=0; i<m_pos.size(); i++)
    {
        std::string val = m_vals.at(m_valNames[i]);
        draw::drawText(render, m_pos[i], val, 20, sf::Color::White);
    }
}

std::string& Displayer::operator[](std::string valueName)
{
    return m_vals[valueName];
}
