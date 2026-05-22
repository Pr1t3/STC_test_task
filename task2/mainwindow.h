#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "job.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void onResultReady(int taskNumber, double piValue);
    void onProgressChanged(int taskNumber, int progress);
    void onJobStarted(int taskNumber);

signals:
    void abortAllJobs();

private:
    Job* createJob(int taskNumber);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
