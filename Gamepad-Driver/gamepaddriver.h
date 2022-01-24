#ifndef GAMEPADDRIVER_H
#define GAMEPADDRIVER_H

#include <QMainWindow>
#include <QGamepad>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class GamepadDriver; }
QT_END_NAMESPACE

class GamepadDriver : public QMainWindow
{
    Q_OBJECT

public:
    GamepadDriver(QWidget *parent = nullptr);
    ~GamepadDriver();

private:
    Ui::GamepadDriver *ui;
    QGamepad *m_gamepad;
};
#endif // GAMEPADDRIVER_H
