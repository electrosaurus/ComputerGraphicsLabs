#pragma once

#include "point.h"
#include "figure.h"

class Rectangle : public Figure
{
public:
	static const unsigned char INSIDE = 0;
	static const unsigned char LEFT = 1;
	static const unsigned char RIGHT = 2;
	static const unsigned char BOTTOM = 4;
	static const unsigned char TOP = 8;

	double min_x, max_x, min_y, max_y;

	Rectangle();
	Rectangle(double min_x, double max_x, double min_y, double max_y);
	Rectangle(Point bottom_left, Point top_right);
	unsigned char point_code(Point point) const;
	void draw(GIFPainter& gif_painter) const;
};
