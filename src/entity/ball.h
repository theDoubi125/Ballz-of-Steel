#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "entity.h"

class MovementHandler;
class Player;

class Ball : public MovingEntity
{
public:
    Ball(Player &player, Vec pos, double r, double m, Vec speed, int maxHealth);
    virtual ~Ball();

    virtual void draw(sf::RenderTarget &render);
    virtual void drawSelected(sf::RenderTarget &render);
    virtual void drawForeground(sf::RenderTarget &render, Vec mousePos);

    sf::Color getColor() const;
    sf::Color getSelectedColor() const;

    virtual void update();

    virtual bool colRect(Vec A, Vec B) const;

    virtual double m() const;
    virtual double r() const;

    virtual void applyOrder(Vec target);

    bool isMoving() const;
    void setMovement(MovementHandler *handler);
    void stopMovement();
    void stopMoving();

    virtual void updateBall();
    virtual void throwBall(Vec pos, Vec dir);

    virtual void handleInteraction(Entity *other);

    void bounce(Vec dir);
    virtual bool isInside(Vec vec) const;

protected:
    double m_m, m_r;

private:
    static sf::Texture m_texture;
    static bool m_loaded;
    sf::Sprite m_sprite, m_selectedSprite;
    sf::CircleShape m_shape;
    MovementHandler* m_movement;
};

void collide(Ball &b1, Ball &b2);
void collisionPush(Ball &b1, Ball &b2);

#endif // BALL_H_INCLUDED
