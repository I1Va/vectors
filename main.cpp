#include <QApplication>
#include <QWidget>
#include <QPainter>


class PixelPoint {
    public:
        int x = 0, y = 0;

        PixelPoint(int x, int y) {
            this->x = x;
            this->y = y;
        }

        bool operator<(const PixelPoint Other) { return x < Other.x && y < Other.y; }
        PixelPoint operator+(const PixelPoint Other) { return PixelPoint(x + Other.x, y + Other.y); } 
};

class Vec2 {

    public:
        double x = 0, y = 0;

        Vec2(double x, double y) {
            this->x = x;
            this->y = y;
        }

        bool operator<(const Vec2 Other) { return x < Other.x && y < Other.y; }
        Vec2 operator+(const Vec2 Other) { return Vec2(x + Other.x, y + Other.y); }

};

class Plot : public QWidget {

public:
    Plot(QWidget *parent, PixelPoint LeftCorner, PixelPoint RightCorner, PixelPoint CordCenter, int CordScale)
        : QWidget(parent) {

        this->CordScale            = CordScale;
        this->CordCenter           = CordCenter;
        
        this->CanvasLeftCorner    = LeftCorner;
        this->CanvasRightCorner   = RightCorner;
        
        this->CanvasWidth = RightCorner.x - LeftCorner.x;
        this->CanvasHeight = RightCorner.y - LeftCorner.y;
    }



private:
    int CordScale = 0;
    PixelPoint CordCenter = {0, 0};

    PixelPoint CanvasLeftCorner = {0, 0};
    PixelPoint CanvasRightCorner = {0, 0};
    int CanvasWidth = 0;
    int CanvasHeight = 0;

    void MakeAxes() {
        QPainter painter(this);

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

    void paintEvent(QPaintEvent *) override {
        setGeometry(CanvasLeftCorner.x, CanvasLeftCorner.y, CanvasWidth, CanvasHeight);  
        setStyleSheet("background-color: white;");

        MakeAxes();
    }
};

// class CordSystem : public Plot {

// }

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget window;  

    window.setWindowTitle("Two Canvases");
    window.resize(800, 600);      

    Plot *big_plot = new Plot(&window, {50, 50}, {550, 550}, {50, 50}, 10);
    Plot *small_plot = new Plot(&window, {600, 400}, {750, 550}, {50, 50}, 10);

    window.show();                

    return app.exec();            
}
