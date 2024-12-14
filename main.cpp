#include "mainwindow.h"
#include <QFile>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile styleFile( ":/style/stylesheet.qss" );
    styleFile.open( QFile::ReadOnly );
    w.setStyleSheet(styleFile.readAll());
    w.show();
    return a.exec();
}
