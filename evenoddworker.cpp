#include "evenoddworker.h"

int EvenOddWorker::currentNumber = 0;
bool EvenOddWorker::isEvenTurn = true;
QMutex EvenOddWorker::mutex;
QWaitCondition EvenOddWorker::condition;

EvenOddWorker::EvenOddWorker(bool isEvenThread)
{
    m_isEvenThread = isEvenThread;
}
/**
 * @brief EvenOddWorker::process
 */
void EvenOddWorker::process()
{
    while (true)
    {
        mutex.lock();

        if (m_isEvenThread)
        {
            while (!isEvenTurn)
                condition.wait(&mutex);

            if (currentNumber > 10)
            {
                condition.wakeAll();
                mutex.unlock();
                break;
            }

            emit numberGenerated(currentNumber);
            currentNumber++;
            isEvenTurn = false;
        }
        else
        {
            while (isEvenTurn)
                condition.wait(&mutex);

            if (currentNumber > 9)
            {
                condition.wakeAll();
                mutex.unlock();
                break;
            }

            emit numberGenerated(currentNumber);
            currentNumber++;
            isEvenTurn = true;
        }

        condition.wakeAll();
        mutex.unlock();
    }

    emit finished();
}