#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point {
    double x;
    double y;
public:
    Point();
    Point(double x, double y);

    bool operator==(const Point& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Point& p);
};

#endif