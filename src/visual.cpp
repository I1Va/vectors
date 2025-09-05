#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMutex>

#include <iostream>
#include "geometry.h"
#include "visual.h"

PixelPoint::PixelPoint(int x, int y) {
    this->x = x;
    this->y = y;
} 

bool PixelPoint::operator<(const PixelPoint other) { return x < other.x && y < other.y; }
PixelPoint PixelPoint::operator+(const PixelPoint other) { return PixelPoint(x + other.x, y + other.y); } 




PlotWidget::PlotWidget(QWidget *parent, 
                       const PixelPoint LeftCorner, 
                       const PixelPoint RightCorner, 
                       const PixelPoint CordCenter, 
                       const int CordScale)
    : QWidget(parent) 
    , CanvasLeftCorner(LeftCorner)
    , CanvasRightCorner(RightCorner)
    , CordCenter(CordCenter)
    , CordScale(CordScale)
{
    CanvasWidth = CanvasRightCorner.x - CanvasLeftCorner.x;
    CanvasHeight = CanvasRightCorner.y - CanvasLeftCorner.y;

    setGeometry(CanvasLeftCorner.x, CanvasLeftCorner.y, CanvasWidth, CanvasHeight);
    setStyleSheet("background-color: white;");
}   

void PlotWidget::DrawVector(QPainter *painter, PixelPoint VecStart, PixelPoint VecEnd, double ArrowScale=DEFAULT_ARROW_SCALE, double ArrowAngle=DEFAULT_ARROW_ANGLE) {
    assert(painter);

    QPen pen(Qt::black);    
    painter->setPen(pen);
    pen.setWidth(2);


    Vec2 Vector(VecStart.x, VecStart.y, VecEnd.x, VecEnd.y);
    VectorArrow Arrow(Vector, ArrowScale, ArrowAngle);

    painter->drawLine(Vector.x1, Vector.y1, Vector.x2, Vector.y2);
    painter->drawLine(Arrow.LeftPart.x1, Arrow.LeftPart.y1, Arrow.LeftPart.x2, Arrow.LeftPart.y2);
    painter->drawLine(Arrow.RightPart.x1, Arrow.RightPart.y1, Arrow.RightPart.x2, Arrow.RightPart.y2);
}

void PlotWidget::MakeAxes(QPainter *painter) {
    assert(painter);

    QPen pen(Qt::black);    
    painter->setPen(pen);

    pen.setWidth(2);
    painter->drawLine(0, CordCenter.y, CanvasWidth, CordCenter.y);
    painter->drawLine(CordCenter.x, 0, CordCenter.x, CanvasHeight);

    pen.setWidth(1);
    
    // Horizontal axe
    for (int hor_tick_x = CordCenter.x; hor_tick_x < CanvasWidth; hor_tick_x += CordScale) {
        painter->drawLine(hor_tick_x, CordCenter.y - 1, hor_tick_x, CordCenter.y + 1);
    }
    for (int hor_tick_x = CordCenter.x; hor_tick_x >= 0; hor_tick_x -= CordScale) {
        painter->drawLine(hor_tick_x, CordCenter.y - 1, hor_tick_x, CordCenter.y + 1);
    }

    // Vertical Axe
    for (int ver_tick_y = CordCenter.y; ver_tick_y < CanvasHeight; ver_tick_y += CordScale) {
        painter->drawLine(CordCenter.x - 1, ver_tick_y, CordCenter.x + 1, ver_tick_y);
    }
    for (int ver_tick_y = CordCenter.y; ver_tick_y >= 0; ver_tick_y -= CordScale) {
        painter->drawLine(CordCenter.x - 1, ver_tick_y, CordCenter.x + 1, ver_tick_y);
    }

}

void PlotWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    MakeAxes(&painter);
}