#pragma once

#include "figure.h"
#include "rectangle.h"

enum PointSegmentRelation
{
	LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, BEGIN, END
};

enum SegmentsIntersection
{
	SAME, PARALLEL, SKEW, SKEW_CROSS, SKEW_NO_CROSS
};

enum SegmentRayRelation
{
	TOUCHING, CROSS_LEFT, CROSS_RIGHT, INESSENTIAL
};

class Segment : public Figure
{
public:
	Point begin, end;

	Segment(Point begin, Point end);
	void draw(GIFPainter& gif_painter) const override;
	PointSegmentRelation point_relation(Point p) const;
	SegmentsIntersection line_intersection(Segment s, double *t = NULL) const;
	SegmentsIntersection segment_intersection(Segment s, double *t1 = NULL, double *t2 = NULL) const;
	SegmentRayRelation ray_relation(Point origin) const;
	bool clip(const Rectangle& bounds);
};
