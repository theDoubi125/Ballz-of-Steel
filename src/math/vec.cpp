#include <cmath>
#include "../math/vec.h"

sf::RenderTarget* Vec::m_render(NULL);

void Vec::setRender(sf::RenderTarget *render)
{
    m_render = render;
}

Vec::Vec() : x(0), y(0)
{

}

Vec::Vec(const Vec &vec) : x(vec.x), y(vec.y)
{

}

Vec::Vec(double x, double y) : x(x), y(y)
{

}

Vec::Vec(sf::Vector2f vec) : x(vec.x), y(vec.y)
{

}

Vec::~Vec()
{

}

double Vec::normSquared() const
{
	return x*x+y*y;
}

double Vec::norm() const
{
	return sqrt(x*x+y*y);
}

double Vec::angle() const
{
	return -(x>=0?0:3.14) + atan(y/x);
}

Vec operator+(Vec v1, Vec v2)
{
	return Vec(v1.x+v2.x, v1.y+v2.y);
}

Vec operator-(Vec v1, Vec v2)
{
	return Vec(v1.x-v2.x, v1.y-v2.y);
}

double operator*(Vec v1, Vec v2)
{
	return v1.x*v2.x+v1.y*v2.y;
}

double vec(Vec v1, Vec v2)
{
	return v1.x*v2.y-v1.y*v2.x;
}

Vec operator*(Vec v, double f)
{
	return Vec(v.x*f, v.y*f);
}

Vec operator*(double f, Vec v)
{
	return Vec(v.x*f, v.y*f);
}

Vec operator/(Vec v, double f)
{
	return Vec(v.x/f, v.y/f);
}

void Vec::operator+=(Vec v)
{
	x += v.x;
	y += v.y;
}

void Vec::operator-=(Vec v)
{
	x -= v.x;
	y -= v.y;
}

void Vec::operator*=(float f)
{
	x*=f;
	y*=f;
}

void Vec::operator/=(float f)
{
	x/=f;
	y/=f;
}

bool operator==(const Vec &v1, const Vec &v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(const Vec &v1, const Vec &v2)
{
    return v1.x != v2.x || v1.y != v2.y;
}

Vec Vec::proj(Vec vec) const
{
	return vec.getVectWithNorm(((*this)*vec))/vec.norm();
}

Vec Vec::getVectWithNorm(float f) const
{
	double n = norm();
	return Vec(x*f/n, y*f/n);
}

Vec Vec::normalize() const
{
	double n = norm();
	return Vec(x/n, y/n);
}

Vec Vec::ortho() const
{
	return Vec(y, -x);
}

Vec Vec::operator-() const
{
	return Vec(-x, -y);
}

double dist(Vec v1, Vec v2)
{
    return (v2-v1).norm();
}

double distSquared(Vec v1, Vec v2)
{
    return (v2-v1).normSquared();
}

Vec Vec::screenToWorld() const
{
    sf::Vector2i pos = sf::Vector2i((int)x, (int)y);
    return m_render->mapPixelToCoords(pos);
}

Vec Vec::worldToScreen() const
{
    sf::Vector2i pos = m_render->mapCoordsToPixel(*(sf::Vector2f*)this);
    return Vec(pos.x, pos.y);
}

Vec::operator sf::Vector2f() const
{
    return sf::Vector2f(x, y);
}

bool Vec::insideRect(Vec pos, Vec dim)
{
    return x >= pos.x && x < (pos+dim).x && y >= pos.y && y < (pos+dim).y;
}
