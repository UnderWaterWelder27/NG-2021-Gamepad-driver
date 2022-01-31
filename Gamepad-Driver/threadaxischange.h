#ifndef THREADAXISCHANGE_H
#define THREADAXISCHANGE_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QGamepad>
#include <QCursor>

class ThreadAxisChange : public QThread
{
    Q_OBJECT

    void run() override;

public:
    ThreadAxisChange(QGamepad* gamepad, double axisX, double axisY);

private:
    QGamepad *m_gamepad;
    double m_axisXValue;
    double m_axisYValue;

signals:
    void gamepadLeftAxisX(double);
    void gamepadLeftAxisY(double);
};

#endif // THREADAXISCHANGE_H
