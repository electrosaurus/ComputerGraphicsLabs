#include "composite_bezier_curve.h"
#include "segment.h"

void CompositeBezierCurve::draw(GIFPainter& gif_painter) const
{
	for (auto& subcurve : subcurves)
		subcurve.draw(gif_painter);
}
