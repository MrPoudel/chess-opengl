#ifndef POINTS_H
#define POINTS_H

template<typename T>
struct Point3D
{
	T x;
	T y;
	T z;
};

template<typename T>
struct Point2D
{
	T x;
	T y;
};

template<typename T>
static Point2D<T> createPoint(T x, T y) {
	Point2D<T> tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}
#endif