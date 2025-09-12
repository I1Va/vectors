// #ifndef VISUAL_H
// #define VISUAL_H

// #include <QVector>
// #include <QMutex>


// class PixelPoint {
//     public:
//         int x, y;

//         PixelPoint(int x, int y);

//         bool operator<(const PixelPoint other);
//         PixelPoint operator+(const PixelPoint other);
// };


// class PlotWidget : public QWidget {
// public:
//     explicit PlotWidget(QWidget *parent, PixelPoint LeftCorner, PixelPoint RightCorner, PixelPoint CordCenter, int CordScale);
//     void DrawVector(PixelPoint VecStart, PixelPoint VecEnd, double ArrowScale, double ArrowAngle); 

// protected:
//     void paintEvent(QPaintEvent *event) override;

// private:
//     void MakeAxes(QPainter *painter);

//     int CordScale = 0;
//     PixelPoint CordCenter = {0, 0};

//     PixelPoint CanvasLeftCorner = {0, 0};
//     PixelPoint CanvasRightCorner = {0, 0};
//     int CanvasWidth = 0;
//     int CanvasHeight = 0;

//     enum ShapeType { 
//         Line, 
//         Dot
//     };

//     struct Shape {
//         enum ShapeType Type;
//         QLine Line;
//     };

//     QVector<Shape> Shapes;
//     QMutex Mutex;

// };





// #endif // VISUAL_H