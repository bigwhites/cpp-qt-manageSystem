#include "mainwindow.h"
#include"logindia.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDia logDia;
    MainWindow w;
    logDia.exec();
    if(!logDia.canLog())
    {
        return 0;
    }
    w.show();
    return a.exec();
}
