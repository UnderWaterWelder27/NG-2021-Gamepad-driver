#ifndef GAMEPADDRIVER_H
#define GAMEPADDRIVER_H

#include <QMainWindow>
#include <QObject>
#include <QGamepad>
#include <QCursor>
#include <QSpinBox>
#include <QSlider>
#include <QDebug>
#include <QThread>
#include <windows.h>
#include "threadaxischange.h"

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
        LEFTDOWN = 2,
        LEFTUP = 4,
        RIGHTDOWN = 8,
        RIGHTUP = 16,
        MIDDLEDOWN = 32,
        MIDDLEUP = 64,
        WHEELROTATE = 0x0800,
        MOVE = 0x0001
    };

public slots:
    void changeConectionStatus();

    void changeMousePos();
    void simulateMouseButtonClick(bool pressSignal);
    void simulateDoubleClick(bool pressSignal);
    void rotateMouseWheel();
    void changeSensitivity(int sliderValue);

private:
    Ui::GamepadDriver *ui;
    QGamepad *m_gamepad;

    int m_cursorSens;
    int m_wheelSens;
    int m_bPress;
    int m_bRemove;
};
#endif // GAMEPADDRIVER_H
