#include <cmath>
#include <iostream>
#include "geometry.hpp"


geom_vector2::geom_vector2(const float x, const float y): x(x), y(y) { len2 = NAN; }
geom_vector2 geom_vector2::operator+(const geom_vector2 &other) const { return geom_vector2(x + other.x, y + other.y); }
geom_vector2 geom_vector2::operator*(const float scalar) const { return geom_vector2(x * scalar, y * scalar); }
geom_vector2 geom_vector2::operator-(const geom_vector2 &other) const { return geom_vector2(x - other.x, y - other.y); }
geom_vector2 geom_vector2::operator+=(const geom_vector2 &other) { 
    len2 = NAN; 
    x += other.x;
    y += other.y;
    return *this;
}
geom_vector2 geom_vector2::operator*=(const float scalar) { 
        len2 = NAN; 
        x *= scalar;
        y *= scalar;
        return *this;
    }
geom_vector2 geom_vector2:: operator-=(const geom_vector2 &other) { 
        len2 = NAN; 
        x -= other.x;
        y -= other.y;
        return *this;
    }

geom_vector2 geom_vector2::rotate90() const {
        return geom_vector2(-y, x);
    }
    
bool geom_vector2::operator<(const geom_vector2 &other) const { return x < other.x && y < other.y; }
bool geom_vector2::operator<=(const geom_vector2 &other) const { return x <= other.x && y <= other.y; }
bool geom_vector2::operator>(const geom_vector2 &other) const { return x > other.x && y > other.y; }
bool geom_vector2::operator>=(const geom_vector2 &other) const { return x >= other.x && y >= other.y; }

    
float geom_vector2::get_x() const { return x; }
float geom_vector2::get_y() const { return y; }
float geom_vector2::get_len2() {
    if (std::isnan(len2)) len2 = x * x + y * y;
    return len2;
}

geom_vector2 cord_mul(const geom_vector2 &a, const geom_vector2 &b) {
    return geom_vector2(a.get_x() * b.get_x(), a.get_y() * b.get_y());
}

std::ostream &operator<<(std::ostream &stream, const geom_vector2 &vec) {
    stream << "{" << vec.get_x() << ", " << vec.get_y() << "}\n"; 
    return stream;
}

geom_vector2 geom_vector2::rotate(float radians) const {
    float x_new = x * std::cos(radians) - y * std::sin(radians);
    float y_new = x * std::sin(radians) + y * std::cos(radians);

    return geom_vector2(x_new, y_new);
}


oriented_vector::oriented_vector(const geom_vector2 &begin, const geom_vector2 &end): begin(begin), end(end) {}
oriented_vector oriented_vector::rotate(const float radians) const {
    geom_vector2 rotated_r_vec = get_radius_vector().rotate(radians) + begin;
    
    return oriented_vector(begin, rotated_r_vec);
}

geom_vector2 oriented_vector::get_radius_vector() const { return end - begin; }
geom_vector2 oriented_vector::get_begin() const { return begin; }
geom_vector2 oriented_vector::get_end() const { return end; }

