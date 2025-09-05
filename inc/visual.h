#ifndef VISUAL_H
#define VISUAL_H


class PixelPoint {
    public:
        int x, y;

        PixelPoint(int x, int y);

        bool operator<(const PixelPoint other);
        PixelPoint operator+(const PixelPoint other);
};


class PlotWidget : public QWidget {
    Q_OBJECT
public:
        PlotWidget(QWidget *parent, PixelPoint LeftCorner, PixelPoint RightCorner, PixelPoint CordCenter, int CordScale);
        void DrawVector(QPainter *painter, PixelPoint VecStart, PixelPoint VecEnd, double ArrowScale, double ArrowAngle); 
    
    
protected:

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);

    setGeometry(CanvasLeftCorner.x, CanvasLeftCorner.y, CanvasWidth, CanvasHeight);  
    setStyleSheet("background-color: white;");

    // MakeAxes(&painter);

    QPen pen(Qt::black);    
    painter.setPen(pen);

    pen.setWidth(2);
    painter.drawLine(0, CordCenter.y, CanvasWidth, CordCenter.y);
    painter.drawLine(CordCenter.x, 0, CordCenter.x, CanvasHeight);

    pen.setWidth(1);
    
    // Horizontal axe
    for (int hor_tick_x = CordCenter.x; hor_tick_x < CanvasWidth; hor_tick_x += CordScale) {
        painter.drawLine(hor_tick_x, CordCenter.y - 1, hor_tick_x, CordCenter.y + 1);
    }
    for (int hor_tick_x = CordCenter.x; hor_tick_x >= 0; hor_tick_x -= CordScale) {
        painter.drawLine(hor_tick_x, CordCenter.y - 1, hor_tick_x, CordCenter.y + 1);
    }

    // Vertical Axe
    for (int ver_tick_y = CordCenter.y; ver_tick_y < CanvasHeight; ver_tick_y += CordScale) {
        painter.drawLine(CordCenter.x - 1, ver_tick_y, CordCenter.x + 1, ver_tick_y);
    }
    for (int ver_tick_y = CordCenter.y; ver_tick_y >= 0; ver_tick_y -= CordScale) {
        painter.drawLine(CordCenter.x - 1, ver_tick_y, CordCenter.x + 1, ver_tick_y);
    }
        }

private:
    void MakeAxes(QPainter *painter);

    int CordScale = 0;
    PixelPoint CordCenter = {0, 0};

    PixelPoint CanvasLeftCorner = {0, 0};
    PixelPoint CanvasRightCorner = {0, 0};
    int CanvasWidth = 0;
    int CanvasHeight = 0;

};





#endif // VISUAL_H