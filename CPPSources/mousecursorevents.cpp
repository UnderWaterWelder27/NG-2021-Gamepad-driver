#include "Headers/mousecursorevents.h"

MouseCursorEvents::MouseCursorEvents()
{
    m_bPress = 0;
    m_bRemove = 0;
}

void MouseCursorEvents::changeMousePos(double axisX, double axisY, int sens,
                                       QDoubleSpinBox *axisLeftX, QDoubleSpinBox *axisLeftY)
{
    mouse_event(MOVE, (axisX * sens)/7, 0, 0, 0);
    mouse_event(MOVE, 0, (axisY * sens)/7, 0, 0);

    axisLeftX->setValue(axisX);
    axisLeftY->setValue(axisY);
}

void MouseCursorEvents::simulateMouseButtonClick(QLabel *LB, QLabel *RB, QLabel *A)
{
    QGamepad *button = (QGamepad*)sender();
    QLabel *textLabel = LB;
    bool bClicked = false;

    if (button->buttonL1()) { bClicked = button->buttonL1(); m_bPress = LEFTDOWN; m_bRemove = LEFTUP; textLabel = LB; }
    if (button->buttonR1()) { bClicked = button->buttonR1(); m_bPress = RIGHTDOWN; m_bRemove = RIGHTUP; textLabel = RB; }
    if (button->buttonA()) { bClicked = button->buttonA(); m_bPress = MIDDLEDOWN; m_bRemove = MIDDLEUP; textLabel = A;}

    if (bClicked == true)    {
        mouse_event(m_bPress, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
        textLabel->setStyleSheet("background-color: rgb(25, 25, 26);\ncolor: rgb(255, 255, 255)");
    }
    else {
        mouse_event(m_bRemove, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
        LB->setStyleSheet("background-color: rgb(32, 33, 34);\ncolor: rgb(255, 255, 255)");
        RB->setStyleSheet("background-color: rgb(32, 33, 34);\ncolor: rgb(255, 255, 255)");
        A->setStyleSheet("background-color: rgb(32, 33, 34);\ncolor: rgb(255, 255, 255)");
    }
}

void MouseCursorEvents::simulateDoubleClick(QLabel *Y)
{
    QGamepad *button = (QGamepad*)sender();
    bool bClicked = button->buttonY();

    if (bClicked == false) {
        Y->setStyleSheet("background-color: rgb(32, 33, 34);\ncolor: rgb(255, 255, 255)");
        return;
    }
    Y->setStyleSheet("background-color: rgb(25, 25, 26);\ncolor: rgb(255, 255, 255)");
    mouse_event(LEFTDOWN | LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
    mouse_event(LEFTDOWN | LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
}

void MouseCursorEvents::rotateMouseWheel(double axisY, int sens, QDoubleSpinBox *axisRightY)
{
    if (axisY > 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(), -sens, 0); }
    if (axisY < 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(),  sens, 0); }
    axisRightY->setValue(axisY);
}
