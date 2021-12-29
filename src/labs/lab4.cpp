#include <fstream>
#include <iostream>
#include <string>
#include "gif_painter.h"
#include "bitmap_image.h"
#include "composite_bezier_curve.h"

void fill_image(const std::string& image_filename)
{
	bitmap_image image(image_filename);
	if (!image)
	{
		throw std::runtime_error("Image not found");
   	}
	GIFPainter gif_painter(image.width(), image.height());
	gif_painter.add_frame(100);
	gif_painter.inverse_y = false;
	std::cout << image.width() << " " << image.height() << std::endl;
	for (size_t y = 0; y < image.height(); y++)
	{
		for (size_t x = 0; x < image.width(); x++)
		{
			//std::cout << x << " " << y << std::endl;
			auto color = image.get_pixel(x, y);
			gif_painter.color.r = color.red;
			gif_painter.color.g = color.green;
			gif_painter.color.b = color.blue;
			//std::cout << "here" << std::endl;
			gif_painter.fill_pixel(x, y);
			//std::cout << "op" << std::endl;
		}
	}
	gif_painter.color = Color::rgb(255, 0, 0);
	gif_painter.flood_fill(100, 100);
	gif_painter.save("output/lab4/filled_image.gif");
}

CompositeBezierCurve process_composite_besier_curve(const std::string& input_filename)
{
	size_t width, height;
	size_t order;
	std::vector<Point> points;
	std::ifstream input(input_filename);
	if (!input)
		throw std::runtime_error("Polygon input file not found");
	input >> width >> height;
	input >> order;
	while (!input.eof())
	{
		Point vertex;
		input >> vertex.x >> vertex.y;
		points.push_back(vertex);
	}
	input.close();
	GIFPainter gif_painter(width, height);
	gif_painter.color = Color::rgb(0, 0, 0);
	gif_painter.add_frame(100);
	CompositeBezierCurve cbc(order, points.begin(), points.end());
	gif_painter.color = Color::rgb(255, 255, 255);
	cbc.draw(gif_painter);
	gif_painter.save("output/lab4/composite_besier_curve.gif");
	return cbc;
}


int main(int argc, char* argv[])
{
	fill_image(argv[1]);
	process_composite_besier_curve(argv[2]);

	return 0;
}
