#ifndef MYSERVER_H
#define MYSERVER_H


#include <QTcpServer>
#include <QTcpSocket>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <QFile>

class myserver : public QTcpServer
{
    Q_OBJECT
public:

   myserver();
   ~myserver();


   //Переменные
   QTcpSocket *socket;

   //Хранение данных для передачи
   QByteArray Data;

   QJsonDocument doc;
   QJsonParseError docError;

   //Методы
public slots:
   void startServer();

   //socketDescriptor - уникальный номер соединеия
   void incomingConnection(qintptr socketDescriptor);
   void sockReady();
   void sockDisc();
};

#endif // MYSERVER_H



