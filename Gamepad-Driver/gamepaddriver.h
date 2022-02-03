#ifndef GAMEPADDRIVER_H
#define GAMEPADDRIVER_H

#include "mousecursorevents.h"

#include <QMainWindow>
#include <QObject>
#include <QGamepad>
#include <QCursor>
#include <QSpinBox>
#include <QSlider>
#include <QThread>
#include <QDebug>

#include <QEvent>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QAction>
#include <QPoint>
#include <QWidget>

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

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void windowCloseHide();
    void trayIconClicked(QSystemTrayIcon::ActivationReason reason);

    void changeConectionStatus();
    void changeMousePos();
    void simulateDoubleClick(bool pressSignal);
    void rotateMouseWheel();
    void changeSensitivity(int sliderValue);

private:
    Ui::GamepadDriver *ui;
    QGamepad *m_gamepad;
    MouseCursorEvents *m_cursorEvent;
    QSystemTrayIcon *m_trayIcon;

    QPoint cursorPressPos;
    int m_cursorSens;
    int m_wheelSens; 
};
#endif // GAMEPADDRIVER_H
