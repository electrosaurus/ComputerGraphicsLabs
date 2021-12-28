#include "segment.h"

Segment::Segment(Point begin, Point end) :
	begin(begin), end(end)
{ }

PointSegmentRelation Segment::point_relation(Point p) const
{
	int ax = end.x - begin.x;
	int ay = end.y - begin.y;
	int bx = p.x - begin.x;
	int by = p.y - begin.y;
	int s = ax * by - bx * ay;
	if (s > 0)
		return LEFT;
	if (s < 0)
		return RIGHT;
	if ((ax * bx < 0) || (ay * by < 0))
		return BEHIND;
	if ((ax * ax + ay * ay) < (bx * bx + by * by))
		return BEYOND;
	if (begin.x == p.x && begin.y == p.y)
		return BEGIN;
	if (end.x == p.x && end.y == p.y)
		return END;
	return BETWEEN;
}

SegmentsIntersection Segment::line_intersection(Segment s, double *t) const
{
	int nx = s.end.y - s.begin.y;
	int ny = s.begin.x - s.end.x;
	PointSegmentRelation point_segment_relation;
	double denom = nx * (end.x - begin.x) + ny * (end.y - begin.y);
	if (denom == 0)
	{
		auto begin_s_relation = s.point_relation(begin);
		if (begin_s_relation == LEFT || begin_s_relation == RIGHT)
			return PARALLEL;
		else
			return SAME;
	}
	if (t)
	{
		double num = nx * (begin.x - s.begin.x) + ny * (begin.y - s.begin.y);
		*t= -num / denom;
	}
	return SKEW;
}

SegmentsIntersection Segment::segment_intersection(Segment s, double *t1, double *t2) const
{
	double tab, tcd;
	auto line_intersection = this->line_intersection(s, &tab);
	if (line_intersection == SAME || line_intersection == PARALLEL)
		return line_intersection;
	if (tab < 0 || tab > 1)
		return SKEW_NO_CROSS;
	s.line_intersection(*this, &tcd);
	if (tcd < 0 || tcd > 1)
		return SKEW_NO_CROSS;
	if (t1)
		*t1 = tab;
	if (t2)
		*t2 = tcd;
	return SKEW_CROSS;
}

SegmentRayRelation Segment::ray_relation(Point origin) const
{
	switch (point_relation(origin))
	{
	case LEFT:
		return origin.y > begin.y && origin.y <= end.y ? CROSS_LEFT : INESSENTIAL;
	case RIGHT:
		return origin.y > end.y && origin.y <= begin.y ? CROSS_RIGHT : INESSENTIAL;
	case BETWEEN:
	case BEGIN:
	case END:
		return TOUCHING;
	default:
		return INESSENTIAL;
	}
}

void Segment::draw(GIFPainter& gif_painter) const
{
	Point pos = begin;
	int dx = end.x - begin.x;
	int dy = end.y - begin.y;
	int ix, iy;
	int e;
	if (dx > 0)
		ix = 1;
	else if (dx < 0)
	{
		ix = -1;
		dx = -dx;
	}
	else
		ix = 0;
	if (dy > 0)
		iy = 1;
	else if (dy < 0)
	{
		iy = -1;
		dy = -dy;
	}
	else
		iy = 0;
	if (dx >= dy)
	{
		e = 2 * dy - dx;
		if (iy >= 0)
		{
			for (int i = 0; i <= dx; i++) {
				gif_painter.fill_pixel(pos.x, pos.y);
				if (e >= 0) {
					pos.y += iy;
					e -= 2 * dx;
				}
				pos.x += ix;
				e += dy * 2;
			}
		}
		else
		{
			for (int i = 0; i <= dx; i++) {
				gif_painter.fill_pixel(pos.x, pos.y);
				if (e > 0)
				{
					pos.y += iy;
					e -= 2 * dx;
				}
				pos.x += ix;
				e += dy * 2;
			}
		}
	}
	else
	{
		e = 2 * dx - dy;
		if (ix >= 0)
		{
			for(int i = 0; i <= dy; i++) {
				gif_painter.fill_pixel(pos.x, pos.y);
				if (e >= 0) {
					pos.x += ix;
					e -= 2 * dy;
				}
				pos.y += iy;
				e += dx * 2;
			}
		}
		else
		{
			for (int i = 0; i <= dy; i++) {
				gif_painter.fill_pixel(pos.x, pos.y);
				if (e > 0)
				{
					pos.x += ix;
					e -= 2 * dy;
				}
				pos.y += iy;
				e += dx * 2;
			}
		}
	}
}



bool Segment::clip(const Rectangle& bounds)
{
    auto code1 = bounds.point_code(begin);
    auto code2 = bounds.point_code(end);
  
    bool accept = false;
  
    while (true) {
        if (code1 == 0 && code2 == 0)
		{
            accept = true;
            break;
        }
        else if (code1 & code2)
		{
            break;
        }
        else
		{
            auto code_out = code1 != 0 ? code1 : code2;
            Point p;
            if (code_out & Rectangle::TOP)
			{
                p.x = begin.x + (end.x - begin.x) * (bounds.max_y - begin.y) / (end.y - begin.y);
                p.y = bounds.max_y;
            }
            else if (code_out & Rectangle::BOTTOM)
			{
                p.x = begin.x + (end.x - begin.x) * (bounds.min_y - begin.y) / (end.y - begin.y);
                p.y = bounds.min_y;
            }
            else if (code_out & Rectangle::RIGHT)
			{
                p.y = begin.y + (end.y - begin.y) * (bounds.max_x - begin.x) / (end.x - begin.x);
                p.x = bounds.max_x;
            }
            else if (code_out & Rectangle::LEFT)
			{
                p.y = begin.y + (end.y - begin.y) * (bounds.min_x - begin.x) / (end.x - begin.x);
                p.x = bounds.min_x;
            }
  
            if (code_out == code1)
			{
                begin = p;
                code1 = bounds.point_code(begin);
            }
            else
			{
				end = p;
                code2 = bounds.point_code(end);
            }
        }
    }
    return accept;
}
