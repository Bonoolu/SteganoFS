#include "worker.h"
#include <QDebug>
#include <QThread>

Q_DECLARE_METATYPE(SteganoFsAdapter*)

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

// Worker class for mounting folders

void Worker::mountFolder(const QVariant& qAdapt, const QString& s)
{

    auto *adapt = qvariant_cast<SteganoFsAdapter *>(qAdapt);

    try {
        adapt->mount(s.toStdString());
    }
    catch (int e) {
    }

}



