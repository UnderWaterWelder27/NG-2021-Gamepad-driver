#ifndef GAMEPADDRIVER_H
#define GAMEPADDRIVER_H

#include "source/mousecursorevents.h"

#include <QMainWindow>
#include <QObject>
#include <QGamepad>
#include <QCursor>
#include <QSpinBox>
#include <QSlider>
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

    void showConectionStatus();
    void changeSensitivity(int sliderValue);

private:
    Ui::GamepadDriver *ui;
    QGamepad *m_gamepad;
    QSystemTrayIcon *m_trayIcon;
    MouseCursorEvents *m_cursorEvent;

    QPoint cursorPressPos;
    int m_cursorSens;
    int m_wheelSens; 
};
#endif // GAMEPADDRIVER_H
