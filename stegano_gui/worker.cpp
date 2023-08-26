#include "worker.h"
#include <QDebug>
#include <QThread>

Q_DECLARE_METATYPE(SteganoFsAdapter*)

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

void Worker::mountFolder(const QVariant& qAdapt, const QString& s)
{
    qDebug() << "RUnning thread: " << QThread::currentThreadId();

    auto *adapt = qvariant_cast<SteganoFsAdapter *>(qAdapt);

    try {
        adapt->mount(s.toStdString());
    }
    catch (int e) {
    }

    qDebug() << "Thread finished: " << QThread::currentThreadId();

}



