#include "Headers/gamepaddriver.h"
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

    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setWindowTitle("XBox Gamepad Driver");
    this->setWindowIcon(QIcon(":/tmp/gamepad-icon.png"));
    m_trayIcon->setIcon(QIcon(":/tmp/gamepad-icon.png"));

    QMenu *trayMenu = new QMenu(this);
    QAction *showProgramWindow = new QAction("View window", this);
    QAction *quitProgram = new QAction("Exit", this);

    trayMenu->addAction(showProgramWindow);
    trayMenu->addAction(quitProgram);
    m_trayIcon->setContextMenu(trayMenu);
    m_trayIcon->show();
    m_trayIcon->setToolTip("XBox Gamepad Driver");

/// PRIVATE VARIABLES
    m_cursorSens = 15;
    m_wheelSens = 15;

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

/// CONNECT TRAY MENU EVENTS
    connect (showProgramWindow, &QAction::triggered, this, &QWidget::showNormal);
    connect (quitProgram, &QAction::triggered, this, &QCoreApplication::quit);
    connect (m_trayIcon, &QSystemTrayIcon::activated, this, &GamepadDriver::trayIconClicked);

/// CONNECT WINDOW CLOSE/HIDE BUTTONS
    connect (ui->b_closeWindow, &QPushButton::clicked, this, &GamepadDriver::windowCloseHide);
    connect (ui->b_hideWindow, &QPushButton::clicked, this, &GamepadDriver::windowCloseHide);
    connect (ui->b_fullWindow, &QPushButton::clicked, this, &GamepadDriver::windowCloseHide);

/// CHECK GAMEPAD CONNECTION
    connect (m_gamepad, &QGamepad::connectedChanged, this, &GamepadDriver::showConectionStatus);

/// CONNECT GAMEPAD KEYS
    connect (m_gamepad, &QGamepad::axisLeftXChanged, m_cursorEvent, [=]() {
        m_cursorEvent->changeMousePos(m_gamepad->axisLeftX(), m_gamepad->axisLeftY(), m_cursorSens,
                                      ui->sb_axisLeftX, ui->sb_axisLeftY);
    });
    connect (m_gamepad, &QGamepad::axisLeftYChanged, m_cursorEvent, [=]() {
        m_cursorEvent->changeMousePos(m_gamepad->axisLeftX(), m_gamepad->axisLeftY(), m_cursorSens,
                                      ui->sb_axisLeftX, ui->sb_axisLeftY);
    });
    connect (m_gamepad, &QGamepad::axisRightYChanged, m_cursorEvent, [=]() {
        m_cursorEvent->rotateMouseWheel(m_gamepad->axisRightY(), m_wheelSens, ui->sb_axisRightY);
    });
    connect (m_gamepad, &QGamepad::buttonL1Changed, m_cursorEvent, [=]() {
        m_cursorEvent->simulateMouseButtonClick(ui->l_LB, ui->l_RB, ui->l_A);
    });
    connect (m_gamepad, &QGamepad::buttonR1Changed, m_cursorEvent, [=]() {
        m_cursorEvent->simulateMouseButtonClick(ui->l_LB, ui->l_RB, ui->l_A);
    });
    connect (m_gamepad, &QGamepad::buttonAChanged, m_cursorEvent, [=]() {
        m_cursorEvent->simulateMouseButtonClick(ui->l_LB, ui->l_RB, ui->l_A);
    });
    connect (m_gamepad, &QGamepad::buttonYChanged , m_cursorEvent, [=]() {
        m_cursorEvent->simulateDoubleClick(ui->l_Y);
    });

/// CONNECT SENSITIVITY SLIDERS
    connect (ui->sl_moveSensitivity, &QSlider::valueChanged, this, &GamepadDriver::changeSensitivity);
    connect (ui->sl_wheelSensitivity, &QSlider::valueChanged, this, &GamepadDriver::changeSensitivity);
}

GamepadDriver::~GamepadDriver()
{
    delete ui;
}

void GamepadDriver::mousePressEvent(QMouseEvent *event)
{
    cursorPressPos = event->pos();
    QWidget::mousePressEvent(event);
}

void GamepadDriver::mouseMoveEvent(QMouseEvent *event)
{
    QPoint addToPos = event->pos() - cursorPressPos;
    QWidget *programWindow = window();
    if (programWindow)
        programWindow->move(programWindow->pos() + addToPos);
    QWidget::mouseMoveEvent(event);
}

void GamepadDriver::windowCloseHide()
{
    QPushButton *button = (QPushButton*)sender();

    if (button->text() == "X" && this->isVisible()) {
        this->hide();
    }
    if (button->text() == "__") {
        if (this->isVisible()) { this->showMinimized(); }
        else { this->showMaximized(); }
    }
    if (button->text() == "[ ]") {
        if (this->isMaximized()) { this->showNormal(); }
        else { this->showMaximized(); }
    }
}

void GamepadDriver::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (this->isVisible() == false) { this->show(); }
        else { this->hide(); }
    }
}

void GamepadDriver::showConectionStatus()
{
    if (m_gamepad->isConnected()) { ui->l_checkConnection->setText("Connected"); }
    else { ui->l_checkConnection->setText("Disconnected"); }
}

void GamepadDriver::changeSensitivity(int sliderValue)
{
    QSlider* currentSlider = (QSlider*)sender();
    if (currentSlider->objectName() == "sl_moveSensitivity" ) { m_cursorSens = sliderValue; }
    if (currentSlider->objectName() == "sl_wheelSensitivity" ) { m_wheelSens = sliderValue; }
}
