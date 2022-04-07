#pragma once

/**
 * @brief Struktura reprezentująca punkt w przestrzeni trójwymiarowej.
 */
struct Point
{
	Point() = default;
	Point(double vx, double vy, double vz) : x(vx), y(vy), z(vz) {}
	double x, y, z;
};

/**
 * @brief Struktura reprezentująca linię w przestrzeni trójwymiarowej.
 */
struct Segment {
	Point begin, end;
	Segment(Point _begin, Point _end) : begin(_begin), end(_end) {}
};
