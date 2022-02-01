#ifndef GAMEPADDRIVER_H
#define GAMEPADDRIVER_H

#include "threadaxischange.h"
#include "mousecursorevents.h"

#include <QMainWindow>
#include <QObject>
#include <QGamepad>
#include <QCursor>
#include <QSpinBox>
#include <QSlider>
#include <QDebug>
#include <QThread>
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
    MouseCursorEvents *m_cursorEvent;

    int m_cursorSens;
    int m_wheelSens;
    int m_bPress;
    int m_bRemove;
};
#endif // GAMEPADDRIVER_H
