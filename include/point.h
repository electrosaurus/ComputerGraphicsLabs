#pragma once

struct Point
{
	double x, y;

	Point();
	Point(double x, double y);
};

inline Point operator+(Point a, Point b)
{
	return Point(a.x + b.x, a.y + b.y);
}

inline Point operator-(Point a, Point b)
{
	return Point(a.x - b.x, a.y - b.y);
}

inline Point operator*(Point p, double q)
{
	return Point(p.x * q, p.y * q);
}

inline Point operator*(double q, Point p)
{
	return Point(q * p.x, q * p.y);
}

inline Point operator/(Point p, double q)
{
	return Point(p.x / q, p.y / q);
}
