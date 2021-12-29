#pragma once

#include "point.h"
#include "transformation_matrix.h"

struct Vector3
{
	double x, y, z;

	Vector3();
	Vector3(double x, double y, double z);
	Point xy() const;
	Vector3 transformed(const TransformationMatrix& t) const;
};

Vector3 operator/(Vector3 v, double t);

Vector3 operator-(Vector3 a, Vector3 b);

Vector3 vector_product(Vector3 a, Vector3 b);
