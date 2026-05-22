#ifndef CITY_H
#define CITY_H

#include <QtGlobal>
#include <QString>

#include "cities-core_global.h"

class CITIES_CORE_EXPORT City
{
public:
    explicit City();

    qlonglong getId() const;
    void setId(qlonglong newId);
    qlonglong getParentId() const;
    void setParentId(qlonglong newParentId);
    QString getType() const;
    void setType(const QString &newType);
    QString getPrefix() const;
    void setPrefix(const QString &newPrefix);
    QString getName() const;
    void setName(const QString &newName);
    QString getNameEng() const;
    void setNameEng(const QString &newNameEng);
    QString getMapPoint() const;
    void setMapPoint(const QString &newMapPoint);
    qreal getLat() const;
    void setLat(qreal newLat);
    qreal getLon() const;
    void setLon(qreal newLon);
    qreal getAlt() const;
    void setAlt(qreal newAlt);
    qlonglong getPopulation() const;
    void setPopulation(qlonglong newPopulation);
    QString getDescription() const;
    void setDescription(const QString &newDescription);
    QString getCountry() const;
    void setCountry(const QString &newCountry);

private:
    qlonglong id;
    qlonglong parentId;
    QString type;
    QString prefix;
    QString name;
    QString nameEng;
    QString mapPoint;
    qreal lat;
    qreal lon;
    qreal alt;
    qlonglong population;
    QString description;
    QString country;
};

#endif // CITY_H
