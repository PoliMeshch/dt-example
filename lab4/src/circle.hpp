#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"
#include <iostream>

class Circle {
    Point center;
    double radius;
public:
    Circle();
    Circle(double x, double y, double r);
    Circle(const Point& c, double r);

    double area() const;
    bool operator==(const Circle& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Circle& c);
};

#endif