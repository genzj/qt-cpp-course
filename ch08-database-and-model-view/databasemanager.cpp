#include "databasemanager.h"

#include <QtSql>
#include <QCoreApplication>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString& path)
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
    , trackDao(*mDatabase)
{
    qDebug() << "open database " << QCoreApplication::applicationDirPath().append(path);
    mDatabase->setDatabaseName(QCoreApplication::applicationDirPath().append(path));
    mDatabase->open();
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
    delete mDatabase;
}
