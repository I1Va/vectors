#include <iostream>

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

    double dx = x2 - x1;
    double dy = y2 - y1;

    double PrevLen = this->Len();
    double NewLen = PrevLen * scalar;
    
    return Vec2(x1, y1, x1 + dx * NewLen / PrevLen, y1 + dy * NewLen / PrevLen);
}

double Vec2::Len() {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}

Vec2 Vec2::operator+(const Vec2 other) { 
    return Vec2(x1 + other.x1, y1 + other.y1, x2 + other.x2, y2 + other.y2); 
}

std::ostream& Vec2::operator<<(std::ostream &stream) {
    stream<< "Vec2{" << x1 << "," << y1 << "," << x2 << "," << y2 << "\n";
    return stream;
}

Vec2 Vec2::Rotate(double Angle) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    double CosVal = std::cos(Angle);
    double SinVal = std::sin(Angle);

    double dxrot = dx * CosVal - dy * SinVal;
    double dyrot = dx * SinVal + dy * CosVal;


    return Vec2(x1, y1, x1 + dxrot, y1 + dyrot);
}



VectorArrow::VectorArrow(Vec2 BaseVector, double ArrowScale, double ArrowAngle) {
    this->BaseVector = BaseVector;
    this->ArrowScale = ArrowScale; 
    this->ArrowAngle = ArrowAngle;

    UpdateArrow();
}

void VectorArrow::UpdateArrow() {
    Vec2 ArrowPartBase = BaseVector * ArrowScale;

    LeftPart = BaseVector + ArrowPartBase; //+ ArrowPartBase.Rotate(0);
    RightPart = ArrowPartBase.Rotate(M_PI / 6);
}

