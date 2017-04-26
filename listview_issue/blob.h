#ifndef BLOB_H_E5XVYAJ7
#define BLOB_H_E5XVYAJ7

#include <QDebug>
#include <QDateTime>
#include <QElapsedTimer>
#include <QObject>
#include <QMutex>
#include <QVector3D>

class Blob : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString uuid MEMBER uuid_ READ uuid CONSTANT)
    Q_PROPERTY(qint64 lastUpdated READ lastUpdated)
    Q_PROPERTY(QVector3D centroid MEMBER centroid_ READ centroid NOTIFY centroidChanged)

   public:

    /** Default constructor */
    explicit Blob(QObject* parent = nullptr) : QObject(parent) {}

    /** Construct with blob data */
    Blob(const QString& uuid, const QVector3D& centroid)
    {
        last_update_.start();

        Update(uuid, centroid);
    }

    ~Blob() = default;

    /** Serialize to string.  Mostly used for debugging */
    QString toQString() const;

    auto Update(const QString& uuid, const QVector3D& centroid) -> void
    {
        uuid_ = uuid;
        setCentroid(centroid);
        last_update_.restart();
    }

    /** Milliseconds since last update */
    auto lastUpdated() -> qint64 const { return last_update_.elapsed(); }

    /** Returns UUID of blob */
    auto uuid() const -> QString { return uuid_; };

    auto centroid() const -> QVector3D { return centroid_; }

   signals:
    void centroidChanged(const QVector3D&);

   protected:

    auto setCentroid(const QVector3D& vec) -> void
    {
        centroid_ = vec;
    }

    /** Target ID and name, from ATR */
    QString uuid_;

    /** X, Y, Z position of blob centroid */
    QVector3D centroid_;

    /**
     * Mutex protecting our point_buffer
     */
    QMutex buffer_mutex_;

    /**
     * Time since last update
     */
    QElapsedTimer last_update_;

   private:

    Q_DISABLE_COPY(Blob)

};

#endif /* end of include guard: BLOB_H_E5XVYAJ7 */

/* vim: set ts=4 sw=4 sts=4 expandtab ffs=unix,dos : */
