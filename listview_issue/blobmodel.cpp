#include "blobmodel.h"

BlobModel::BlobModel(QObject* parent)
    : QAbstractListModel(parent)
{}

BlobModel::~BlobModel()
{
    removeRows(0, rowCount());
}

auto BlobModel::setBlobLifeTime(unsigned int l) -> void
{
    blob_life_time_ = l;
}


auto BlobModel::Contains(const QString& uuid) -> int
{
    // Using canonical for here in order to get the index of an element
    for (int i = 0; i<rowCount(); i++)
    {
        auto b = blobs_[i];
        if (b->uuid() == uuid)
            return i;
    }

    return -1;
}

auto BlobModel::cleanBlobs() -> bool
{
    auto lifetime = static_cast<qint64>(blob_life_time_);

    QList<int> indicies;

    for (int idx = 0; idx<blobs_.size(); idx++)
    {
        if (blobs_[idx]->lastUpdated() > lifetime) indicies.push_back(idx);
    }

    auto changed = indicies.size() > 0;
    while (indicies.size() > 0)
    {
        removeRows(indicies[0], 1);

        if (indicies.size() > 0) {
            indicies.removeFirst();

            // Decrement all remiaing indicies.
            std::transform(indicies.begin(), indicies.end(), indicies.begin(),
                [](const int i) { return i-1; });
        }
    }

    return changed;
}


auto BlobModel::rowCount(const QModelIndex& parent) const -> int
{
    Q_UNUSED(parent);
    return blobs_.size();
}

auto BlobModel::data(const QModelIndex& index, int role) const -> QVariant
{
    if(!index.isValid())
    {
        qWarning("Invalid index used.");
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= blobs_.count())
    {
        qWarning("Invalid row requested.");
        return QVariant();
    }

    auto blob = blobs_[index.row()];

    if (role == CentroidRole)
        return blob->centroid();
    else if (role == UuidRole)
        return blob->uuid();
    return QVariant();
}

auto BlobModel::addBlob(const QString& uuid, const QVector3D& centroid) -> void
{
    const auto idx = Contains(uuid);
    if (-1 != idx)
    {
        blobs_[idx]->Update(uuid, centroid);
        Q_EMIT dataChanged(createIndex(idx, 0), createIndex(idx, 0));
    }
    else
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        blobs_ << new Blob{uuid, centroid};
        endInsertRows();

        Q_EMIT dataChanged(createIndex(rowCount(), 0), createIndex(rowCount(), 0));
    }
}

auto BlobModel::removeRows(int row, int count, const QModelIndex& parent) -> bool
{
    if (count < 0)
    {
        qFatal("Invalid count provided in BlobModel::removeRows");
        return false;
    }

    if (row + count > rowCount())
        return false;
    if (!count)
        return true;

    beginRemoveRows(parent, row, row+count - 1);
    while (count > 0)
    {
        auto b = blobs_.takeAt(row);
        qDebug() << "Deleting " << b->uuid();
        delete b;
        count--;
    }
    endRemoveRows();

    Q_EMIT countChanged(rowCount());

    return true;
}

auto BlobModel::roleNames() const -> QHash<int, QByteArray>
{
    QHash<int, QByteArray> roles;
    roles[CentroidRole] = "centroid";
    roles[UuidRole]  = "uuid";
    return roles;
}

/* vim: set ts=4 sw=4 sts=4 expandtab ffs=unix,dos : */
