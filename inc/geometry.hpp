#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP


#include <cmath>
#include <iostream>


class geom_vector2 {
    float x, y;
    float len2;
public:
    geom_vector2(const float x, const float y);
    geom_vector2 operator+(const geom_vector2 &other) const;
    geom_vector2 operator*(const float scalar) const;
    geom_vector2 operator-(const geom_vector2 &other) const;
    geom_vector2 operator+=(const geom_vector2 &other);

    geom_vector2 operator*=(const float scalar);
    geom_vector2 operator-=(const geom_vector2 &other);
    geom_vector2 rotate90() const;
    
    bool operator<(const geom_vector2 &other) const;
    bool operator<=(const geom_vector2 &other) const;
    bool operator>(const geom_vector2 &other) const;
    bool operator>=(const geom_vector2 &other) const;

    geom_vector2 rotate(float radians) const;

      

    float get_x() const;
    float get_y() const;
    float get_len2();
};

std::ostream &operator<<(std::ostream &stream, const geom_vector2 &vec);
geom_vector2 cord_mul(const geom_vector2 &a, const geom_vector2 &b);


class oriented_vector {
    geom_vector2 begin;
    geom_vector2 end;

public:
    oriented_vector(const geom_vector2 &begin, const geom_vector2 &end);
    oriented_vector rotate(const float radians) const;
    
    geom_vector2 get_begin() const;
    geom_vector2 get_end() const;
    geom_vector2 get_radius_vector() const;
};


#endif // GEOMETRY_HPP