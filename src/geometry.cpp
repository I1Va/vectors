#include "geometry.h"

Vec2::Vec2(double x1, double y1, double x2, double y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

Vec2::Vec2() {
    this->x1 = 0;
    this->y1 = 0;
    this->x2 = 0;
    this->y2 = 0;
}

Vec2 Vec2::operator*(const double scalar) {
    return Vec2(x1 * scalar, y1 * scalar, x2 * scalar, y2 * scalar);
}

Vec2 Vec2::operator+(const Vec2 other) { 
    return Vec2(x1 + other.x1, y1 + other.y1, x2 + other.x2, y2 + other.y2); 
}

Vec2 Vec2::Rotate(double Angle) {
    Vec2 ResVec2 = NULLVECTOR;
    ResVec2.x1 = x1 * cos(Angle) - y1 * sin(Angle);
    ResVec2.y1 = x1 * sin(Angle) + y1 * cos(Angle);
    ResVec2.x2 = x2 * cos(Angle) - y2 * sin(Angle);
    ResVec2.y2 = x2 * sin(Angle) + y2 * cos(Angle);

    return ResVec2;
}


VectorArrow::VectorArrow(Vec2 BaseVector, double ArrowScale, double ArrowAngle) {
    this->BaseVector = BaseVector;
    this->ArrowScale = ArrowScale; 
    this->ArrowAngle = ArrowAngle;

    UpdateArrow();
}

void VectorArrow::UpdateArrow() {   
    Vec2 ArrowPartBase = (BaseVector + (BaseVector * ArrowScale));

    LeftPart = ArrowPartBase.Rotate(M_PI - ArrowAngle);
    RightPart = ArrowPartBase.Rotate(M_PI + ArrowAngle);
}

