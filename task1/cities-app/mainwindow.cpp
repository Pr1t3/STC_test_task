#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mCityFilterProxyModel(nullptr)
    , mSelectionModel(nullptr)
{
    ui->setupUi(this);

    CityModel* mCityModel = new CityModel(this);
    mCityFilterProxyModel = new CityFilterProxyModel(this);
    mCityFilterProxyModel->setSourceModel(mCityModel);
    mSelectionModel = new QItemSelectionModel(mCityFilterProxyModel, this);

    ui->citiesTable->setModel(mCityFilterProxyModel);
    ui->citiesTable->setSelectionModel(mSelectionModel);

    ui->populationFilterSelector->addItem("Население не учитывать.", 0);
    ui->populationFilterSelector->addItem("Население от 1 тыс. чел.", 1000);
    ui->populationFilterSelector->addItem("Население от 10 тыс. чел.", 10000);
    ui->populationFilterSelector->addItem("Население от 25 тыс. чел.", 25000);
    ui->populationFilterSelector->addItem("Население от 50 тыс. чел.", 50000);
    ui->populationFilterSelector->addItem("Население от 100 тыс. чел.", 100000);
    ui->populationFilterSelector->addItem("Население от 250 тыс. чел.", 250000);
    ui->populationFilterSelector->addItem("Население от 500 тыс. чел.", 500000);
    ui->populationFilterSelector->addItem("Население от 1 млн. чел.", 1000000);
    ui->populationFilterSelector->addItem("Население от 2 млн. чел.", 2000000);
    ui->populationFilterSelector->addItem("Население от 5 млн. чел.", 5000000);
    ui->populationFilterSelector->addItem("Население от 10 млн. чел.", 10000000);

    connect(ui->addCityButton, &QPushButton::clicked, this, &MainWindow::addCity);
    connect(ui->deleteCityButton, &QPushButton::clicked, this, &MainWindow::deleteCity);
    connect(ui->populationFilterSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        qlonglong population = ui->populationFilterSelector->itemData(index).toLongLong();
        mCityFilterProxyModel->setPopulationFilter(population);
    });
    connect(ui->textFilterInput, &QLineEdit::textChanged, this, [this] (const QString& text) {
        mCityFilterProxyModel->setTextFilter(text);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteCity()
{
    if (mSelectionModel->selectedIndexes().isEmpty()) {
        return;
    }
    int row = mSelectionModel->currentIndex().row();
    mCityFilterProxyModel->removeRow(row);
}

void MainWindow::addCity()
{
    City city;
    city.setParentId(0);
    city.setType("");
    city.setPrefix("New");
    city.setName("City");
    city.setNameEng("");
    city.setMapPoint("");
    city.setLat(0.0);
    city.setLon(0.0);
    city.setAlt(0);
    city.setPopulation(0);
    city.setDescription("");
    city.setCountry("");
    QModelIndex newIndex = mCityFilterProxyModel->getCityModel()->addCity(city);
    mSelectionModel->setCurrentIndex(newIndex, QItemSelectionModel::SelectCurrent);
}

