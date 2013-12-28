#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED

#include "../math/vec.h"
#include "../graphic/util.h"

class Displayer
{
public:
    void addValue(Vec pos, std::string valueName, std::string val);
    void draw(sf::RenderTarget &render) const;

    std::string& operator[](std::string valueName);

    static Displayer instance;

private:
    std::vector<Vec> m_pos;
    std::map<std::string, std::string> m_vals;
    std::vector<std::string> m_valNames;
};

#endif // COUNTER_H_INCLUDED
