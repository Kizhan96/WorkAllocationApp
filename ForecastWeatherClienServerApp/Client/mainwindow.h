#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QStandardItem>
#include <QFile>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpSocket* socket;
    QByteArray Data;


    QJsonDocument doc;
    QJsonParseError docError;

public slots:
    void socketReady();
    void socketDisconnected();


private slots:
    void on_connectButton_clicked();

    void on_comboBox_activated();

    void on_LogInButton_clicked();

    void on_SignUpButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
