#ifndef TRACKDAO_H
#define TRACKDAO_H

#include <memory>
#include <vector>

#include "track.h"

class QSqlDatabase;

class TrackDao
{
public:
    TrackDao(QSqlDatabase& database);
    std::unique_ptr<std::vector<std::unique_ptr<Track>>> tracks() const;

private:
    QSqlDatabase& mDatabase;
};

#endif // TRACKDAO_H
