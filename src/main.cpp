#include <QApplication>
#include "mainwindow.h"
#include <QSettings>

#include "conf.h"

void setDefaultSettings()
{
    QSettings s;

    /*!
     * Sets the drawing metric.
     */
    s.setValue("drawingMetric", ELLIPTIC);

    /*!
     * Labels visibility. True - show, False - hide.
     */
    s.setValue("showLabels", true);

    /*!
     * Dock's size in relation to the size of the window.
     */
    s.setValue("dockInitialSizeRatio", 0.3);

    /*!
     * Sets the size of a point.
     */
    s.setValue("pointSize", 3);

    /*!
     * Sets the thickness of lines drawn in the scene.
     */
    s.setValue("defaultLineWidth", 2);

    /*!
     * Sets the size of the scene before it expands.
     */
    s.setValue("sceneSize", 300000);

    /*!
     * Adjust the accuracy which coordinates are displayed to.
     */
    s.setValue("floatingPointAccuracy", 3);

    /*!
     * Sets whether the application should use float evaluation or not.
     */
    s.setValue("floatEvaluation", true);

    /*!
     * Set the hover colour of the graphics on the scene.
     */
    s.setValue("graphicsHoverColour", QColor(255, 0, 0));

    /*!
     * Set the default colour of the graphics in the scene.
     */
    s.setValue("defaultGraphicsColour", QColor(0, 0, 0));

    /*!
     * Set the default line style.
     */
    s.setValue("defaultLineStyle", SOLID);

    /*!
     * Set the zoom factor. Between (0 and 1).
     */
    s.setValue("zoomFactorAmount", 0.1);

    /*!
     * Set the amount of time to wait after the mouse stops to highlight the nearest cycle.
     */
    s.setValue("mouseStopWait", 200);

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initiate settings object
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QCoreApplication::setOrganizationName("My Organization");
    QCoreApplication::setOrganizationDomain("myorganization.com");
    QCoreApplication::setApplicationName("My Application");

    setDefaultSettings();

    MainWindow w;

    w.show();

    return a.exec();
}
