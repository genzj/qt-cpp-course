#include "trackmodel.h"
#include "databasemanager.h"

#include <QColor>

#include <algorithm>

TrackModel::TrackModel()
    : mDb(DatabaseManager::instance())
    , mTracks(mDb.trackDao.tracks())
{

}


int TrackModel::rowCount(const QModelIndex &) const
{
    return static_cast<int>(mTracks->size());
}

int TrackModel::columnCount(const QModelIndex &) const
{
    return 4;
}

QVariant TrackModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0:
            return QVariant("ID");
        case 1:
            return QVariant("Name");
        case 2:
            return QVariant("Album");
        case 3:
            return QVariant("Artist");
        }
    }
    return QVariant();
}

QVariant TrackModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case 0:
            return QVariant(
                        mTracks->at(
                            static_cast<size_t>(index.row()))->id()
                        );
        case 1:
            return QVariant(
                        mTracks->at(
                            static_cast<size_t>(index.row()))->name()
                        );
        case 2:
            return QVariant(
                        mTracks->at(
                            static_cast<size_t>(index.row()))->album()
                        );
        case 3:
            return QVariant(
                        mTracks->at(
                            static_cast<size_t>(index.row()))->artist()
                        );
        }
    }
    else if (role == Qt::BackgroundRole)
    {
        return index.row() % 2 ? QVariant(QColor(Qt::lightGray)) : QVariant();
    }
    return QVariant();
}

#include <QDebug>
void TrackModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << "sort.." << column << " " << order;
    auto cmp = [column, order](const std::unique_ptr<Track> &t1, const std::unique_ptr<Track> &t2) {
        bool ret = true;
        switch (column) {
        case 0:
            ret = t1->id() < t2->id();
            break;
        case 1:
            ret = t1->name() < t2->name() || (t1->name() == t2->name() && t1->id() < t2->id());
            break;
        case 2:
            ret = t1->album() < t2->album() || (t1->album() == t2->album() && t1->id() < t2->id());
            break;
        case 3:
            ret = t1->artist() < t2->artist() || (t1->artist() == t2->artist() && t1->id() < t2->id());
            break;
        }
        return order == Qt::AscendingOrder ? ret : !ret;
    };
    emit layoutAboutToBeChanged(QList<QPersistentModelIndex>(), QAbstractItemModel::VerticalSortHint);
    std::sort(mTracks->begin(), mTracks->end(), cmp);
    emit layoutChanged(QList<QPersistentModelIndex>(), QAbstractItemModel::VerticalSortHint);
}
