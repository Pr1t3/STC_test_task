#ifndef CITYFILTERPROXYMODEL_H
#define CITYFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "citymodel.h"

class CityFilterProxyModel : public QSortFilterProxyModel
{
public:
    CityFilterProxyModel(QObject* parent = nullptr);

    void setSourceModel(QAbstractItemModel *sourceModel) override;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    CityModel* getCityModel() const;

public slots:
    void setPopulationFilter(qlonglong population);
    void setTextFilter(const QString& text);

private:
    qlonglong populationFilter;
    QString textFilter;
};

#endif // CITYFILTERPROXYMODEL_H
