#include "parallelepiped.h"

bool Parallelepiped::draw_invisible_edges = false;

const size_t Parallelepiped::SIDE_EDGES[6][4] = {
	{ 0, 1, 2, 3 }, // Bottom
	{ 7, 6, 5, 4 }, // Top
	{ 0, 8, 4, 9 }, // Left
	{ 2, 10, 6, 11 }, // Right
	{ 3, 11, 7, 8 }, // Front
	{ 1, 9, 5, 10 } // Back
};

const size_t Parallelepiped::EDGE_VERTICES[12][2] = {
	{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, // Floor
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, // Ceiling
	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } // Walls
};

Parallelepiped::Parallelepiped(double width, double height, double depth)
{
	vertices[0] = Vector3(-width / 2,  -height / 2, -depth / 2);
	vertices[1] = Vector3(-width / 2,  -height / 2, +depth / 2);
	vertices[2] = Vector3(+width / 2,  -height / 2, +depth / 2);
	vertices[3] = Vector3(+width / 2,  -height / 2, -depth / 2);
	vertices[4] = Vector3(-width / 2,  +height / 2, -depth / 2);
	vertices[5] = Vector3(-width / 2,  +height / 2, +depth / 2);
	vertices[6] = Vector3(+width / 2,  +height / 2, +depth / 2);
	vertices[7] = Vector3(+width / 2,  +height / 2, -depth / 2);
}

std::array<Vector3, 2> Parallelepiped::edge_vertices(size_t i) const
{
	return {
		vertices[Parallelepiped::EDGE_VERTICES[i][0]],
		vertices[Parallelepiped::EDGE_VERTICES[i][1]]
	};
}

Parallelepiped Parallelepiped::transformed(const TransformationMatrix& t) const
{
	Parallelepiped pt(*this);
	for (size_t i = 0; i < 8; i++)
	{
		pt.vertices[i] = vertices[i].transformed(t);
	}
	return pt;
}

void Parallelepiped::draw(GIFPainter& gif_painter) const
{
	auto t3 = TransformationMatrix::translation(gif_painter.width / 2, gif_painter.height / 2, 0).transposed();
	auto pt = transformed(t3);
	if (Parallelepiped::draw_invisible_edges)
	{
		for (size_t i = 0; i < 12; i++)
		{
			Segment(
				pt.vertices[Parallelepiped::EDGE_VERTICES[i][0]].xy(),
				pt.vertices[Parallelepiped::EDGE_VERTICES[i][1]].xy()
			).draw(gif_painter);
		}
	}
	else
	{
		for (size_t i = 0; i < 6; i++)
		{
			auto side_edges = Parallelepiped::SIDE_EDGES[i];
			auto a_vertices = pt.edge_vertices(side_edges[0]);
			auto b_vertices = pt.edge_vertices(side_edges[3]);
			auto a = a_vertices[1] - a_vertices[0];
			auto b = b_vertices[1] - b_vertices[0];
			auto norm = vector_product(a, b);
			if (norm.z <= 0)
			{
				for (size_t j = 0; j < 4; j++)
				{
					auto vertices = pt.edge_vertices(side_edges[j]);
					Segment(vertices[0].xy(), vertices[1].xy()).draw(gif_painter);
				}
			}
		}
	}
}
