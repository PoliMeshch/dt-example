#include "circle.hpp"

Circle::Circle() : center(), radius(0.0) {}

Circle::Circle(double x, double y, double r) : center(x, y), radius(r) {}

Circle::Circle(const Point& c, double r) : center(c), radius(r) {}

double Circle::area() const {
    return 3.14 * radius * radius;
}

bool Circle::operator==(const Circle& other) const {
    return (center == other.center) and (radius == other.radius);
}

std::ostream& operator<<(std::ostream& out, const Circle& c) {
    out << c.center << " " << c.radius;
    return out;
}