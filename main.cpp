#include "mainwindow.h"
#include"logindia.h"
#include <QApplication>

//#define IS_DEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
#ifndef IS_DEBUG
    LoginDia logDia;
    logDia.exec();
    if(!logDia.canLog())
    {
        return 0;
    }

#endif
    w.show();
    return a.exec();
}
