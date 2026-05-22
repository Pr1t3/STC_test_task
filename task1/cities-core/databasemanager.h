#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <memory>
#include "citydao.h"

class QSqlDatabase;

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    static void init(const QString& path);
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager& rhs) = delete;
    DatabaseManager& operator=(const DatabaseManager& rhs) = delete;

protected:
    DatabaseManager(const QString& path);

private:
    static DatabaseManager* mInstance;
    std::unique_ptr<QSqlDatabase> mDatabase;

public:
    const CityDao mCityDao;
};

#endif // DATABASEMANAGER_H
