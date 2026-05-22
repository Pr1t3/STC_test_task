#include "city.h"

City::City() {}

qlonglong City::getId() const
{
    return id;
}

void City::setId(qlonglong newId)
{
    id = newId;
}

qlonglong City::getParentId() const
{
    return parentId;
}

void City::setParentId(qlonglong newParentId)
{
    parentId = newParentId;
}

QString City::getType() const
{
    return type;
}

void City::setType(const QString &newType)
{
    type = newType;
}

QString City::getPrefix() const
{
    return prefix;
}

void City::setPrefix(const QString &newPrefix)
{
    prefix = newPrefix;
}

QString City::getName() const
{
    return name;
}

void City::setName(const QString &newName)
{
    name = newName;
}

QString City::getNameEng() const
{
    return nameEng;
}

void City::setNameEng(const QString &newNameEng)
{
    nameEng = newNameEng;
}

QString City::getMapPoint() const
{
    return mapPoint;
}

void City::setMapPoint(const QString &newMapPoint)
{
    mapPoint = newMapPoint;
}

qreal City::getLat() const
{
    return lat;
}

void City::setLat(qreal newLat)
{
    lat = newLat;
}

qreal City::getLon() const
{
    return lon;
}

void City::setLon(qreal newLon)
{
    lon = newLon;
}

qreal City::getAlt() const
{
    return alt;
}

void City::setAlt(qreal newAlt)
{
    alt = newAlt;
}

qlonglong City::getPopulation() const
{
    return population;
}

void City::setPopulation(qlonglong newPopulation)
{
    population = newPopulation;
}

QString City::getDescription() const
{
    return description;
}

void City::setDescription(const QString &newDescription)
{
    description = newDescription;
}

QString City::getCountry() const
{
    return country;
}

void City::setCountry(const QString &newCountry)
{
    country = newCountry;
}
