/**
 * @file Point.hpp
 * @brief The header file for the Point class.
 */
#ifndef POINT_HPP
#define POINT_HPP

#include "HalfEdge.hpp"

/**
 * @brief The Point class represents a point in 2D space.
 */
class Point
{
public:
/**
 * @brief The x coordinate of the point.
 */
    double x;
/**
 * @brief The y coordinate of the point.
 */
    double y;

/**
 * @brief A pointer to the half-edge incident to the point.
 */
    HalfEdge* incident_edge;

/**
 * @brief Constructs a point at the origin.
 */
    Point(double a = 0, double b = 0)
    {
        x = a;
        y = b;
        incident_edge = nullptr;
    }
};

#endif