#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // //setapp style sheet
    // QFile stylesheetfile("C:/Users/PARSIAN/Downloads/Hookmark/Hookmark.qss");
    // stylesheetfile.open(QFile::ReadOnly);
    // QString stylesheet=QLatin1String(stylesheetfile.readAll());
    // a.setStyleSheet(stylesheet);
    w.show();
    return a.exec();
}
