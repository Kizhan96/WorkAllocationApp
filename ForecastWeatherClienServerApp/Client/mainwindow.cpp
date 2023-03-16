#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->SrvIpAddrInput->setText("127.0.0.1");

    ui->comboBox->addItem("Makhachkala");
    ui->comboBox->addItem("Grozniy");
    ui->comboBox->addItem("London");
    ui->comboBox->addItem("Moscow");

    ui->LogInButton->setDisabled(true);
    ui->SignUpButton->setDisabled(true);
    ui->comboBox->setDisabled(true);

    socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(socketReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectButton_clicked()
{
    socket->connectToHost(ui->SrvIpAddrInput->text(),1996);
}

void MainWindow::socketDisconnected() {
    socket->deleteLater();
}

void MainWindow::socketReady() {
    if (socket->waitForConnected(500)) {
       socket->waitForReadyRead(500);
       Data = socket->readAll();

       doc = QJsonDocument::fromJson(Data, &docError);

       if (docError.errorString().toInt() == QJsonParseError::NoError) {
            if (doc.object().value("Command").toString() == "Connection" && doc.object().value("Status").toString() == "yes"){
//                QMessageBox::information(this, "Info", "Connected");
                ui->LogInButton->setDisabled(false);
                ui->SignUpButton->setDisabled(false);

            }

            else if (doc.object().value("Command").toString() == "WeatherData") {
                ui->messageWindow->append("City name:\t\t" + doc.object().value("City").toString());
                ui->messageWindow->append("Country:\t\t" + doc.object().value("Country").toString());
                ui->messageWindow->append("Date:\t\t" + doc.object().value("Date").toString());
                ui->messageWindow->append("Sunset time:\t\t" + doc.object().value("Sunset").toString());
                ui->messageWindow->append("Sunrise time:\t\t" + doc.object().value("Sunrise").toString());
                ui->messageWindow->append("Current temperature:\t" + doc.object().value("CurrentTemperature").toString());
                ui->messageWindow->append("Max temperature:\t" + doc.object().value("MaxTemperature").toString());
                ui->messageWindow->append("Min temperature:\t" + doc.object().value("MinTemperature").toString());
                ui->messageWindow->append("Temperature feels like:\t" + doc.object().value("FeelsLike_temperature").toString());
                ui->messageWindow->append("Humidity:\t\t" + doc.object().value("Humidity").toString());
                ui->messageWindow->append("Atmospheric pressure:\t" + doc.object().value("AtmosphericPressure").toString());
                ui->messageWindow->append("Wind:\t\t" + doc.object().value("Wind").toString());
                ui->messageWindow->append("Gusts:\t\t" + doc.object().value("Gusts").toString());
                ui->messageWindow->append("Clouds:\t\t" + doc.object().value("Clouds").toString());
                ui->messageWindow->append("WindDirection:\t\t" + doc.object().value("WindDirection").toString());
                ui->messageWindow->append("Precipitation:\t\t" + doc.object().value("Precipitation").toString());
                ui->messageWindow->append("Weather:\t\t" + doc.object().value("Weather").toString());
                ui->messageWindow->append("Visibility:\t\t" + doc.object().value("Visibility").toString());
                qDebug() << Data;
            }

            else if (doc.object().value("Command").toString() == "AuthStatus" && doc.object().value("Status").toString() == "Correct") {
                ui->comboBox->setDisabled(false);
                ui->LoginSignUpStatusLabel_2->setText("Good!");
                ui->LoginSignUpStatusLabel_2->setStyleSheet("color: rgb(50, 150, 70)");
            }

            else if (doc.object().value("Command").toString() == "AuthStatus" && doc.object().value("Status").toString() == "Incorrect") {
                ui->comboBox->setDisabled(true);
                ui->LoginSignUpStatusLabel_2->setText("Bad!");
                ui->LoginSignUpStatusLabel_2->setStyleSheet("color: rgb(255, 0, 0)");
            }

            else {
                qDebug() << Data;
                QMessageBox::information(this, "Info", "Not connected");
            }

        }
        else {
                QMessageBox::information(this, "Info", "Transfer format error" + docError.errorString());
        }

    }
}


void MainWindow::on_comboBox_activated()
{
    QString city = ui->comboBox->currentText();
    socket->write("{\"Command\":\"getWeather\",\"City\":\"" + city.toUtf8() + "\"}");
    ui->messageWindow->clear();
}



void MainWindow::on_LogInButton_clicked()
{
    QString login = ui->LoginInput->text();
    QString password = ui->PasswordInput->text();


    if (socket->isOpen()){
        socket->write("{\"Command\":\"login\",\"Username\":\"" + login.toUtf8() + "\",\"Password\":\"" + password.toUtf8() + "\"}");
        ui->LoginInput->clear();
        ui->PasswordInput->clear();
    }
    else {
        QMessageBox::information(this,"info", "error login button");
    }
}

void MainWindow::on_SignUpButton_clicked()
{
    QString login = ui->LoginInput->text();
    QString password = ui->PasswordInput->text();


    if (socket->isOpen()){
        socket->write("{\"Command\":\"signup\",\"Username\":\"" + login.toUtf8() + "\",\"Password\":\"" + password.toUtf8() + "\"}");
        ui->LoginInput->clear();
        ui->PasswordInput->clear();
    }
    else {
        QMessageBox::information(this,"info", "error sign up button");
    }
}
