#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

#include <SFML/Graphics.hpp>
using namespace sf;
class Vec
{
	public:
	Vec();
	Vec(const Vec &vec);
	Vec(double x, double y);
	Vec(sf::Vector2f vec);

	virtual ~Vec();

	double normSquared() const;
	double norm() const;
	double angle() const;

	bool insideRect(Vec pos, Vec dim);

	void operator+=(Vec vec);
	void operator-=(Vec vec);
	void operator*=(float f);
	void operator/=(float f);

	operator Vector2f() const;
	void operator=(sf::Vector2f v);

	Vec proj(Vec  vec) const;
	Vec getVectWithNorm(float norm) const;
	Vec normalize() const;

	Vec ortho() const;

	Vec operator-() const;

	Vec screenToWorld() const;
	Vec worldToScreen() const;

	static void setRender(RenderTarget *render);

	double x, y;

    private:
	static RenderTarget* m_render;
};

double vec(Vec v1, Vec  v2);
Vec operator+(Vec v1, Vec  v2);
Vec operator-(Vec v1, Vec  v2);
double operator*(Vec v1, Vec v2);
Vec operator*(double f, Vec v2);
Vec operator*(Vec v2, double f);
Vec operator/(Vec v, double f);

bool operator==(const Vec &v1, const Vec &v2);
bool operator!=(const Vec &v1, const Vec &v2);

double dist(Vec v1, Vec v2);
double distSquared(Vec v1, Vec v2);

#endif // VEC_H_INCLUDED
