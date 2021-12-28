#pragma once

#include <vector>
#include "figure.h"
#include "segment.h"
#include "rectangle.h"

enum FillMode { EO, NZW };

class Polygon : public Figure
{
public:
	std::vector<Point> vertices;

	Polygon(const std::vector<Point>& vertices);
	Segment side(size_t index) const;

	void draw(GIFPainter& gif_painter) const override;
	Rectangle bounds() const;
	bool contains(Point p, FillMode fill_mode = EO) const;
	void fill(GIFPainter& gif_painter, FillMode fill_mode = EO) const;
	bool is_convex() const;
	bool is_simple() const;
};
