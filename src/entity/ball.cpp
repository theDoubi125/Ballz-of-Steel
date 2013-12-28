#include <SFML/Graphics.hpp>
#include <cmath>

#include "ball.h"
#include "../world/world.h"
#include "../graphic/image_manager.h"
#include "../graphic/util.h"

bool Ball::m_loaded = false;

Ball::Ball(Player &player, Vec pos, double r, double m, Vec speed, int maxHealth) : MovingEntity(player, pos, speed, BALL, maxHealth), m_m(m), m_r(r), m_movement(NULL)
{
    sf::Texture *texture = ImageManager::instance.getTexture("ball");
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(x-r, y-r);
    m_sprite.setScale(sf::Vector2f(2*r/texture->getSize().x, 2*r/texture->getSize().y));
    m_sprite.setColor(player.getBaseColor());
    sf::Texture *selectedTexture = ImageManager::instance.getTexture("selectedBall");
    m_selectedSprite.setTexture(*selectedTexture);
    m_selectedSprite.setPosition(x-r, y-r);
    m_selectedSprite.setScale(sf::Vector2f(2*r/texture->getSize().x, 2*r/texture->getSize().y));
    m_selectedSprite.setColor(player.getSelectedColor());
}

Ball::~Ball()
{

}

void Ball::draw(sf::RenderTarget &render)
{
    m_sprite.setPosition(x-m_r, y-m_r);
    render.draw(m_sprite);
    //if(mustDrawHealth())
    //    drawHealthBar(render, getPos()-Vec(r(), r()/5), Vec(2*r(), 2*r()/5), getHealthAlpha());
}

void Ball::drawSelected(sf::RenderTarget &render)
{
    m_selectedSprite.setPosition(x-m_r, y-m_r);
    render.draw(m_selectedSprite);
}

void Ball::drawForeground(sf::RenderTarget &render, Vec mousePos)
{
    if(distSquared(getPos(), mousePos) < 10000 || getLastHitTime() < 150)
        drawHealthBar(render, getPos()-Vec(m_r, m_r/4), Vec(m_r*2, m_r/2), std::max(1-distSquared(getPos(), mousePos)/10000, getLastHitTime() < 150 ? 1-getLastHitTime()/150.0:0));
}

sf::Color Ball::getColor() const
{
    return getPlayer().getBaseColor();
}

sf::Color Ball::getSelectedColor() const
{
    return getPlayer().getSelectedColor();
}

void Ball::update()
{
    mulSpeed(0.95);
    if(getWorld() != NULL)
    {
        if(x < r())
        {
            setSpeedX(std::abs(getSpeed().x));
            x = r();
        }
        if(y < r())
        {
            setSpeedY(std::abs(getSpeed().y));
            y = r();
        }
        if(x+r() > getWorld()->getDim().x)
        {
            setSpeedX(-std::abs(getSpeed().x));
            x = getWorld()->getDim().x-r();
        }
        if(y+r() > getWorld()->getDim().y)
        {
            setSpeedY(-std::abs(getSpeed().y));
            y = getWorld()->getDim().y-r();
        }
    }
    updateBall();
    MovingEntity::update();
}

double Ball::m() const
{
    return m_m;
}

double Ball::r() const
{
    return m_r;
}

void collide(Ball &b1, Ball &b2)
{
    Vec AB = b1-b2;
	Vec v1 = b1.getSpeed().proj(AB), v2 = b2.getSpeed().proj(AB);
    if(&b1 == &b2)
        return;
    collisionPush(b1, b2);
    if((v1-v2)*AB <= 0)
	{

		Vec newV1 = 2*b2.m()/(b2.m()+b1.m())*v2+(b1.m()-b2.m())/(b1.m()+b2.m())*v1;
		Vec newV2 = 2*b1.m()/(b1.m()+b2.m())*v1+(b2.m()-b1.m())/(b2.m()+b1.m())*v2;

        double energy = b1.m()*v1.normSquared()*(v1*(b2-b1)>0 ? 1:-1)-b2.m()*v2.normSquared()*(v2*(b1-b2)>0 ? 1:-1);
        if(&b1.getPlayer() != &b2.getPlayer() && std::abs(energy) > 20)
        {
            if(energy > 0)
                b2.damage(std::abs(energy));
            else
                b1.damage(std::abs(energy));
        }
		b1.setSpeed((b1.getSpeed()-v1+newV1));
		b2.setSpeed((b2.getSpeed()-v2+newV2));
	}
}

void collisionPush(Ball &b1, Ball &b2)
{
    Vec v1 = b1.getSpeed(), v2 = b2.getSpeed();
    double f = 0;
    while(dist(b1-v1*f, b2-v2*f) > b1.r() + b2.r())
    {
        f+=0.001;
    }
    Vec C = ((b1-v1*f)*b2.r() + (b2 -v2*f)*b1.r())/(b1.r()+b2.r());
    Vec dir = b1-b2+(v2-v1)*f;
    b1.setPos(C+dir.getVectWithNorm(b1.r())*1.000001);
    b2.setPos(C-dir.getVectWithNorm(b2.r())*1.000001);
}

bool Ball::colRect(Vec A, Vec B) const
{
    double minX = std::min(A.x, B.x);
    double minY = std::min(A.y, B.y);
    double maxX = std::max(A.x, B.x);
    double maxY = std::max(A.y, B.y);
    return (x > minX && x < maxX && (y + m_r > minY && y - m_r < maxY))
            || (y > minY && y < maxY && (x + m_r > minX && x - m_r < maxX))
            || distSquared(getPos(), A) < m_r*m_r
            || distSquared(getPos(), B) < m_r*m_r
            || distSquared(getPos(), Vec(A.x, B.y)) < m_r*m_r
            || distSquared(getPos(), Vec(B.x, A.y)) < m_r*m_r;
}

void Ball::applyOrder(Vec target)
{
    centralForce(0.3, target);
}


bool Ball::isMoving() const
{
    return m_movement != NULL;
}

void Ball::updateBall()
{

}

void Ball::setMovement(MovementHandler *handler)
{
    m_movement = handler;
}

void Ball::stopMovement()
{
    m_movement = NULL;
}

void Ball::stopMoving()
{
    if(m_movement != NULL)
        m_movement->stopMovement(this);
}

void Ball::throwBall(Vec pos, Vec dir)
{
    setPos(pos);
    setSpeed(dir.getVectWithNorm(10));
}

void Ball::handleInteraction(Entity *other)
{
    if(other == this)
        return;
    if(other->getType() == BALL)
    {
        if(((Ball*)other)->r() + r() > dist(*other, getPos()))
            collide(*this, *(Ball*)other);
    }
    else other->handleInteraction(this);
}

void Ball::bounce(Vec dir)
{
    Vec normalSpeed = getSpeed().proj(dir);
    Vec tangentSpeed = getSpeed()-normalSpeed;
    setSpeed(tangentSpeed-normalSpeed);
}

bool Ball::isInside(Vec vec) const
{
    return distSquared(getPos(), vec) < r()*r();
}
