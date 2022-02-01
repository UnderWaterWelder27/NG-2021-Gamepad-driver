#include "gamepaddriver.h"
#include "ui_gamepaddriver.h"

GamepadDriver::GamepadDriver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamepadDriver)
    , m_gamepad(0)
{
    ui->setupUi(this);

/// SYSTEM TRAY ICON CONFIGURATION
    m_trayIcon = new QSystemTrayIcon(this);
    m_gamepad = new QGamepad;
    m_cursorEvent = new MouseCursorEvents;

    this->setWindowTitle("XBox Gamepad Driver");
    this->setWindowIcon(QIcon(":/tmp/gamepad-icon.png"));
    m_trayIcon->setIcon(QIcon(":/tmp/gamepad-icon.png"));

    QMenu *trayMenu = new QMenu(this);
    QAction *showProgramWindow = new QAction("View window", this);
    QAction *quitProgram = new QAction("Exit", this);

    trayMenu->addAction(showProgramWindow);
    trayMenu->addAction(quitProgram);
    m_trayIcon->setContextMenu(trayMenu);

/// PRIVATE VARIABLES
    m_cursorSens = 15;
    m_wheelSens = 15;
    m_bPress = 0;
    m_bRemove = 0;

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

/// CONNECT TRAY MENU EVENTS
    connect (showProgramWindow, &QAction::triggered, this, &QWidget::showNormal);
    connect (quitProgram, &QAction::triggered, this, &QCoreApplication::quit);
    connect (m_trayIcon, &QSystemTrayIcon::activated, this, &GamepadDriver::trayIconClicked);

/// CHECK GAMEPAD CONNECTION
    connect (m_gamepad, &QGamepad::connectedChanged, this, &GamepadDriver::changeConectionStatus);

/// CONNECT GAMEPAD KEYS
    connect (m_gamepad, &QGamepad::axisLeftXChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisLeftYChanged, this, &GamepadDriver::changeMousePos);
    connect (m_gamepad, &QGamepad::axisRightYChanged, this, &GamepadDriver::rotateMouseWheel);
    connect (m_gamepad, &QGamepad::buttonL1Changed, this, &GamepadDriver::simulateMouseButtonClick);
    connect (m_gamepad, &QGamepad::buttonR1Changed, this, &GamepadDriver::simulateMouseButtonClick);
    connect (m_gamepad, &QGamepad::buttonR2Changed, this, &GamepadDriver::simulateMouseButtonClick);
    connect (m_gamepad, &QGamepad::buttonYChanged , this, &GamepadDriver::simulateDoubleClick);

/// CONNECT SENSITIVITY SLIDERS
    connect (ui->sl_moveSensitivity, &QSlider::valueChanged, this, &GamepadDriver::changeSensitivity);
    connect (ui->sl_wheelSensitivity, &QSlider::valueChanged, this, &GamepadDriver::changeSensitivity);
}

GamepadDriver::~GamepadDriver()
{
    delete ui;
}

void GamepadDriver::closeEvent(QCloseEvent *event)
{
    if (this->isVisible()) {
        event->ignore();
        this->hide();
        m_trayIcon->show();
    }
}

void GamepadDriver::changeConectionStatus()
{
    if (m_gamepad->isConnected()) { ui->l_checkConnection->setText("Connected"); }
    else { ui->l_checkConnection->setText("Disconnected"); }
}

void GamepadDriver::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (this->isVisible() == false) { this->show(); m_trayIcon->hide(); }
        else { this->hide(); m_trayIcon->show(); }
    }
}

void GamepadDriver::changeMousePos()
{
    m_cursorEvent->changeMousePos(m_gamepad->axisLeftX(), m_gamepad->axisLeftY(), m_cursorSens,
                                  ui->sb_axisLeftX, ui->sb_axisLeftY, ui->sb_mousePosX, ui->sb_mousePosY);
}

void GamepadDriver::simulateMouseButtonClick(bool pressSignal)
{
    QGamepad* button = (QGamepad*)sender();
    if (button->buttonL1()) { m_bPress = 2; m_bRemove = 4; }
    if (button->buttonR1()) { m_bPress = 8; m_bRemove = 16; }
    if (button->buttonR2()) { m_bPress = 32; m_bRemove = 64; }

    if (pressSignal)    { mouse_event(m_bPress, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
    else                { mouse_event(m_bRemove, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
}

void GamepadDriver::simulateDoubleClick(bool pressSignal)
{
    if (pressSignal == false) { return; }
    m_cursorEvent->simulateDoubleClick();
}

void GamepadDriver::rotateMouseWheel()
{
    m_cursorEvent->rotateMouseWheel(m_gamepad->axisRightY(), m_wheelSens, ui->sb_axisRightY);
}

void GamepadDriver::changeSensitivity(int sliderValue)
{
    QSlider* currentSlider = (QSlider*)sender();
    if (currentSlider->objectName() == "sl_moveSensitivity" ) { m_cursorSens = sliderValue; }
    if (currentSlider->objectName() == "sl_wheelSensitivity" ) { m_wheelSens = sliderValue; }
}
