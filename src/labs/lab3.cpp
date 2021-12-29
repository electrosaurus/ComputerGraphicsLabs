#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include "parallelepiped.h"

Parallelepiped process_parallelepiped(const std::string& input_filename)
{
	size_t width, height;
	double p_width, p_height, p_depth;
	Vector3 n;
	std::ifstream input(input_filename);
	if (!input)
		throw std::runtime_error("Parallelepiped input file not found");
	input >> width >> height;
	input >> p_width >> p_height >> p_depth;
	input >> Parallelepiped::draw_invisible_edges;
	input >> n.x >> n.y >> n.z;
	n = n / sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	input.close();
	Parallelepiped p(p_width, p_height, p_depth);
	p = p.transformed(TransformationMatrix::x_rotation(0.5));
	p = p.transformed(TransformationMatrix::y_rotation(0.2));
	p = p.transformed(TransformationMatrix::z_rotation(0.1));
	p = p.transformed(TransformationMatrix::one_point_projection(1000).transposed());
	GIFPainter gif_painter(width, height);
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(0, 0, 0);
	//Parallelepiped::draw_invisible_edges = false;
	p.draw(gif_painter);
	gif_painter.save("output/lab3/parallelepiped_one_point_projection.gif");
	gif_painter.clear();

	p = Parallelepiped(p_width, p_height, p_depth);
	p = p.transformed(TransformationMatrix::x_rotation(0.5));
	p = p.transformed(TransformationMatrix::y_rotation(0.2));
	p = p.transformed(TransformationMatrix::z_rotation(0.1));
	p = p.transformed(TransformationMatrix::parallel_projection(1000).transposed());
	gif_painter.color = Color::rgb(255, 255, 200);
	gif_painter.add_frame(100);
	gif_painter.color = Color::rgb(0, 0, 0);
	p.draw(gif_painter);
	gif_painter.save("output/lab3/parallelepiped_parallel_projection.gif");
	gif_painter.clear();
	
	p = Parallelepiped(p_width, p_height, p_depth);
	for (size_t i = 0; i < 100; i++)
	{
		Parallelepiped pt = p.transformed(TransformationMatrix::rotation_around(n.x, n.y, n.z, i / 10.0));
		//Parallelepiped pt = p.transformed(TransformationMatrix::x_rotation(i * 0.01));
		//pt = pt.transformed(TransformationMatrix::y_rotation(i * 0.02));
		//pt = pt.transformed(TransformationMatrix::z_rotation(i * 0.03));
		//pt = pt.transformed(TransformationMatrix::one_point_projection(1000).transposed());
		gif_painter.color = Color::rgb(255, 255, 200);
		gif_painter.add_frame(10);
		gif_painter.color = Color::rgb(0, 0, 0);
		pt.draw(gif_painter);
	}
	gif_painter.save("output/lab3/parallelepiped_rotation.gif");
	gif_painter.clear();

	return p;
}


int main(int argc, char* argv[])
{
	auto p = process_parallelepiped(argv[1]);

	return 0;
}
