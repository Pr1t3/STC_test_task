#ifndef CITYMODEL_H
#define CITYMODEL_H

#include <QAbstractTableModel>
#include <QHash>
#include <memory>
#include <vector>

#include "city.h"
#include "databasemanager.h"

class CityModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CityModel(QObject* parent = nullptr);

    QModelIndex addCity(const City& city);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    bool isIndexValid(const QModelIndex& index) const;

    DatabaseManager& mDatabaseManager;
    std::unique_ptr<std::vector<std::unique_ptr<City>>> mCities;
};

#endif // CITYMODEL_H
