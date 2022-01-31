#ifndef THREADAXISCHANGE_H
#define THREADAXISCHANGE_H

#include <QObject>
#include <QThread>

class ThreadAxisChange : public QThread
{
    Q_OBJECT

    void run() override;

public:
    ThreadAxisChange();

signals:
    void gamepadLeftAxisX(double);
    void gamepadLeftAxisY(double);
};

#endif // THREADAXISCHANGE_H
