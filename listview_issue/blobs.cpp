#include "blobs.h"

#include <QtGlobal>
#include <QUuid>

Blobs::Blobs(QQuickItem* parent)
    : QQuickItem(parent)
    , blobs_{new BlobModel{this}}
    , cleanup_timer_{new QTimer(this)}
    , create_timer_{new QTimer(this)}
{
    connect(cleanup_timer_, SIGNAL(timeout()), this, SLOT(cleanBlobs()));
    cleanup_timer_->start(1000); // 1 second repetitive timer.

    connect(create_timer_, SIGNAL(timeout()), this, SLOT(autoCreateBlob()));
    create_timer_->start(3000); // 1 second repetitive timer.

    blobs_->setBlobLifeTime(blob_life_time_);
    connect(this, SIGNAL(blobLifeTimeChanged(unsigned int)), blobs_, SLOT(setBlobLifeTime(unsigned int)));
}

Blobs::~Blobs()
{
    delete blobs_;
    delete cleanup_timer_;
}

auto Blobs::newBlobData(const QString& uuid, const QVector3D& centroid) -> void
{
    blobs_->addBlob(uuid, centroid);
    Q_EMIT blobsChanged(blobs_);
}

auto Blobs::callRemoveBlobs() -> void
{
    blobs_->removeRows(0, 1);
}

auto Blobs::cleanBlobs() -> void
{
    if (blobs_->cleanBlobs())
    {
        Q_EMIT blobsChanged(blobs_);
    }
}

auto Blobs::autoCreateBlob() -> void
{
    auto uuid = QUuid::createUuid().toString();
    auto centroid = QVector3D(qrand(), 1, 1);

    qDebug() << "Creating uuid " << uuid;
    newBlobData(uuid, centroid);
}

/* vim: set ts=4 sw=4 sts=4 expandtab ffs=unix,dos : */
