#include "job.h"

#include <random>

Job::Job(int taskNumber, long long iterationMax, QObject *parent)
    : QObject(parent)
    , mIterationMax(iterationMax)
    , mTaskNumber(taskNumber)
{
}

void Job::run()
{
    emit started(mTaskNumber);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    long long pointsInside = 0;
    long long step = mIterationMax / 100;
    for (long long i = 0; i < mIterationMax; ++i) {
        if (mAbort.loadRelaxed()) {
            return;
        }
        double x = distribution(generator);
        double y = distribution(generator);

        if ((x * x + y * y) <= 1.0) {
            ++pointsInside;
        }
        int newProgress = static_cast<int>(i / step);
        if (i % step == 0) {
            emit progressChanged(mTaskNumber, static_cast<int>(newProgress));
        }
    }

    double pi = 4.0 * static_cast<double>(pointsInside) / static_cast<double>(mIterationMax);
    emit resultReady(mTaskNumber, pi);
}

void Job::abort()
{
    mAbort.storeRelaxed(true);
}

