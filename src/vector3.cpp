#include "vector3.h"

Vector3::Vector3(): x(0), y(0), z(0)
{ }

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z)
{ }

Point Vector3::xy() const
{
	return Point(x, y);
}

Vector3 operator/(Vector3 v, double t)
{
	return Vector3(v.x / t, v.y / t, v.z / t);
}

Vector3 operator-(Vector3 a, Vector3 b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 Vector3::transformed(const TransformationMatrix& t) const
{
	return Vector3(
		x * t(0, 0) + y * t(0, 1) + z * t(0, 2) + t(0, 3),
		x * t(1, 0) + y * t(1, 1) + z * t(1, 2) + t(1, 3),
		x * t(2, 0) + y * t(2, 1) + z * t(2, 2) + t(2, 3)
	) / (x * t(3, 0) + y * t(3, 1) + z * t(3, 2) + t(3, 3));
}

Vector3 vector_product(Vector3 a, Vector3 b)
{
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.x * b.z - a.z * b.x,
		a.x * b.y - a.y * b.x
	);
}
