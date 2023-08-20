#include "worker.h"
#include <QDebug>
#include <QThread>

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

void Worker::mountFolder(SteganoFsAdapter *adapt, std::string s)
{
    qDebug() << "RUnning thread: " << QThread::currentThreadId();

    adapt->mount(s);

    qDebug() << "Thread finished: " << QThread::currentThreadId();
    emit mountFinished();
}



