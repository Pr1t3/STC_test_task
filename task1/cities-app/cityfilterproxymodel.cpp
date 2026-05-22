#include "cityfilterproxymodel.h"

CityFilterProxyModel::CityFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
     , populationFilter(0)
     , textFilter("")
{
}

void CityFilterProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);
    invalidateFilter();
}

bool CityFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex populationIndex = sourceModel()->index(source_row, 3, source_parent);
    QModelIndex prefixIndex = sourceModel()->index(source_row, 0, source_parent);
    QModelIndex nameIndex = sourceModel()->index(source_row, 1, source_parent);
    QModelIndex mapPointIndex = sourceModel()->index(source_row, 2, source_parent);
    QModelIndex descriptionIndex = sourceModel()->index(source_row, 7, source_parent);
    QModelIndex countryIndex = sourceModel()->index(source_row, 4, source_parent);
    if (!populationIndex.isValid() || !nameIndex.isValid()
        || !prefixIndex.isValid() || !mapPointIndex.isValid()
        || !descriptionIndex.isValid() || !countryIndex.isValid()) {
        return false;
    }
    qlonglong population = sourceModel()->data(populationIndex).toDouble() * 1000;
    QString name = sourceModel()->data(nameIndex).toString();
    QString prefix = sourceModel()->data(prefixIndex).toString();
    QString mapPoint = sourceModel()->data(mapPointIndex).toString();
    QString description = sourceModel()->data(descriptionIndex).toString();
    QString country = sourceModel()->data(countryIndex).toString();
    return population >= populationFilter
           && (name.contains(textFilter, Qt::CaseInsensitive)
           || prefix.contains(textFilter, Qt::CaseInsensitive)
           || mapPoint.contains(textFilter, Qt::CaseInsensitive)
           || description.contains(textFilter, Qt::CaseInsensitive)
           || country.contains(textFilter, Qt::CaseInsensitive));
}

CityModel *CityFilterProxyModel::getCityModel() const
{
    return static_cast<CityModel*>(sourceModel());
}

void CityFilterProxyModel::setPopulationFilter(qlonglong population)
{
    populationFilter = population;
    invalidateFilter();
}

void CityFilterProxyModel::setTextFilter(const QString &text)
{
    textFilter = text;
    invalidateFilter();
}
