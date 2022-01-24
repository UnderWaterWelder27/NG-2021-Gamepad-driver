#include "gamepaddriver.h"
#include "ui_gamepaddriver.h"

GamepadDriver::GamepadDriver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamepadDriver)
{
    ui->setupUi(this);

    m_gamepad = new QGamepad;
}

GamepadDriver::~GamepadDriver()
{
    delete ui;
}

