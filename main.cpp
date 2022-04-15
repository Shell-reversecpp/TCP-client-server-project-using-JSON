#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Создание объекта от собственного класа myserver
    myserver Server;
    Server.startServer();
    return a.exec();
}
