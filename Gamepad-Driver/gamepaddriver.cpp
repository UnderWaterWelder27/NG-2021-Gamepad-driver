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
    connect (m_gamepad, &QGamepad::axisLeftXChanged, this, [](double value){ qDebug() << "Left X" << value; });
    connect (m_gamepad, &QGamepad::axisLeftYChanged, this, [](double value){ qDebug() << "Left Y" << value; });
    connect (m_gamepad, &QGamepad::axisRightXChanged, this, [](double value){ qDebug() << "Right X" << value; });
    connect (m_gamepad, &QGamepad::axisRightYChanged, this, [](double value){ qDebug() << "Right Y" << value; });
    connect (m_gamepad, &QGamepad::buttonL1Changed, this, [](bool value){ qDebug() << "LB" << value; });
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

