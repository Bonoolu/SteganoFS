#include "worker.h"
#include <QDebug>
#include <QThread>

Q_DECLARE_METATYPE(SteganoFsAdapter*)

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

void Worker::mountFolder(QVariant qAdapt, QString s)
{
    qDebug() << "RUnning thread: " << QThread::currentThreadId();

    SteganoFsAdapter *adapt = qvariant_cast<SteganoFsAdapter*>(qAdapt);

    adapt->mount(s.toStdString());

    qDebug() << "Thread finished: " << QThread::currentThreadId();
    emit mountFinished();
}



