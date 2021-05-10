#include <QApplication>
#include <QPushButton>
#include <QStyleFactory>
#include "display/Window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Window *window = new Window();
    return QApplication::exec();
}
