#include "citymodel.h"

CityModel::CityModel(QObject *parent)
    : QAbstractTableModel(parent)
    , mDatabaseManager(DatabaseManager::instance())
    , mCities(mDatabaseManager.mCityDao.getAllCities())
{

}

QModelIndex CityModel::addCity(const City &city)
{
    int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);
    std::unique_ptr<City> newCity(new City(city));
    mDatabaseManager.mCityDao.addCity(*newCity);
    mCities->push_back(std::move(newCity));
    endInsertRows();
    return index(row, 0);
}

int CityModel::rowCount(const QModelIndex &parent) const
{
    return mCities->size();
}

int CityModel::columnCount(const QModelIndex &parent) const
{
    return 8;
}

QVariant CityModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }
    const City& city = *mCities->at(index.row());

    if (role != Qt::DisplayRole && role != Qt::EditRole) {
        return QVariant();
    }
    switch (index.column()) {
        case 0:
            return city.getPrefix();
        case 1:
            return city.getName();
        case 2:
            return city.getMapPoint();
        case 3:
            return static_cast<double>(city.getPopulation()) / 1000.0;
        case 4:
            return city.getCountry();
        case 5:
            return city.getLat();
        case 6:
            return city.getLon();
        case 7:
            return city.getDescription();
        default:
            return QVariant();
    }
}

bool CityModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!isIndexValid(index)) {
        return false;
    }

    City& city = *mCities->at(index.row());

    if (role != Qt::EditRole) {
        return false;
    }

    switch (index.column()) {
        case 0:
            city.setPrefix(value.toString());
            break;
        case 1:
            city.setName(value.toString());
            break;
        case 2:
            city.setMapPoint(value.toString());
            break;
        case 3:
            city.setPopulation(static_cast<qlonglong>(value.toDouble() * 1000.0));
            break;
        case 4:
            city.setCountry(value.toString());
            break;
        case 5:
            city.setLat(value.toReal());
            break;
        case 6:
            city.setLon(value.toReal());
            break;
        case 7:
            city.setDescription(value.toString());
            break;
        default:
            return false;

    }
    mDatabaseManager.mCityDao.updateCity(city);
    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

bool CityModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row >= mCities->size() || count <= 0 || row + count > mCities->size()) {
        return false;
    }
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = row; i < row + count; ++i) {
        mDatabaseManager.mCityDao.deleteCity(mCities->at(i)->getId());
    }
    mCities->erase(mCities->begin() + row, mCities->begin() + row + count);
    endRemoveRows();
    return true;
}

Qt::ItemFlags CityModel::flags(const QModelIndex &index) const
{
    if (!isIndexValid(index)) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QVariant CityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0: return "Префикс";
        case 1: return "Название";
        case 2: return "Точка привязки";
        case 3: return "Население, тыс чел.";
        case 4: return "Страна";
        case 5: return "Широта";
        case 6: return "Долгота";
        case 7: return "Описание";
        default: return QVariant();
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

bool CityModel::isIndexValid(const QModelIndex &index) const
{
    return index.isValid()
           && index.row() >= 0 && index.row() < rowCount()
           && index.column() >= 0 && index.column() < columnCount();
}
