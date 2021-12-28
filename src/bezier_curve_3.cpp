#include "bezier_curve_3.h"
#include "segment.h"

BezierCurve3::BezierCurve3(Point p1, Point p2, Point p3, Point p4) :
	p1(p1), p2(p2), p3(p3), p4(p4)
{ }

Point BezierCurve3::point(double t) const
{
	double q = 1 - t;
	return q * q * q * p1 + 3 * t * q * q * p2 + 3 * t * t * q * p3 + t * t * t * p4;
}

void BezierCurve3::draw(GIFPainter& gif_painter) const
{
	size_t n = BezierCurve3::draw_segments + 1;
	for (size_t i = 0; i < BezierCurve3::draw_segments; i++)
	{
		Segment s(point((double)i / n), point((double)(i + 1) / n));
		s.draw(gif_painter);
	}
}

size_t BezierCurve3::draw_segments = 100;
