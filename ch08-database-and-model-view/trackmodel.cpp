#include "trackmodel.h"
#include "databasemanager.h"

#include <QColor>

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
