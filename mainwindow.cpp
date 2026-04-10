#include "mainwindow.h"
#include "evenoddworker.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::startPrint);
}
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::startPrint
 * This function helps to start the thread
 */
void MainWindow::startPrint()
{
    mEvenThread = new QThread;
    mOddThread = new QThread;

    EvenOddWorker *evenWorker = new EvenOddWorker(true);
    EvenOddWorker *oddWorker = new EvenOddWorker(false);

    evenWorker->moveToThread(mEvenThread);
    oddWorker->moveToThread(mOddThread);

    connect(mEvenThread, &QThread::started, evenWorker, &EvenOddWorker::process);
    connect(mOddThread, &QThread::started, oddWorker, &EvenOddWorker::process);

    connect(evenWorker, &EvenOddWorker::numberGenerated, this, &MainWindow::updateUI);
    connect(oddWorker, &EvenOddWorker::numberGenerated, this, &MainWindow::updateUI);

    connect(evenWorker, &EvenOddWorker::finished, mEvenThread, &QThread::quit);
    connect(oddWorker, &EvenOddWorker::finished, mOddThread, &QThread::quit);

    connect(mEvenThread, &QThread::finished, evenWorker, &QObject::deleteLater);
    connect(mOddThread, &QThread::finished, oddWorker, &QObject::deleteLater);

    mEvenThread->start();
    mOddThread->start();
}
/**
 * @brief MainWindow::updateUI
 * This function print the numbers in ui
 * @param number
 */
void MainWindow::updateUI(int number)
{
    ui->txtPrintNumbers->append(QString::number(number));
}