#include "MyChatSrv.h"

int clientID;

myserver::myserver() {
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    QString pathToDB = QDir::currentPath() + "/auth.sqlite";
    myDB.setDatabaseName(pathToDB);

    QFileInfo checkFile(pathToDB);


    if (checkFile.isFile()) {
        if (myDB.open()) {
            qDebug() << "[+] Connected to Database File";
        }
        else {
            qDebug() << "[!] Database File was not opened";
        }
    }
    else {
        qDebug() << "[!] Database File does not exist" << ' ' << QDir::currentPath();
    }

    if (!myDB.isOpen()) {
            qDebug() << "No connection to Database";
            return;
    }
}

myserver::~myserver() {
    myDB.close();
}

void myserver::startServer() {
    if (this->listen(QHostAddress::Any,1996)) {
        qDebug()<<"Listening";
    }
    else {
        qDebug()<<"Not listening";
    }
}

void myserver::incomingConnection(int socketDescriptor) {
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    clientID = socketDescriptor;

    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug() <<"Client" << clientID << " connected";

    socket->write("{\"Command\":\"Connection\", \"Status\":\"yes\"}");
    qDebug()<<"Send client connect status - YES";
}

void myserver::sockReady()
{
    QSqlQuery qry;
    QString Username;
    QString Password;

    Data = socket->readAll();
    doc = QJsonDocument::fromJson(Data, &docError);

    if (docError.errorString().toInt() == QJsonParseError::NoError) {
        if (doc.object().value("Command").toString() == "login") {
            if (qry.exec("SELECT Username, Password FROM Users WHERE Username=\'" + doc.object().value("Username").toString() + "\' AND Password=\'" + doc.object().value("Password").toString() + "\'")) {
                    if (qry.next()) {
                        qDebug() << ("[+] Valid Username and Password");
                        socket->write("{\"Command\":\"AuthStatus\",\"Status\":\"Correct\"}");
                        qDebug() << "Login was successful";
                    }
                    else {
                       qDebug() << ("[-] Wrong Username or Password");
                       socket->write("{\"Command\":\"AuthStatus\",\"Status\":\"Incorrect\"}");
                    }
                }
                else {
                    qDebug() << ("[-] Wrong query");
                }
            }

        if (doc.object().value("Command").toString() == "signup") {
//            qDebug() << !qry.exec("SELECT EXISTS (SELECT 1 FROM Users WHERE Username='SmartCO');");
//            if (qry.exec("SELECT EXISTS (SELECT * FROM Users WHERE Username=\'" + doc.object().value("Username").toString() + "\'")){
//
//            }

            qry.prepare("INSERT INTO Users (Username, Password) "
                         "VALUES (:Username, :Password)");
            qry.bindValue(":Username", doc.object().value("Username").toString());
            qry.bindValue(":Password", doc.object().value("Password").toString());
            qry.exec();
        }

        if (doc.object().value("Command").toString() == "getWeather") {
            //получить данные о погоде
            QNetworkAccessManager *manager = new QNetworkAccessManager(this);
            QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("http://api.openweathermap.org/data/2.5/weather?q=" + doc.object().value("City").toString() + "&mode=xml&appid=a7be801c8fde9619bc54084aaed99cc3")));

            QEventLoop loop;
            connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec();

            QByteArray Data = reply->readAll();
            QString str = QString::fromUtf8(Data);

            reply->deleteLater();
            manager->deleteLater();

            QXmlStreamReader reader(str);

            QString City;
            QString Country;
            QString Date;
            QString Sunset;
            QString Sunrise;
            QString CurrentTemperature;
            QString MaxTemperature;
            QString MinTemperature;
            QString FeelsLike_temperature;
            QString Humidity;
            QString AtmosphericPressure;
            QString Wind;
            QString Gusts;
            QString Clouds;
            QString WindDirection;
            QString Precipitation;
            QString Weather;
            QString Visibility;


            while(!reader.atEnd()){
                if(reader.isStartElement()){
                    QString name = reader.name().toString();

                    if(name == "city"){
                        QXmlStreamAttributes attributes = reader.attributes();
                        if(attributes.hasAttribute("name")){
                            qDebug() << "City:" << attributes.value("name").toString();
                            City = attributes.value("name").toUtf8();

                        }
                    }

                    if(name=="country"){
                        Country = reader.readElementText();
                    }

                    if(name == "sun"){
                        QXmlStreamAttributes attributes = reader.attributes();
                        if(attributes.hasAttribute("set")){
                            qDebug() << "Date:" << attributes.value("set").toString().trimmed().left(10);
                            Date = attributes.value("set").toString().trimmed().left(10);

                            QString set = attributes.value("set").toString().trimmed().right(8);
                            QString GMT = QString::number(set.left(2).toInt() + 3);
                            QString sunset = GMT + attributes.value("set").toString().trimmed().right(6);
                            qDebug() << "Sunset:" << sunset;
                            Sunset = GMT + attributes.value("set").toString().trimmed().right(6);
                        }

                        if(attributes.hasAttribute("rise")){
                            QString rise = attributes.value("rise").toString().trimmed().right(8);
                            QString GMT = QString::number(rise.left(2).toInt() + 3);
                            QString sunrise = GMT + attributes.value("set").toString().trimmed().right(6);
                            qDebug() << "Sunrise:" << sunrise;
                            Sunrise = GMT + attributes.value("set").toString().trimmed().right(6);
                        }

                    }

                    if (name == "temperature") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug() << "Current temp.:" << attributes.value("value").toFloat() - 273.15;
                             CurrentTemperature = QString::number(attributes.value("value").toFloat() - 273.15);
                         }
                         if(attributes.hasAttribute("max")){
                             qDebug() << "Max temp.:" << attributes.value("max").toFloat() - 273.15;
                             MaxTemperature = QString::number(attributes.value("max").toFloat() - 273.15);
                         }
                         if(attributes.hasAttribute("min")){
                             qDebug() << "Min temp.:" << attributes.value("min").toDouble() - 273.15;
                             MinTemperature = QString::number(attributes.value("min").toFloat() - 273.15);
                         }
                    }

                    if (name == "feels_like") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug() << "Feels like:" << attributes.value("value").toFloat() - 273.15;
                             FeelsLike_temperature = QString::number(attributes.value("value").toFloat() - 273.15);
                         }
                    }

                    if (name == "humidity") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug() << "Humidity:" << attributes.value("value").toString();
                             Humidity = attributes.value("value").toString();
                         }
                    }

                    if (name == "pressure") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug() << "Pressure:" << attributes.value("value").toString();
                             AtmosphericPressure = attributes.value("value").toString();
                         }
                    }

                    if (name == "speed") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug().noquote() << "Wind:" << attributes.value("value").toString();
                             Wind = attributes.value("value").toString();
                         }
                    }

                    if (name == "gusts") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug() << "Gusts:" << attributes.value("value").toString();
                             Gusts = attributes.value("value").toString();
                         }
                    }

                    if (name == "clouds") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug() << "Clouds:" << attributes.value("value");
                             Clouds = attributes.value("value").toString();
                         }
                    }

                    if (name == "direction") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("name")){
                             qDebug() << "Wind direction:" << attributes.value("name").toString();
                             WindDirection = attributes.value("name").toString();
                         }
                    }

                    if (name == "visibility") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug() << "Visibility:" << attributes.value("value").toString();
                             Visibility = attributes.value("value").toString();
                         }
                    }

                    if (name == "precipitation") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("mode")){
                             qDebug() << "Precipitation:" << attributes.value("mode").toString();
                             Precipitation = attributes.value("mode").toString();
                         }
                    }

                    if (name == "weather") {
                         QXmlStreamAttributes attributes = reader.attributes();
                         if(attributes.hasAttribute("value")){
                             qDebug() << "Weather:" << attributes.value("value").toString();
                             Weather = attributes.value("value").toString();
                         }
                    }

                }

                if (reader.isEndElement()){
                    QString name = reader.name().toString();
                    if(name == "current"){
                        qDebug() << "End";
                    }
                }

                reader.readNext();
            }

            if(reader.hasError()){
                qDebug() << "error loading xml" << reader.errorString();
            }


