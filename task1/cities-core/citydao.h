#ifndef CITYDAO_H
#define CITYDAO_H

#include <memory>
#include <vector>
#include <QtGlobal>

class QSqlDatabase;
class City;

class CityDao
{
public:
    CityDao(QSqlDatabase& database);
    void init() const;
    void addCity(City& city) const;
    void updateCity(const City& city) const;
    void deleteCity(qlonglong cityId) const;
    std::unique_ptr<std::vector<std::unique_ptr<City>>> getAllCities() const;
private:
    QSqlDatabase& mDatabase;
};

#endif // CITYDAO_H
