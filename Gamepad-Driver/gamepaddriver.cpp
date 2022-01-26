#include "gamepaddriver.h"
#include "ui_gamepaddriver.h"

GamepadDriver::GamepadDriver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamepadDriver)
    , m_gamepad(0)
{
    ui->setupUi(this);
    m_gamepad = new QGamepad;

    connect (m_gamepad, &QGamepad::connectedChanged, this, &GamepadDriver::changeConectionStatus);
    connect (m_gamepad, &QGamepad::axisLeftXChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisLeftYChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisRightXChanged, this, [](double value){ qDebug() << "Right X" << value; });
    connect (m_gamepad, &QGamepad::axisRightYChanged, this, [](double value){ qDebug() << "Right Y" << value; });
    connect (m_gamepad, &QGamepad::buttonL1Changed, this, &GamepadDriver::clickLeftMouseButton);
    connect (m_gamepad, &QGamepad::buttonR1Changed, this, &GamepadDriver::clickRightMouseButton);
    connect (m_gamepad, &QGamepad::buttonL2Changed, this, &GamepadDriver::doubleClick);
}

GamepadDriver::~GamepadDriver()
{
    delete ui;
}

void GamepadDriver::changeConectionStatus()
{
    ui->l_checkConnection->setText("Connected");
}

void GamepadDriver::changeMousePos()
{
    double X = QCursor::pos().x();
    double Y = QCursor::pos().y();
    double axisX = m_gamepad->axisLeftX();
    double axisY = m_gamepad->axisLeftY();

    QCursor::setPos(X + axisX*1.0, Y + axisY*1.0);
    QCursor::setPos(X + axisX*3.0, Y + axisY*3.0);
    QCursor::setPos(X + axisX*5.0, Y + axisY*5.0);
    QCursor::setPos(X + axisX*7.0, Y + axisY*7.0);
    QCursor::setPos(X + axisX*10.0, Y + axisY*10.0);
}

void GamepadDriver::clickLeftMouseButton(bool pressSignal)
{
    double X = QCursor::pos().x();
    double Y = QCursor::pos().y();
    if (pressSignal == true) { mouse_event(LEFTDOWN, X, Y, 0, 0); }
    else { mouse_event(LEFTUP, X, Y, 0, 0); }
}

void GamepadDriver::clickRightMouseButton(bool pressSignal)
{
    double X = QCursor::pos().x();
    double Y = QCursor::pos().y();
    if (pressSignal == true) { mouse_event(RIGHTDOWN, X, Y, 0, 0); }
    else { mouse_event(RIGHTUP, X, Y, 0, 0); }
}

void GamepadDriver::doubleClick(bool pressSignal)
{
    double X = QCursor::pos().x();
    double Y = QCursor::pos().y();
    if (pressSignal == true) { mouse_event(LEFTDOWN, X, Y, 0, 0); }
    mouse_event(LEFTUP, X, Y, 0, 0);
}
