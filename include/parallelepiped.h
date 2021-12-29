#pragma once

#include <array>
#include "figure.h"
#include "vector3.h"
#include "segment.h"
#include "transformation_matrix.h"

class Parallelepiped : public Figure
{
private:
	static const size_t SIDE_EDGES[6][4];
	static const size_t EDGE_VERTICES[12][2];

public:
	static bool draw_invisible_edges;
	Vector3 vertices[8];

	Parallelepiped(double width = 1, double height = 1, double depth = 1);
	std::array<Vector3, 2> edge_vertices(size_t i) const;


	void draw(GIFPainter& gif_painter) const override;
	Parallelepiped transformed(const TransformationMatrix& t) const;
};
