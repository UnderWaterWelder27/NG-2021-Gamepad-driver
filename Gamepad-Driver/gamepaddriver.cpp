#include "gamepaddriver.h"
#include "ui_gamepaddriver.h"

GamepadDriver::GamepadDriver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamepadDriver)
    , m_gamepad(0)
{
    ui->setupUi(this);

/// AXIS QSPINBOXES
    ui->sb_axisLeftX->setReadOnly(true);
    ui->sb_axisLeftY->setReadOnly(true);
    ui->sb_axisLeftX->setRange(-1.0000000, 1.0000000);
    ui->sb_axisLeftY->setRange(-1.0000000, 1.0000000);

/// CURSOR QSPINBOXES
    ui->sb_mousePosX->setReadOnly(true);
    ui->sb_mousePosY->setReadOnly(true);
    ui->sb_mousePosX->setRange(0, 1400);
    ui->sb_mousePosY->setRange(0, 800);

    m_gamepad = new QGamepad;
    connect (m_gamepad, &QGamepad::connectedChanged, this, &GamepadDriver::changeConectionStatus);

/// BIND GAMEPAD KEYS
    connect (m_gamepad, &QGamepad::axisLeftXChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisLeftYChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisRightYChanged, this, &GamepadDriver::rotateMouseWheel);
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

    ui->sb_axisLeftX->setValue(axisX);
    ui->sb_axisLeftY->setValue(axisY);

    ui->sb_mousePosX->setValue(QCursor::pos().x());
    ui->sb_mousePosY->setValue(QCursor::pos().y());
}

void GamepadDriver::clickLeftMouseButton(bool pressSignal)
{
    if (pressSignal == true)    { mouse_event(LEFTDOWN, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
    else                        { mouse_event(LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
}

void GamepadDriver::clickRightMouseButton(bool pressSignal)
{
    if (pressSignal == true)    { mouse_event(RIGHTDOWN, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
    else                        { mouse_event(RIGHTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
}

void GamepadDriver::doubleClick(bool pressSignal)
{
    if (pressSignal == true)    { mouse_event(LEFTDOWN, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
                                  mouse_event(LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
}

void GamepadDriver::rotateMouseWheel()
{
    if (m_gamepad->axisRightY() > 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(), -30, 0); }
    if (m_gamepad->axisRightY() < 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(), 30, 0); }
}
