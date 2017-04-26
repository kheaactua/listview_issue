#ifndef BLOBSMODEL_H_VDJELPI1
#define BLOBSMODEL_H_VDJELPI1

#include <QAbstractListModel>
#include <QList>

#include "blob.h"

class BlobModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(unsigned int count READ rowCount NOTIFY countChanged)

public:
    enum BlobRoles {
        CentroidRole = Qt::UserRole + 1,
        UuidRole
    };

    BlobModel(QObject* parent = nullptr);

    /** Deletes all the blobs in the container */
    virtual ~BlobModel();

    /** Adds or updates a blob in the list */
    auto addBlob(const QString& uuid, const QVector3D& centroid) -> void;

    /** Returns number of blobs in the list */
    auto rowCount(const QModelIndex& parent = QModelIndex()) const -> int;

    /** Fetch blob from the list */
    auto data(const QModelIndex& index, int role = Qt::DisplayRole) const -> QVariant;

    /** Remove rows (blobs) from the model */
    auto removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) -> bool;

    /**
     * Check whether the UUID exists in the list.  Returns the index if the
     * collection contains the blob, otherwise returns -1 for now found.
     */
    auto Contains(const QString& uuid) -> int;

    /**
     * Clean out old blobs.  Returns true is any blobs were removed.
     */
    auto cleanBlobs() -> bool;

signals:

    void countChanged(unsigned int count);

public slots:

    /** Setter for blob lifetime */
    void setBlobLifeTime(unsigned int l);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    Q_DISABLE_COPY(BlobModel)

    /**
     * List of blobs.
     */
    QList<Blob*> blobs_;

    unsigned int blob_life_time_ = 5000;
};

#endif /* end of include guard: BLOBSMODEL_H_VDJELPI1 */

/* vim: set ts=4 sw=4 sts=4 expandtab ffs=unix,dos : */
