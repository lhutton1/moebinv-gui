#include <QApplication>
#include "mainwindow.h"
#include <QSettings>
#include <QDebug>

#include "conf.h"

void setDefaultSettings()
{
    QSettings s;

    /*!
     * Sets the drawing metric.
     */
    s.setValue("pointMetric", ELLIPTIC);

    /*!
     * Sets the cycle metric.
     */
    s.setValue("cycleMetric", PARABOLIC);

    /*!
     * Sets the figure evaluation type.
     */
    s.setValue("evaluationType", FLOATING);

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
     * NOTE: Increasing this by too large a factor could cause the application to run out of memory.
     */
    s.setValue("sceneSize", 30000);

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

    /*!
     * Set the initial zoom factor of the graphics view.
     */
    s.setValue("initialZoomFactor", 40);

    /*!
     * Set the distance in which a cycle can be hovered.
     */
    s.setValue("highlightDistance", 0.25);

    /*!
     * Show the bounding rect of items on the graphicsScene.
     */
    s.setValue("debugBoundingRect", false);

    /*!
     * Set whether the gui displays only real cycles.
     */
    s.setValue("realCycles", true);

    /*!
     * Set default the name of the figure.
     */
    s.setValue("figureName", "unnamed");

    /*!
     * Set the default figure description.
     */
    s.setValue("figureDescription", "no description");

    /*!
     * Set automatic assignment of labels i.e. A, B, C, ...
     */
    s.setValue("automaticLabels", true);

    /*!
     * Set the default background colour
     */
    s.setValue("backgroundColour", QColor(255, 255, 255));

    /*!
     * The main windows position.
     *
     * A null value will mean that the OS uses its window manager to decide.
     */
    s.setValue("mainWindowPosition", 0);

    /*!
     * The main windows size.
     */
    s.setValue("mainWindowSize", 0);

    /*!
     * The default save directory for .gar files.
     */
    QDir defaultPath = QDir(QStandardPaths::writableLocation(
        static_cast<QStandardPaths::StandardLocation>(QStandardPaths::DocumentsLocation)));
    qDebug() << defaultPath.absolutePath();
    s.setValue("defaultSaveDirectory", defaultPath.absolutePath());

    /*!
     * Set whether the only relas relation is applied automatically to 'this'.
     */
    s.setValue("automaticOnlyReals", true);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initiate settings object
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QCoreApplication::setOrganizationName("moebinv-gui");
    QCoreApplication::setOrganizationDomain("moebinv-gui.com");
    QCoreApplication::setApplicationName("moebinv-gui");

    setDefaultSettings();

    MainWindow w;

    w.show();

    return a.exec();
}
