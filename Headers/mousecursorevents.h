#ifndef MOUSECURSOREVENTS_H
#define MOUSECURSOREVENTS_H

#include <QObject>
#include <QGamepad>
#include <QCursor>
#include <QLabel>
#include <QSpinBox>
#include <windows.h>

class MouseCursorEvents : public QObject
{
    Q_OBJECT

public:
    MouseCursorEvents();

    enum MouseEventFlags
    {
        LEFTDOWN = 2,
        LEFTUP = 4,
        RIGHTDOWN = 8,
        RIGHTUP = 16,
        MIDDLEDOWN = 32,
        MIDDLEUP = 64,
        WHEELROTATE = 0x0800,
        MOVE = 0x0001
    };

    void changeMousePos(double axisX, double axisY, int sens,
                        QDoubleSpinBox *axisLeftX, QDoubleSpinBox *axisLeftY);
    void simulateMouseButtonClick(QLabel *LB, QLabel *RB, QLabel *A);
    void simulateDoubleClick(QLabel *Y);
    void rotateMouseWheel(double axisY, int sens, QDoubleSpinBox *axisRightY);

private:
    int m_bPress;
    int m_bRemove;
};

#endif // MOUSECURSOREVENTS_H
