#ifndef GEOMETRY_H
#define GEOMETRY_H


#include <math.h>
#include <iostream>


class Vec2;
class VectorArrow;


class Vec2 {
    public:
        double x1, y1;
        double x2, y2;
    
        Vec2(double x1, double y1, double x2, double y2);
        Vec2();

        Vec2 operator*(const double scalar);
        Vec2 operator+(const Vec2 other);
        std::ostream& operator<<(std::ostream &stream);
        Vec2 Rotate(double Angle);

        double Len();
};

class VectorArrow {
    // invariant: arrow data always actual

    double ArrowAngle;
    double ArrowScale;

    Vec2 BaseVector;

    public:
        Vec2 LeftPart;
        Vec2 RightPart;
        
        VectorArrow(Vec2 BaseVector, double ArrowScale, double ArrowAngle);
        void UpdateArrow();
};


const Vec2 NULLVECTOR = {0, 0, 0, 0};
const double DEFAULT_ARROW_SCALE = 0.2;
const double DEFAULT_ARROW_ANGLE = M_PI / 6;


#endif // GEOMETRY_Hroustruop c++ second edition