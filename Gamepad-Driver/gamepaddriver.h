#ifndef GAMEPADDRIVER_H
#define GAMEPADDRIVER_H

#include <QMainWindow>
#include <QObject>
#include <QGamepad>
#include <QCursor>
#include <QSpinBox>
#include <QSlider>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GamepadDriver; }
QT_END_NAMESPACE

class GamepadDriver : public QMainWindow
{
    Q_OBJECT

public:
    GamepadDriver(QWidget *parent = nullptr);
    ~GamepadDriver();

    enum MouseEventFlags
    {
        LEFTDOWN = 0x0002,
        LEFTUP = 0x0004,
        RIGHTDOWN = 0x0008,
        RIGHTUP = 0x0010,
        MIDDLEDOWN = 0x0020,
        MIDDLEUP = 0x0040,
        WHEELROTATE = 0x0800,
        MOVE = 0x0001
    };

public slots:
    void changeConectionStatus();

    void changeMousePos();
    void clickLeftMouseButton(bool pressSignal);
    void clickRightMouseButton(bool pressSignal);
    void doubleClick(bool pressSignal);
    void rotateMouseWheel();

    void changeSensetivity(int sliderValue);

private:
    Ui::GamepadDriver *ui;
    QGamepad *m_gamepad;
    int m_cursorSens;
    int m_wheelSens;
};
#endif // GAMEPADDRIVER_H
