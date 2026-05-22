#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QRunnable>
#include <QAtomicInteger>

class Job : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Job(int taskNumber, long long iterationMax, QObject* parent = nullptr);
    void run() override;

signals:
    void resultReady(int taskNumber, double piValue);
    void progressChanged(int taskNumber, int progress);
    void started(int taskNumber);

public slots:
    void abort();

private:
    long long mIterationMax;
    int mTaskNumber;
    QAtomicInteger<bool> mAbort;
};

#endif // JOB_H