//            QString WheatherData = "\"City\":" + City;

            socket->write("{\"Command\":\"WeatherData\","
                         " \"City\":\"" + City.toUtf8() + "\","
                         " \"Country\":\"" + Country.toUtf8() + "\","
                         " \"Date\":\"" + Date.toUtf8() + "\","
                         " \"Sunset\":\"" + Sunset.toUtf8() + "\","
                         " \"Sunrise\":\"" + Sunrise.toUtf8() + "\","
                         " \"CurrentTemperature\":\"" + CurrentTemperature.toUtf8() + "\","
                         " \"MaxTemperature\":\"" + MaxTemperature.toUtf8() + "\","
                         " \"MinTemperature\":\"" + MinTemperature.toUtf8() + "\","
                         " \"FeelsLike_temperature\":\"" + FeelsLike_temperature.toUtf8() + "\","
                         " \"Humidity\":\"" + Humidity.toUtf8() + "\","
                         " \"AtmosphericPressure\":\"" + AtmosphericPressure.toUtf8() + "\","
                         " \"Wind\":\"" + Wind.toUtf8() + "\","
                         " \"Gusts\":\"" + Gusts.toUtf8() + "\","
                         " \"Clouds\":\"" + Clouds.toUtf8() + "\","
                         " \"WindDirection\":\"" + WindDirection.toUtf8() + "\","
                         " \"Precipitation\":\"" + Precipitation.toUtf8() + "\","
                         " \"Weather\":\"" + Weather.toUtf8() + "\","
                         " \"Visibility\":\"" + Visibility.toUtf8() + "\"}");
        }

    }

    if (!myDB.isOpen()) {
            qDebug() << "No connection to Database";
            return;
        }


}

void myserver::sockDisc()
{

    qDebug() << "User " << clientID  << " disconnected";
    socket->deleteLater();
}
