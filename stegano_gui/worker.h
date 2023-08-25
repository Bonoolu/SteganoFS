#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "../cpp-wrapper/SteganoFsAdapter.h"

/*!
 * \class Worker
 * \brief The Worker class represents a worker object that performs tasks asynchronously.
 *
 * This class inherits from QObject and provides slots for performing various tasks.
 */
class Worker: public QObject
{
Q_OBJECT
public:
    /*!
     * \brief Constructor for the Worker class.
     * \param parent The parent QObject for this worker.
     */
    explicit Worker(QObject *parent = nullptr);

public slots:
    /*!
     * \brief Mounts a folder using the provided adapter and path.
     * \param qAdapt The QVariant containing a pointer to the SteganoFsAdapter.
     * \param s The path to the folder to be mounted.
     */
    void mountFolder(const QVariant& qAdapt, const QString& s);

};

#endif // WORKER_H
