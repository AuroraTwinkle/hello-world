#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel *la=new QLabel("hello.world");
    la->show();


    return a.exec();
}
