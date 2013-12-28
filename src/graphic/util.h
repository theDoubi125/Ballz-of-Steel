#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED
#include <sstream>

#include "../math/vec.h"
#include "counter.h"

namespace draw
{
    void drawRect(sf::RenderTarget &render, Vec A, Vec B, sf::Color col, int thickness = 1, sf::Color fillCol = sf::Color(0, 0, 0, 0));
    void fillRect(sf::RenderTarget &render, Vec A, Vec B, sf::Color col);

    void drawText(sf::RenderTarget &render, Vec pos, std::string str, int size = 20, sf::Color col = sf::Color::Black);

    void initRenderEngine();
    static sf::Font font;

    template <typename T>
    std::string to_string(T x)
    {
        std::ostringstream stream;
        stream << x;
        return stream.str();
    }
}

#endif // UTIL_H_INCLUDED
