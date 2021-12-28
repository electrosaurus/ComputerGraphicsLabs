#include <fstream>
#include <iostream>
#include <string>
#include "bezier_curve_3.h"
#include "segment.h"
#include "rectangle.h"

BezierCurve3 process_bezier_curve_3(const std::string& input_filename)
{
	size_t width, height;
	Point p1, p2, p3, p4;
	std::ifstream input(input_filename);
	if (!input)
		throw std::runtime_error("Bezier curve input file not found");
	input >> width >> height;
	input >> p1.x >> p1.y;
	input >> p2.x >> p2.y;
	input >> p3.x >> p3.y;
	input >> p4.x >> p4.y;
	input.close();
	BezierCurve3 bc3(p1, p2, p3, p4);
	GIFPainter gif_painter(width, height);
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(0, 0, 0);
	bc3.draw(gif_painter);
	gif_painter.save("output/lab2/bezier_curve_3.gif");
	return bc3;
}

Segment process_segment_clipping(const std::string& input_filename)
{
	size_t width, height;
	Point begin, end, bottom_left_bound, top_right_bound;
	std::ifstream input(input_filename);
	if (!input)
		throw std::runtime_error("Clipping input file not found");
	input >> width >> height;
	input >> begin.x >> begin.y;
	input >> end.x >> end.y;
	input >> bottom_left_bound.x >> bottom_left_bound.y;
	input >> top_right_bound.x >> top_right_bound.y;
	input.close();
	Segment segment(begin, end);
	Rectangle bounds(bottom_left_bound, top_right_bound);
	GIFPainter gif_painter(width, height);
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(200, 0, 0);
	segment.draw(gif_painter);
	gif_painter.color = Color::rgb(0, 200, 0);
	bounds.draw(gif_painter);
	segment.clip(bounds);
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(0, 0, 200);
	segment.draw(gif_painter);
	gif_painter.color = Color::rgb(0, 200, 0);
	bounds.draw(gif_painter);
	gif_painter.save("output/lab2/segment_clipping.gif");
	return segment;
}

int main(int argc, char* argv[])
{
	auto bc3 = process_bezier_curve_3(argv[1]);
	auto segment = process_segment_clipping(argv[2]);

	return 0;
}
