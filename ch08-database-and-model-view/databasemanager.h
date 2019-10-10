#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "trackdao.h"

#include <QString>

const QString DATABASE_FILENAME = "/../chinook.db";

class QSqlDatabase;

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    QSqlDatabase* mDatabase;

public:
    const TrackDao trackDao;
};

#endif // DATABASEMANAGER_H
