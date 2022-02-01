#include "mousecursorevents.h"

MouseCursorEvents::MouseCursorEvents()
{

}

void MouseCursorEvents::changeMousePos(double axisX, double axisY, int sens,
                                       QDoubleSpinBox *axisLeftX, QDoubleSpinBox *axisLeftY, QSpinBox *mousePosX, QSpinBox *mousePosY)
{
    mouse_event(MOVE, (axisX * sens)/7, 0, 0, 0);
    mouse_event(MOVE, 0, (axisY * sens)/7, 0, 0);

    axisLeftX->setValue(axisX);
    axisLeftY->setValue(axisY);
    mousePosX->setValue(QCursor::pos().x());
    mousePosY->setValue(QCursor::pos().y());
}

void MouseCursorEvents::simulateDoubleClick()
{
    mouse_event(LEFTDOWN | LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
    mouse_event(LEFTDOWN | LEFTUP, QCursor::pos().x(), QCursor::pos().y(), 0, 0);
}

void MouseCursorEvents::rotateMouseWheel(double axisY, int sens, QDoubleSpinBox *axisRightY)
{
    if (axisY > 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(), -sens, 0); }
    if (axisY < 0) { mouse_event(WHEELROTATE, QCursor::pos().x(), QCursor::pos().y(),  sens, 0); }
    axisRightY->setValue(axisY);
}
