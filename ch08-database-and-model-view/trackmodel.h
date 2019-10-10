#ifndef TRACKMODEL_H
#define TRACKMODEL_H

#include "track.h"

#include <QAbstractTableModel>
#include <memory>

class DatabaseManager;

class TrackModel : public QAbstractTableModel
{
public:
    TrackModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
private:
    DatabaseManager& mDb;
    std::unique_ptr<std::vector<std::unique_ptr<Track>>> mTracks;
};

#endif // TRACKMODEL_H
