#include "Headers/gamepaddriver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GamepadDriver w;
    w.show();
    return a.exec();
}
