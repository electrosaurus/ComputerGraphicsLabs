#include <fstream>
#include <iostream>
#include <string>
#include "segment.h"
#include "polygon.h"

Segment process_segment(const std::string& input_filename)
{
	size_t width, height;
	Point begin, end;
	std::ifstream input(input_filename);
	if (!input)
		throw std::runtime_error("Line segment input file not found");
	input >> width >> height;
	input >> begin.x >> begin.y;
	input >> end.x >> end.y;
	input.close();
	Segment segment(begin, end);
	GIFPainter gif_painter(width, height);
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(0, 0, 0);
	segment.draw(gif_painter);
	gif_painter.save("output/lab1/segment.gif");
	return segment;
}

Polygon process_polygon(const std::string& input_filename)
{
	size_t width, height;
	std::vector<Point> vertices;
	std::ifstream input(input_filename);
	if (!input)
		throw std::runtime_error("Polygon input file not found");
	input >> width >> height;
	while (!input.eof())
	{
		Point vertex;
		input >> vertex.x >> vertex.y;
		vertices.push_back(vertex);
	}
	input.close();
	Polygon polygon(vertices);
	GIFPainter gif_painter(width, height);
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(0, 0, 0);
	polygon.draw(gif_painter);
	gif_painter.save("output/lab1/polygon.gif");
	gif_painter.clear();
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(255, 50, 50);
	polygon.fill(gif_painter, EO);
	gif_painter.save("output/lab1/polygon_fill_eo.gif");
	gif_painter.clear();
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(50, 50, 255);
	polygon.fill(gif_painter, NZW);
	gif_painter.save("output/lab1/polygon_fill_nzw.gif");
	return polygon;
}

int main(int argc, char* argv[])
{
	auto segment = process_segment(argv[1]);
	auto polygon = process_polygon(argv[2]);

	std::cout << "The polygon is " << (polygon.is_convex() ? "convex" : "concave") <<
		" and " << (polygon.is_simple() ? "simple" : "complex") << "." << std::endl;

	return 0;
}
