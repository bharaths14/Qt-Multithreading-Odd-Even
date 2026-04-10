#ifndef EVENODDWORKER_H
#define EVENODDWORKER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>

class EvenOddWorker : public QObject
{
    Q_OBJECT

public:
    EvenOddWorker(bool isEvenThread);

signals:
    void numberGenerated(int number);
    void finished();

public slots:
    void process();

private:
    bool m_isEvenThread;

    static int currentNumber;
    static bool isEvenTurn;
    static QMutex mutex;
    static QWaitCondition condition;
};

#endif // EVENODDWORKER_H