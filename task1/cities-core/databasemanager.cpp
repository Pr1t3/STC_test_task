#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlError>

DatabaseManager* DatabaseManager::mInstance = nullptr;

DatabaseManager &DatabaseManager::instance()
{
    if (!mInstance) {
        throw std::runtime_error("DatabaseManager is not initialized.");
    }
    return *mInstance;
}

void DatabaseManager::init(const QString &path)
{
    if (mInstance) {
        return;
    }
    mInstance = new DatabaseManager(path);
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
}

DatabaseManager::DatabaseManager(const QString &path)
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
    , mCityDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);
    if (!mDatabase->open()) {
        throw std::runtime_error("Failed to open database: " + mDatabase->lastError().text().toStdString());
    }

    mCityDao.init();
}
