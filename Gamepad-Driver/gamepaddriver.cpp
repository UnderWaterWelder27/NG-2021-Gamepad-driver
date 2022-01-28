#include "gamepaddriver.h"
#include "ui_gamepaddriver.h"

GamepadDriver::GamepadDriver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamepadDriver)
    , m_gamepad(0)
{
    ui->setupUi(this);

/// SENSETIVITY SLIDERS
    ui->sl_moveSensetivity->setRange(2, 15);
    ui->sl_wheelSensetivity->setRange(2, 15);

/// AXIS QSPINBOXES
    ui->sb_axisLeftX->setReadOnly(true);
    ui->sb_axisLeftY->setReadOnly(true);
    ui->sb_axisRightY->setReadOnly(true);
    ui->sb_axisLeftX->setRange(-1.0000000, 1.0000000);
    ui->sb_axisLeftY->setRange(-1.0000000, 1.0000000);
    ui->sb_axisRightY->setRange(-1.0000000, 1.0000000);

/// CURSOR QSPINBOXES
    ui->sb_mousePosX->setReadOnly(true);
    ui->sb_mousePosY->setReadOnly(true);
    ui->sb_mousePosX->setRange(0, 1400);
    ui->sb_mousePosY->setRange(0, 800);

    m_gamepad = new QGamepad;
    m_sensetivity = 2;
    connect (m_gamepad, &QGamepad::connectedChanged, this, &GamepadDriver::changeConectionStatus);

/// BIND GAMEPAD KEYS
    connect (m_gamepad, &QGamepad::axisLeftXChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisLeftYChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisRightYChanged, this, &GamepadDriver::rotateMouseWheel);
    connect (m_gamepad, &QGamepad::buttonL1Changed, this, &GamepadDriver::clickLeftMouseButton);
    connect (m_gamepad, &QGamepad::buttonR1Changed, this, &GamepadDriver::clickRightMouseButton);
    connect (m_gamepad, &QGamepad::buttonL2Changed, this, &GamepadDriver::doubleClick);

    connect (ui->sl_moveSensetivity, &QSlider::valueChanged, this, &GamepadDriver::changeSensetivity);
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

    for (int i = 1; i <= m_sensetivity; i++) {
        QCursor::setPos(X + m_gamepad->axisLeftX() * m_sensetivity, Y + m_gamepad->axisLeftY() * m_sensetivity);
    }

    ui->sb_axisLeftX->setValue(m_gamepad->axisLeftX());
    ui->sb_axisLeftY->setValue(m_gamepad->axisLeftY());

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

    ui->sb_axisRightY->setValue(m_gamepad->axisRightY());
}

int GamepadDriver::changeSensetivity()
{

}
