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
    connect (m_gamepad, &QGamepad::buttonL1Changed, this, &GamepadDriver::clickMouseButton);
    connect (m_gamepad, &QGamepad::buttonR1Changed, this, [](bool value){ qDebug() << "RB" << value; });
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
    double cursorX = QCursor::pos().x();
    double cursorY = QCursor::pos().y();
    double axisX = m_gamepad->axisLeftX();
    double axisY = m_gamepad->axisLeftY();
    double sensitivity = 4.1;

    if (axisX > 0.93 || axisX < -0.93 || axisY > 0.93 || axisX < -0.93) {
        sensitivity = 7.1;
    }
    else if (axisX > 0.74 || axisX < -0.74 || axisY > 0.74 || axisX < -0.74) {
        sensitivity = 6.1;
    }
    else if (axisX > 0.63 || axisX < -0.63 || axisY > 0.63 || axisX < -0.63) {
        sensitivity = 5.1;
    }

    QCursor::setPos(cursorX + axisX*sensitivity, cursorY + axisY*sensitivity);

}

void GamepadDriver::clickMouseButton(bool pressSignal)
{
    double X = QCursor::pos().x();
    double Y = QCursor::pos().y();

    if (pressSignal == true) { mouse_event(0x0002, X, Y, 0, 0); }
    else { mouse_event(0x0004, X, Y, 0, 0); }
}
