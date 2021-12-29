#pragma once

#include "bezier_curve.h"

class CompositeBezierCurve : public Figure
{
public:
	std::vector<Point> points;
	size_t order;
	std::vector<BezierCurve> subcurves;

	template <class TIterator>
	CompositeBezierCurve(size_t order, TIterator begin, TIterator end);

	Point point(double t) const;
	void draw(GIFPainter& gif_painter) const override;
};

template <class TIterator>
CompositeBezierCurve::CompositeBezierCurve(size_t order, TIterator begin, TIterator end) : points(begin, end)
{
	size_t k = (points.size() - 1) / order;
	for (size_t i = 0; i < k; i++)
	{
		subcurves.push_back(BezierCurve(points.begin() + i * order, points.begin() + (i + 1) * order + 1));
	}
}
