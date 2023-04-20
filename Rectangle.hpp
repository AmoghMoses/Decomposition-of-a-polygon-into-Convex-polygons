/**
 * @file Rectangle.hpp
 * @brief Defines the Rectangle class used for geometric computations.
 */

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "Point.hpp"


/**
 * @brief The Rectangle class represents a rectangle in 2D space.
 */

class Rectangle
{
public:
    /**
     * @brief The maximum x coordinate of the rectangle.
     */
    double x_max;
    
    /**
     * @brief The maximum y coordinate of the rectangle.
     */
    double y_max;
    
    /**
     * @brief The minimum x coordinate of the rectangle.
     */
    double x_min;
    
    /**
     * @brief The minimum y coordinate of the rectangle.
     */
    double y_min;

    /**
     * @brief Constructs an empty rectangle.
     */

    Rectangle();
    /**
     * @brief Sets the limits of the rectangle to include a given point.
     * @param p A pointer to the point to include.
     */
    void setLimit(Point *p);
    /**
     * @brief It checks if the given point p is inside the rectangle.
     * @param p A pointer to the point to be checked.
     */
    bool checkInside(Point *p);    
};

/**
 * @brief Constructs an empty rectangle.
 */
Rectangle::Rectangle()
{
    x_max = INT_MIN;
    y_max = INT_MIN;
    x_min = INT_MAX;
    y_min = INT_MAX;
}

/**
 * @brief Sets the limits of the rectangle to include a given point.
 * @param p A pointer to the point to include.
 */
void Rectangle::setLimit(Point *p)
{
    x_max = max(x_max, p->x);
    y_max = max(y_max, p->y);
    x_min = min(x_min, p->x);
    y_min = min(y_min, p->y);
}

/**
 * @brief It checks if the given point p is inside the rectangle.
 * @param p A pointer to the point to be checked.
 */
bool Rectangle::checkInside(Point *p)
{
    if (p->x > x_min && p->x < x_max && p->y > y_min && p->y < y_max)
        return true;
    return false;
}

#endif