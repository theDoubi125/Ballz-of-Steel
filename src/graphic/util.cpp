#include <SFML/Graphics.hpp>

#include "util.h"

void draw::drawRect(sf::RenderTarget &render, Vec A, Vec B, sf::Color col, int thickness, sf::Color fillCol)
{
    sf::RectangleShape shape;
    shape.setPosition(A);
    shape.setSize(B);
    shape.setOutlineColor(col);
    shape.setOutlineThickness(thickness);
    shape.setFillColor(fillCol);
    render.draw(shape);
}

void draw::fillRect(sf::RenderTarget &render, Vec A, Vec B, sf::Color col)
{
    sf::RectangleShape shape;
    shape.setPosition(A);
    shape.setSize(B);
    shape.setFillColor(col);
    shape.setOutlineThickness(0);
    render.draw(shape);
}

void draw::drawText(sf::RenderTarget &render, Vec pos, std::string str, int size, sf::Color col)
{
    sf::Text text(str, draw::font, size);
    text.setColor(col);
    text.setPosition(pos);
    render.draw(text);
}

void draw::initRenderEngine()
{
    draw::font.loadFromFile("font");
}
