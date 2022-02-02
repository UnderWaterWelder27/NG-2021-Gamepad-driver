#ifndef GAMEPADDRIVER_H
#define GAMEPADDRIVER_H

#include "mousecursorevents.h"

#include <QMainWindow>
#include <QObject>
#include <QGamepad>
#include <QCursor>
#include <QSpinBox>
#include <QSlider>
#include <QDebug>
#include <QThread>

#include <QMenu>
#include <QCloseEvent>
#include <QSystemTrayIcon>
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
    void changeConectionStatus();
    void trayIconClicked(QSystemTrayIcon::ActivationReason reason);

    void changeMousePos();
    void simulateMouseButtonClick(bool pressSignal);
    void simulateDoubleClick(bool pressSignal);
    void rotateMouseWheel();
    void changeSensitivity(int sliderValue);

private:
    Ui::GamepadDriver *ui;
    QGamepad *m_gamepad;
    MouseCursorEvents *m_cursorEvent;
    QSystemTrayIcon *m_trayIcon;

    int m_cursorSens;
    int m_wheelSens;
    int m_bPress;
    int m_bRemove;

    QPoint cursorPressPos;
};
#endif // GAMEPADDRIVER_H
