#include "point.hpp"

Point::Point() : x(0.0), y(0.0) {}

Point::Point(double x, double y) : x(x), y(y) {}

bool Point::operator==(const Point& other) const {
    return (x == other.x) and (y == other.y);
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << p.x << " " << p.y;
    return out;
}