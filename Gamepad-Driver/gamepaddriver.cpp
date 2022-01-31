#include "gamepaddriver.h"
#include "ui_gamepaddriver.h"

GamepadDriver::GamepadDriver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamepadDriver)
    , m_gamepad(0)
{
    ui->setupUi(this);

    m_gamepad = new QGamepad;
    m_axisThread = new ThreadAxisChange(m_gamepad, m_cursorSens);

    m_prevAxisAngle = 0.000000;

    m_cursorSens = 10;
    m_wheelSens = 15;
    m_bPress = 0;
    m_bPress = 0;

/// SENSETIVITY SLIDERS
    ui->sl_moveSensitivity->setRange(15, 100);
    ui->sl_wheelSensitivity->setRange(15, 70);

/// AXIS QSPINBOXES
    ui->sb_axisLeftX->setReadOnly(true);
    ui->sb_axisLeftY->setReadOnly(true);
    ui->sb_axisRightY->setReadOnly(true);
    ui->sb_axisLeftX->setRange(-1.00, 1.00);
    ui->sb_axisLeftY->setRange(-1.00, 1.00);
    ui->sb_axisRightY->setRange(-1.00, 1.00);

/// CURSOR QSPINBOXES
    ui->sb_mousePosX->setReadOnly(true);
    ui->sb_mousePosY->setReadOnly(true);
    ui->sb_mousePosX->setRange(0, 1400);
    ui->sb_mousePosY->setRange(0, 800);

    connect (m_gamepad, &QGamepad::connectedChanged, this, &GamepadDriver::changeConectionStatus);

/// BIND GAMEPAD KEYS
    connect (m_gamepad, &QGamepad::axisLeftXChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisLeftYChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisRightYChanged, this, &GamepadDriver::rotateMouseWheel);
    connect (m_gamepad, &QGamepad::buttonL1Changed, this, &GamepadDriver::simulateMouseButtonClick);
    connect (m_gamepad, &QGamepad::buttonR1Changed, this, &GamepadDriver::simulateMouseButtonClick);
    connect (m_gamepad, &QGamepad::buttonR2Changed, this, &GamepadDriver::simulateMouseButtonClick);
    connect (m_gamepad, &QGamepad::buttonL2Changed, this, &GamepadDriver::simulateDoubleClick);

    connect (ui->sl_moveSensitivity, &QSlider::valueChanged, this, &GamepadDriver::changeSensitivity);
    connect (ui->sl_wheelSensitivity, &QSlider::valueChanged, this, &GamepadDriver::changeSensitivity);
}

GamepadDriver::~GamepadDriver()
{
    delete ui;
}

void GamepadDriver::changeConectionStatus()
{
    if (m_gamepad->isConnected()) { ui->l_checkConnection->setText("Connected"); }
    else { ui->l_checkConnection->setText("Disconnected"); }
}

void GamepadDriver::changeMousePos()
{
    //disconnect (m_gamepad, &QGamepad::axisLeftXChanged, this, &GamepadDriver::changeMousePos);
    //disconnect (m_gamepad, &QGamepad::axisLeftYChanged, this, &GamepadDriver::changeMousePos);

    connect (m_axisThread, &ThreadAxisChange::gamepadLeftAxisX, this, &GamepadDriver::changeMousePos);
    connect (m_axisThread, &ThreadAxisChange::gamepadLeftAxisX, this, &GamepadDriver::changeMousePos);

    ui->sb_axisLeftX->setValue(m_gamepad->axisLeftX());
    ui->sb_axisLeftY->setValue(m_gamepad->axisLeftY());
    ui->sb_mousePosX->setValue(QCursor::pos().x());
    ui->sb_mousePosY->setValue(QCursor::pos().y());

    qDebug() << "cursor pos y" << QCursor::pos().y();
    qDebug() << "cursor pos x" << QCursor::pos().x();
    qDebug() << "axis y" << m_gamepad->axisLeftY();
    qDebug() << "axis x" << m_gamepad->axisLeftX();
    qDebug() << "change pos x" << (m_gamepad->axisLeftX() * m_cursorSens)/5;
    qDebug() << "change pos y" << (m_gamepad->axisLeftY() * m_cursorSens)/5;

    //connect (m_gamepad, &QGamepad::axisLeftXChanged, this, &GamepadDriver::changeMousePos);
    //connect (m_gamepad, &QGamepad::axisLeftYChanged, this, &GamepadDriver::changeMousePos);
}

void GamepadDriver::simulateMouseButtonClick(bool pressSignal)
{
    QGamepad* button = (QGamepad*)sender();

    if (button->buttonL1()) { m_bPress = 2; m_bRemove = 4; }
    if (button->buttonR1()) { m_bPress = 8; m_bRemove = 16; }
    if (button->buttonR2()) { m_bPress = 32; m_bRemove = 64; }

    if (pressSignal == true)    { mouse_event(m_bPress, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
    else                        { mouse_event(m_bRemove, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
}

void GamepadDriver::simulateDoubleClick(bool pressSignal)
{
    if (pressSignal == true)    { mouse_event(LEFTDOWN, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
                                  mouse_event(LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
}

void GamepadDriver::rotateMouseWheel()
{
    if (m_gamepad->axisRightY() > 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(), -m_wheelSens, 0); }
    if (m_gamepad->axisRightY() < 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(),  m_wheelSens, 0); }

    ui->sb_axisRightY->setValue(m_gamepad->axisRightY());
}

void GamepadDriver::changeSensitivity(int sliderValue)
{
    QSlider* currentSlider = (QSlider*)sender();
    if (currentSlider->objectName() == "sl_moveSensitivity" ) { m_cursorSens = sliderValue; }
    if (currentSlider->objectName() == "sl_wheelSensitivity" ) { m_wheelSens = sliderValue; }
}
