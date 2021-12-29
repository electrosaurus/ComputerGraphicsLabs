#pragma once

#include "figure.h"
#include <cmath>

class BezierCurve : public Figure
{
public:
	std::vector<Point> points;
	std::vector<Point> polynomial_coeffs;
	static size_t draw_segments;

	template <class TIterator>
	BezierCurve(TIterator begin, TIterator end);

	Point point(double t) const;
	size_t order() const;
	void draw(GIFPainter& gif_painter) const override;
};

unsigned long int fac(int n);

template <class TIterator>
BezierCurve::BezierCurve(TIterator begin, TIterator end) : points(begin, end)
{
	size_t n = order();
	polynomial_coeffs.resize(n + 1);
	for (int j = 0; j <= n; j++)
	{
		double q = 1;
		for (int m = 0; m <= j - 1; m++)
			q *= (n - m);
		Point w;
		for (int i = 0; i <= j; i++)
			w = w + ((i + j) % 2 ? -1 : 1) * points[i] / ((double)fac(i) * (double)fac(j - i));
		polynomial_coeffs[j] = q * w;
	}
}
