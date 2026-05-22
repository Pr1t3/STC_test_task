#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int port, QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void clientConnected();
    void clientDisconnected(QTcpSocket* client);
    void clientReadyRead(QTcpSocket* client);
    void disconnectClient();

    void showContextMenu(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QTcpServer* mServer;
    QMap<QTcpSocket*, QTableWidgetItem*> mClients;
    QMap<QTcpSocket*, QByteArray> mBuffers;
};
#endif // MAINWINDOW_H
