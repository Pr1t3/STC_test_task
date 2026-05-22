#include "mainwindow.h"
#include "databasemanager.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Cities Database Editor");
    parser.addHelpOption();

    QCommandLineOption databasePathOption(QStringList() << "d" << "database", "Path to the cities database file.", "path");
    parser.addOption(databasePathOption);
    parser.process(a);

    QString databasePath = parser.value(databasePathOption);
    if (databasePath.isEmpty()) {
        databasePath = "cities.db3";
    }
    try {
        DatabaseManager::init(databasePath);
    } catch (const std::exception& e) {
        qCritical() << "Failed to initialize database:" << e.what();
        return 1;
    }

    MainWindow w;
    w.show();
    return QApplication::exec();
}
