#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("TCP Server Application");
    parser.addHelpOption();

    QCommandLineOption portOption(QStringList() << "p" << "port", "Port to listen on", "port", "5000");
    parser.addOption(portOption);
    parser.process(a);

    int port = parser.value(portOption).toInt();

    MainWindow w(port);
    w.show();
    return QApplication::exec();
}
