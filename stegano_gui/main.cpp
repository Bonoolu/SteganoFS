#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include "example.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Example::example();

    //open qss file
    QFile file(":/assets/stylesheet/assets/stylesheet/Darkeum.qss");
    file.open(QFile::ReadOnly);

    QString styleSheet { QLatin1String(file.readAll()) };

    //setup stylesheet
    a.setStyleSheet(styleSheet);

    w.show();
    return a.exec();
}
