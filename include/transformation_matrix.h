#pragma once

#include <iostream>

struct TransformationMatrix
{
	double elements[4][4] = { 0 };
	double& operator()(size_t i, size_t j);
	const double& operator()(size_t i, size_t j) const;
	TransformationMatrix transposed() const;
	void dump() const;
	static TransformationMatrix identity();
	static TransformationMatrix parallel_projection(double n);
	static TransformationMatrix one_point_projection(double d);
	static TransformationMatrix x_rotation(double angle);
	static TransformationMatrix y_rotation(double angle);
	static TransformationMatrix z_rotation(double angle);	
	static TransformationMatrix translation(double x, double y, double z);
	static TransformationMatrix rotation_around(double x, double y, double z, double angle);
};

inline double& TransformationMatrix::operator()(size_t i, size_t j)
{
	return elements[i][j];
}

inline const double& TransformationMatrix::operator()(size_t i, size_t j) const
{
	return elements[i][j];
}
