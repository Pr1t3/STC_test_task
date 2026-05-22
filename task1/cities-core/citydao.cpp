#include "citydao.h"
#include "city.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <vector>

CityDao::CityDao(QSqlDatabase &database)
    : mDatabase(database)
{
}

void CityDao::init() const
{
    if (!mDatabase.tables().contains("cities")) {
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE cities ") +
                   "(id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                   "parent_id INTEGER NOT NULL, " +
                   "type TEXT, " +
                   "prefix TEXT, " +
                   "name TEXT, " +
                   "name_eng TEXT, " +
                   "map_point TEXT, " +
                   "lat REAL, " +
                   "lon REAL, " +
                   "alt REAL, " +
                   "population INTEGER, " +
                   "description TEXT, " +
                   "country TEXT)");
    }
}

void CityDao::addCity(City &city) const
{
    QSqlQuery query(mDatabase);
    query.prepare(QString("INSERT INTO cities ") +
                  "(parent_id, type, prefix, name, name_eng, map_point, lat, " +
                  "lon, alt, population, description, country) " +
                  "VALUES (:parent_id, :type, :prefix, :name, :name_eng, :map_point, :lat, " +
                  ":lon, :alt, :population, :description, :country)");
    query.bindValue(":parent_id", city.getParentId());
    query.bindValue(":type", city.getType());
    query.bindValue(":prefix", city.getPrefix());
    query.bindValue(":name", city.getName());
    query.bindValue(":name_eng", city.getNameEng());
    query.bindValue(":map_point", city.getMapPoint());
    query.bindValue(":lat", city.getLat());
    query.bindValue(":lon", city.getLon());
    query.bindValue(":alt", city.getAlt());
    query.bindValue(":population", city.getPopulation());
    query.bindValue(":description", city.getDescription());
    query.bindValue(":country", city.getCountry());
    query.exec();
    city.setId(query.lastInsertId().toLongLong());
}

void CityDao::updateCity(const City &city) const
{
    QSqlQuery query(mDatabase);
    query.prepare(QString("UPDATE cities SET ") +
                  "prefix = :prefix, " +
                  "name = :name, " +
                  "map_point = :map_point, " +
                  "lat = :lat, " +
                  "lon = :lon, " +
                  "population = :population, " +
                  "description = :description, " +
                  "country = :country " +
                  "WHERE id = :id");
    query.bindValue(":id", city.getId());
    query.bindValue(":prefix", city.getPrefix());
    query.bindValue(":name", city.getName());
    query.bindValue(":map_point", city.getMapPoint());
    query.bindValue(":lat", city.getLat());
    query.bindValue(":lon", city.getLon());
    query.bindValue(":population", city.getPopulation());
    query.bindValue(":description", city.getDescription());
    query.bindValue(":country", city.getCountry());
    query.exec();
}

void CityDao::deleteCity(qlonglong cityId) const
{
    QSqlQuery query(mDatabase);
    query.prepare(QString("DELETE FROM cities WHERE id = :id"));
    query.bindValue(":id", cityId);
    query.exec();
}

std::unique_ptr<std::vector<std::unique_ptr<City>>> CityDao::getAllCities() const
{
    QSqlQuery query(mDatabase);
    query.exec(QString("SELECT * FROM cities"));
    std::unique_ptr<std::vector<std::unique_ptr<City>>> cities(new std::vector<std::unique_ptr<City>>());
    while (query.next()) {
        auto city = std::make_unique<City>();
        city->setId(query.value("id").toLongLong());
        city->setPrefix(query.value("prefix").toString());
        city->setName(query.value("name").toString());
        city->setMapPoint(query.value("map_point").toString());
        city->setLat(query.value("lat").toReal());
        city->setLon(query.value("lon").toReal());
        city->setPopulation(query.value("population").toLongLong());
        city->setDescription(query.value("description").toString());
        city->setCountry(query.value("country").toString());

        cities->push_back(std::move(city));
    }
    return cities;
}
