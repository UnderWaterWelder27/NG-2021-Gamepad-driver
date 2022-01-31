#include "threadaxischange.h"

void ThreadAxisChange::run()
{
    double x = 0;
    double y = 0;

    qDebug() << "THREAD";
    do {
        x = m_axisXValue;
        y = m_axisYValue;

        //for (int i = 1; i <= 25; i++) {
            QCursor::setPos(QCursor::pos().x() + (x * m_cursorSensetivity)/5,
                            QCursor::pos().y() + (y * m_cursorSensetivity)/5);
        //}
        QThread::msleep(100);

        if (x != m_gamepad->axisLeftX()) { emit gamepadLeftAxisX(x); }
        else if (y != m_gamepad->axisLeftY()) { emit gamepadLeftAxisY(y); }
    } while (!(y < 0.2 && y > -0.2));
}

ThreadAxisChange::ThreadAxisChange(QGamepad* gamepad, int sens)
{
    m_gamepad = gamepad;
    m_axisXValue = gamepad->axisLeftX();
    m_axisYValue = gamepad->axisLeftX();
    m_cursorSensetivity = sens;
}

