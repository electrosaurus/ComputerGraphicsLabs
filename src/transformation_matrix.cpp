#include "transformation_matrix.h"
#include <cmath>

TransformationMatrix TransformationMatrix::transposed() const
{
	TransformationMatrix t;
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			t(i, j) = (*this)(j, i);
	return t;
}

TransformationMatrix TransformationMatrix::identity()
{
	TransformationMatrix t;
	t(0, 0) = 1;
	t(1, 1) = 1;
	t(2, 2) = 1;
	t(3, 3) = 1;
	return t;
}

TransformationMatrix TransformationMatrix::parallel_projection(double n)
{
	TransformationMatrix t;
	t(0, 0) = 1;
	t(1, 1) = 1;
	t(3, 2) = n;
	t(3, 3) = 1;
	return t;
}

TransformationMatrix TransformationMatrix::one_point_projection(double d)
{
	auto t = TransformationMatrix::identity();
	t(2, 3) = 1 / d;
	return t;
}

TransformationMatrix TransformationMatrix::translation(double x, double y, double z)
{
	TransformationMatrix t = TransformationMatrix::identity();
	t(3, 0) = x;
	t(3, 1) = y;
	t(3, 2) = z;
	return t;
}

TransformationMatrix TransformationMatrix::x_rotation(double angle)
{
	TransformationMatrix t = TransformationMatrix::identity();
	t(1, 1) = cos(angle);
	t(1, 2) = sin(angle);
	t(2, 1) = -sin(angle);
	t(2, 2) = cos(angle);
	return t;
}

TransformationMatrix TransformationMatrix::y_rotation(double angle)
{
	TransformationMatrix t = TransformationMatrix::identity();
	t(0, 0) = cos(angle);
	t(0, 2) = -sin(angle);
	t(2, 0) = sin(angle);
	t(2, 2) = cos(angle);
	return t;
}

TransformationMatrix TransformationMatrix::z_rotation(double angle)
{
	TransformationMatrix t = TransformationMatrix::identity();
	t(0, 0) = cos(angle);
	t(0, 1) = sin(angle);
	t(1, 0) = -sin(angle);
	t(1, 1) = cos(angle);
	return t;
}

TransformationMatrix TransformationMatrix::rotation_around(double x, double y, double z, double angle)
{
	TransformationMatrix t = TransformationMatrix::identity();
	t(0, 0) = cos(angle) + x * x * (1 - cos(angle));
	t(0, 1) = x * y * (1 - cos(angle)) + z * sin(angle);
	t(0, 2) = x * z * (1 - cos(angle)) - y * sin(angle);
	t(1, 0) = x * y * (1 - cos(angle)) - z * sin(angle);
	t(1, 1) = cos(angle) + y * y * (1 - cos(angle));
	t(1, 2) = y * z * (1 - cos(angle)) + x * sin(angle);
	t(2, 0) = x * z * (1 - cos(angle)) + y * sin(angle);
	t(2, 1) = y * z * (1 - cos(angle)) - x * sin(angle);
	t(2, 2) = cos(angle) + z * z * (1 - cos(angle));
	return t;
}

void TransformationMatrix::dump() const
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << (*this)(i, j) << " ";
		}
		std::cout << std::endl;
	}
}
