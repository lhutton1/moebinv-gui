#include <QApplication>
#include "mainwindow.h"
#include <QSettings>

void setDefaultSettings()
{
    QSettings s;

    s.setValue("showLabels", true);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initiate settings
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QCoreApplication::setOrganizationName("My Organization");
    QCoreApplication::setOrganizationDomain("myorganization.com");
    QCoreApplication::setApplicationName("My Application");

    setDefaultSettings();

    MainWindow w;

    w.show();

    return a.exec();
}
