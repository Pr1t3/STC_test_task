#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QThreadPool>

const long long ITERATION_MAX = 100000000;
const int TASK_COUNT = 50;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tasksTableWidget->setColumnCount(3);
    ui->tasksTableWidget->setRowCount(TASK_COUNT);
    ui->tasksTableWidget->setHorizontalHeaderLabels({"Task number", "Progress", "Result"});
    ui->tasksTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < TASK_COUNT; ++i) {
        Job* job = createJob(i);
        connect(job, &Job::resultReady, this, &MainWindow::onResultReady);
        connect(job, &Job::progressChanged, this, &MainWindow::onProgressChanged);
        connect(job, &Job::started, this, &MainWindow::onJobStarted);
        connect(this, &MainWindow::abortAllJobs, job, &Job::abort);
        QThreadPool::globalInstance()->start(job);

        ui->tasksTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        ui->tasksTableWidget->setItem(i, 1, new QTableWidgetItem("0%"));
        ui->tasksTableWidget->setItem(i, 2, new QTableWidgetItem("Waiting"));
    }
}

MainWindow::~MainWindow()
{
    QThreadPool::globalInstance()->clear();
    emit abortAllJobs();
    delete ui;
}

void MainWindow::onResultReady(int taskNumber, double piValue)
{
    ui->tasksTableWidget->item(taskNumber, 1)->setText("100%");
    ui->tasksTableWidget->item(taskNumber, 2)->setText("PI is: " + QString::number(piValue));
}

void MainWindow::onProgressChanged(int taskNumber, int progress)
{
    ui->tasksTableWidget->item(taskNumber, 1)->setText(QString::number(progress) + "%");
}

void MainWindow::onJobStarted(int taskNumber)
{
    ui->tasksTableWidget->setItem(taskNumber, 2, new QTableWidgetItem("In progress"));
}

Job* MainWindow::createJob(int taskNumber)
{
    return new Job(taskNumber, ITERATION_MAX);
}
