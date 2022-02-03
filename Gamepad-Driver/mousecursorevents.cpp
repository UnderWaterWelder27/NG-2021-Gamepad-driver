#include "mousecursorevents.h"

MouseCursorEvents::MouseCursorEvents()
{
    m_bPress = 0;
    m_bRemove = 0;
}

void MouseCursorEvents::changeMousePos(double axisX, double axisY, int sens,
                                       QDoubleSpinBox *axisLeftX, QDoubleSpinBox *axisLeftY,
                                       QSpinBox *mousePosX, QSpinBox *mousePosY)
{
    mouse_event(MOVE, (axisX * sens)/7, 0, 0, 0);
    mouse_event(MOVE, 0, (axisY * sens)/7, 0, 0);

    axisLeftX->setValue(axisX);
    axisLeftY->setValue(axisY);
    mousePosX->setValue(QCursor::pos().x());
    mousePosY->setValue(QCursor::pos().y());
}

void MouseCursorEvents::simulateMouseButtonClick()
{
    QGamepad *button = (QGamepad*)sender();
    bool bClicked = false;

    if (button->buttonL1()) { bClicked = button->buttonL1(); m_bPress = LEFTDOWN; m_bRemove = LEFTUP; }
    if (button->buttonR1()) { bClicked = button->buttonR1(); m_bPress = RIGHTDOWN; m_bRemove = RIGHTUP; }
    if (button->buttonA()) { bClicked = button->buttonA(); m_bPress = MIDDLEDOWN; m_bRemove = MIDDLEUP; }

    if (bClicked == true)    { mouse_event(m_bPress, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
    else                     { mouse_event(m_bRemove, QCursor::pos().x(), QCursor::pos().y(), 0, 0); }
}

void MouseCursorEvents::simulateDoubleClick()
{
    QGamepad *button = (QGamepad*)sender();
    bool bClicked = button->buttonY();

    if (bClicked == false) { return; }
    mouse_event(LEFTDOWN | LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
    mouse_event(LEFTDOWN | LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
}

void MouseCursorEvents::rotateMouseWheel(double axisY, int sens, QDoubleSpinBox *axisRightY)
{
    if (axisY > 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(), -sens, 0); }
    if (axisY < 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(),  sens, 0); }
    axisRightY->setValue(axisY);
}
