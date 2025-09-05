#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <math.h>

#include "geometry.h"
#include "visual.h"


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget window;  

    window.setWindowTitle("Two Canvases");
    window.resize(800, 600);      

    PlotWidget *big_plot = new PlotWidget(&window, {50, 50}, {550, 550}, {50, 50}, 10);
    PlotWidget *small_plot = new PlotWidget(&window, {600, 400}, {750, 550}, {50, 50}, 10);

    //  small_plot->DrawVector({0, 0}, {100, 100});

    window.show();                

    return app.exec();            
}
