#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QMenu>

MainWindow::MainWindow(int port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mServer(new QTcpServer(this))
    , mClients()
    , mBuffers()
{
    ui->setupUi(this);

    ui->connectionTableWidget->setColumnCount(3);
    ui->connectionTableWidget->setHorizontalHeaderLabels({"IP Address", "Port", "Last Message"});
    ui->connectionTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->connectionTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->connectionTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->connectionTableWidget, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    ui->portText->setText(QString("Port: ") + QString::number(port));

    mServer->listen(QHostAddress::Any, port);
    connect(mServer, &QTcpServer::newConnection, this, &MainWindow::clientConnected);
}

MainWindow::~MainWindow()
{
    for (auto client : mClients.keys()) {
        client->disconnectFromHost();
    }
    delete ui;
}

void MainWindow::clientConnected()
{
    auto client = mServer->nextPendingConnection();
    int row = ui->connectionTableWidget->rowCount();

    ui->connectionTableWidget->insertRow(row);
    auto* item = new QTableWidgetItem(client->peerAddress().toString());
    ui->connectionTableWidget->setItem(row, 0, item);
    ui->connectionTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(client->peerPort())));
    ui->connectionTableWidget->setItem(row, 2, new QTableWidgetItem(""));
    mClients[client] = item;

    connect(client, &QTcpSocket::readyRead, this, [this, client] {
        clientReadyRead(client);
    });
    connect(client, &QTcpSocket::disconnected, this, [this, client]() {
        clientDisconnected(client);
    });
    connect(client, &QTcpSocket::errorOccurred, this, [this, client](QAbstractSocket::SocketError) {
        clientDisconnected(client);
    });
}

void MainWindow::clientDisconnected(QTcpSocket *client)
{
    mBuffers.remove(client);
    auto* item = mClients.take(client);
    if (!item) {
        return;
    }
    int row = ui->connectionTableWidget->row(item);
    ui->connectionTableWidget->removeRow(row);
    client->deleteLater();
}

void MainWindow::clientReadyRead(QTcpSocket *client)
{
    auto data = client->readAll();
    qDebug() << data;
    mBuffers[client].append(data);

    int newlineIndex;
    while ((newlineIndex = mBuffers[client].indexOf('\n')) != -1) {
        QByteArray lineData = mBuffers[client].left(newlineIndex);
        mBuffers[client].remove(0, newlineIndex + 1);

        QString message = QString::fromUtf8(lineData);

        auto* item = mClients.value(client);
        if (!item) {
            continue;
        }

        int row = ui->connectionTableWidget->row(item);
        if (row < 0) {
            continue;
        }

        auto* msgItem = ui->connectionTableWidget->item(row, 2);
        msgItem->setText(message);
    }
}

void MainWindow::disconnectClient()
{
    int row = ui->connectionTableWidget->currentRow();
    if (row < 0) {
        return;
    }
    auto* item = ui->connectionTableWidget->item(row, 0);
    auto client = mClients.key(item);
    if (client) {
        client->disconnectFromHost();
    }
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    if (!ui->connectionTableWidget->itemAt(pos)) {
        return;
    }
    QMenu contextMenu(this);
    QAction* disconnectAction = contextMenu.addAction("Disconnect Client");
    connect(disconnectAction, &QAction::triggered, this, &MainWindow::disconnectClient);
    contextMenu.exec(ui->connectionTableWidget->viewport()->mapToGlobal(pos));
}
