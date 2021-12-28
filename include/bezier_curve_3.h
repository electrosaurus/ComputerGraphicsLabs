#pragma once

#include "figure.h"

class BezierCurve3 : public Figure
{
public:
	Point p1, p2, p3, p4;
	static size_t draw_segments;

	BezierCurve3(Point p1, Point p2, Point p3, Point p4);
	Point point(double t) const;
	void draw(GIFPainter& gif_painter) const override;
};
