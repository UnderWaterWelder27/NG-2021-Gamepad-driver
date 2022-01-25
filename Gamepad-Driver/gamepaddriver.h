#ifndef GAMEPADDRIVER_H
#define GAMEPADDRIVER_H

#include <QMainWindow>
#include <QObject>
#include <QGamepad>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class GamepadDriver; }
QT_END_NAMESPACE

class GamepadDriver : public QMainWindow
{
    Q_OBJECT

public:
    GamepadDriver(QWidget *parent = nullptr);
    ~GamepadDriver();

    void changeConectionStatus();

private:
    Ui::GamepadDriver *ui;
    QGamepad *m_gamepad;
};
#endif // GAMEPADDRIVER_H
