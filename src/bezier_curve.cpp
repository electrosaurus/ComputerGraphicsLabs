#include "bezier_curve.h"
#include "segment.h"

unsigned long int fac(int n)
{
    return n == 0 || n == 1 ? 1 : n * fac(n - 1);
}

size_t BezierCurve::order() const
{
	return points.size() - 1;
}

Point BezierCurve::point(double t) const
{
	size_t n = order();
	Point p;
	for (size_t i = 0; i <= n; i++)
		p = p + polynomial_coeffs[i] * pow(t, i);
	return p;
}

void BezierCurve::draw(GIFPainter& gif_painter) const
{
	size_t n = BezierCurve::draw_segments + 1;
	for (size_t i = 0; i < BezierCurve::draw_segments; i++)
	{
		Segment s(point((double)i / n), point((double)(i + 1) / n));
		s.draw(gif_painter);
	}
}

size_t BezierCurve::draw_segments = 100;
