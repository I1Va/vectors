#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QPushButton btn("Hello Qt");
    btn.resize(200,60);
    btn.show();
    return app.exec();
}