#include <QApplication>
#include <QWidget>
#include <QPainter>

class Point {
    public:
        int x = 0, y = 0;
};

class CordSystem : public QWidget {

private:
    int     cord_scale      = 0;
    Point   cord_center     = {0, 0};

    Point   canvas_left_corner  = {0, 0};
    Point   canvas_right_corner = {0, 0};
    int     canvas_width        = 0;
    int     canvas_height       = 0;
    
    

public:
    CordSystem(QWidget *parent, Point left_corner, Point right_corner, Point cord_center, int cord_scale)
        : QWidget(parent) {
        
        this->cord_scale            = cord_scale;
        this->cord_center           = cord_center;
        
        this->canvas_left_corner    = left_corner;
        this->canvas_right_corner   = right_corner;
        
        this->canvas_width = right_corner.x - left_corner.x;
        this->canvas_height = right_corner.y - left_corner.y;

    }

protected:
    void paintEvent(QPaintEvent *) override {
        setGeometry(canvas_left_corner.x, canvas_left_corner.y, canvas_width, canvas_height);  
        setStyleSheet("background-color: white;");

        QPainter painter(this);
        QPen pen(Qt::black);
        pen.setWidth(2);    

        painter.setPen(pen); 

        painter.drawLine(0, cord_center.y, canvas_width, cord_center.y);
        painter.drawLine(cord_center.x, 0, cord_center.x, canvas_height);
    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget window;  

    window.setWindowTitle("Two Canvases");
    window.resize(800, 600);      

    CordSystem *big_plot = new CordSystem(&window, {50, 50}, {550, 550}, {50, 50}, 1);
    CordSystem *small_plot = new CordSystem(&window, {600, 400}, {750, 550}, {50, 50}, 1);

    window.show();                

    return app.exec();            
}
