#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "../cpp-wrapper/SteganoFsAdapter.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:
    void mountFinished();

public slots:
    void mountFolder(SteganoFsAdapter *adapt, std::string s);

};

#endif // WORKER_H