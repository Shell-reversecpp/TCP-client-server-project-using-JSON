#include "myserver.h"


myserver::myserver()
{

}

myserver::~myserver()
{

}

void myserver::startServer()
{
    if(this->listen(QHostAddress::Any,5555))
    {
        qDebug() <<"Listening...";
    }
    else {
         qDebug() <<"Not listening!";
    }
}

void myserver::incomingConnection(qintptr socketDescriptor)
{
    //Новое соединение -> создаем сокет
    socket = new QTcpSocket(this);

    //Присвоение уникаольного номера соединения
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<socketDescriptor<<"Client has been connected";

    //Ответ клиенту в json
    socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");

    qDebug()<<"Sended to client connect status - YES";

}

void myserver::sockReady()
{
    //Получение данных от клиента , запись в Data
    Data = socket->readAll();
    qDebug()<<"Data: "<<Data;

    //Запись из Data в doc + error
    doc = QJsonDocument::fromJson(Data, &docError);

    if (docError.errorString().toInt()==QJsonParseError::NoError)
    {
        //разбор команды от клиента
        if((doc.object().value("type").toString() == "select") && (doc.object().value("params").toString() == "workers"))
        {
            QFile file;
            file.setFileName("../JsonData/workers.json");
            if(file.open(QIODevice::ReadOnly|QFile::Text))
            {

                //Считывание из файла
                QByteArray fromFile = file.readAll();

                //Присвоение итоговой переменной json + считывание из файла
                QByteArray itog = "{\"type\":\"resultSelect\",\"result\":"+fromFile+"}";

                //Отправить переменную пользователю
                socket->write(itog);
                //Ожидание для записи на всякий )
                socket->waitForBytesWritten(1000);
            }
            file.close();
        }
    }
}

void myserver::sockDisc()
{
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
