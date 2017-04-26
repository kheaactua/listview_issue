#ifndef BLOBSMODEL_H_DKP2BCRT
#define BLOBSMODEL_H_DKP2BCRT

#include <QTimer>
#include <QDebug>
#include <QtQuick/QQuickItem>
//#include <QtQuick/QQuickWindow>

#include "blob.h"
#include "blobmodel.h"

class Blobs : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(BlobModel* blobs MEMBER blobs_ READ blobs NOTIFY blobsChanged)

    Q_PROPERTY(unsigned int blobLifeTime MEMBER blob_life_time_ NOTIFY blobLifeTimeChanged)

   public:

    /**
     * Connects the windowChanged signal to handleWindowChanged
     */
    Blobs(QQuickItem* parent = nullptr);

    /**
     * Clears blob objects
     */
    virtual ~Blobs();

    Q_INVOKABLE void callRemoveBlobs();

    /**
     * Getter for pointer to blobs container (model)
     */
    auto blobs() -> BlobModel* { return blobs_; }

    Q_INVOKABLE void newBlobData(const QString& uuid, const QVector3D& centroid);

   signals:

    /**
     * Signal generated when blob data has been modified.
     */
    void blobsChanged(BlobModel* blobs);

    void maxBlobBufferChanged(const unsigned int max_buffer_size);

    void blobLifeTimeChanged(unsigned int life_time);

   public slots:

   /**
    * Clean out old blobs
    */
   void cleanBlobs();

   protected:

    /** Map of blobs indexed by blob uuid */
    BlobModel* blobs_;

    /** Timer to regualrly trigger the blob cleanup */
    QTimer* cleanup_timer_;

    unsigned int blob_life_time_ = 5000;
};

#endif /* end of include guard: BLOBSMODEL_H_DKP2BCRT */

/* vim: set ts=4 sw=4 sts=4 expandtab ffs=unix,dos : */
