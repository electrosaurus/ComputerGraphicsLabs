#include <limits>
#include "rectangle.h"
#include "segment.h"

Rectangle::Rectangle() :
	min_x(std::numeric_limits<double>::max()),
	max_x(0.0),
	min_y(std::numeric_limits<double>::max()),
	max_y(0.0)
{ }

Rectangle::Rectangle(double min_x, double max_x, double min_y, double max_y) :
	min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y)
{ }

Rectangle::Rectangle(Point bottom_left, Point top_right) :
	min_x(bottom_left.x), max_x(top_right.x), min_y(bottom_left.y), max_y(top_right.y)
{ }

unsigned char Rectangle::point_code(Point point) const
{
    unsigned char code = Rectangle::INSIDE;
    if (point.x < min_x)
        code |= Rectangle::LEFT;
    else if (point.x > max_x)
        code |= Rectangle::RIGHT;
    if (point.y < min_y)
        code |= Rectangle::BOTTOM;
    else if (point.y > max_y)
        code |= Rectangle::TOP;
    return code;
}

void Rectangle::draw(GIFPainter& gif_painter) const
{
	Segment(Point(min_x, min_y), Point(min_x, max_y)).draw(gif_painter);
	Segment(Point(min_x, max_y), Point(max_x, max_y)).draw(gif_painter);
	Segment(Point(max_x, max_y), Point(max_x, min_y)).draw(gif_painter);
	Segment(Point(max_x, min_y), Point(min_x, min_y)).draw(gif_painter);
}
