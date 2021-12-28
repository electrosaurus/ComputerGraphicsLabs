#include "polygon.h"
#include <iostream>

Polygon::Polygon(const std::vector<Point>& vertices) :
	vertices(vertices)
{ }

Segment Polygon::side(size_t index) const
{
	return Segment(vertices[index], vertices[(index + 1) % vertices.size()]);
}

void Polygon::draw(GIFPainter& gif_painter) const
{
	size_t n = vertices.size();
	for (size_t i1 = 0; i1 < n; i1++)
	{
		size_t i2 = (i1 + 1) % n;
		Segment(vertices[i1], vertices[i2]).draw(gif_painter);
	}
}

Rectangle Polygon::bounds() const
{
	Rectangle result;
	for (auto vertex : vertices)
	{
		result.min_x = std::min(result.min_x, vertex.x);
		result.max_x = std::max(result.max_x, vertex.x);
		result.min_y = std::min(result.min_y, vertex.y);
		result.max_y = std::max(result.max_y, vertex.y);
	}
	return result;
}

bool Polygon::contains(Point p, FillMode fill_mode) const
{
	size_t n = vertices.size();
	int param = 0;
	switch (fill_mode)
	{
	case EO:
		for (int i = 0; i < n; i++)
		{
			switch (side(i).ray_relation(p))
			{
			case TOUCHING:
				return true;
			case CROSS_LEFT:
			case CROSS_RIGHT:
				param = 1 - param;
				break;
			case INESSENTIAL:
				break;
			}
		}
		return param == 1;
	case NZW:
		for (int i = 0; i < n; i++)
		{
			switch (side(i).ray_relation(p))
			{
			case TOUCHING:
				return true;
			case CROSS_LEFT:
				param -= 1;
				break;
			case CROSS_RIGHT:
				param += 1;
				break;
			case INESSENTIAL:
				break;
			}
		}
		return param != 0;
	}
}

void Polygon::fill(GIFPainter& gif_painter, FillMode fill_mode) const
{
	auto bounds = this->bounds();
	for (int x = bounds.min_x; x < bounds.max_x; x++)
	{
		for (int y = bounds.min_y; y < bounds.max_y; y++)
		{
			if (contains(Point(x, y), fill_mode))
			{
				gif_painter.fill_pixel(x, y);
			}
		}
	}
}

bool Polygon::is_convex() const
{
	size_t n = vertices.size();
	bool has_left = false, has_right = false;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			switch (side(i).point_relation(vertices[j]))
			{
			case LEFT:
				has_left = true;
				break;
			case RIGHT:
				has_right = true;
				break;
			default:
				break;
			}
			if (has_left && has_right)
				return false;
		}
	}
	return true;
}

bool Polygon::is_simple() const
{
	size_t n = vertices.size();
	for (size_t i = 0; i < n; i++)
	{
		size_t lim = i == 0 ? n - 1 : n;
		for (size_t j = i + 2; j < lim; j++)
		{
			auto side_intersection = side(i).segment_intersection(side(j));
			if (side_intersection == SKEW_CROSS)
			{
				//std::cout << side(i).begin << " -> " << side(i).end << std::endl;
				//std::cout << side(j).begin << " -> " << side(j).end << std::endl;
				return false;
			}
		}
	}
	return true;
}
