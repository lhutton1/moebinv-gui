#include <QApplication>
#include "mainwindow.h"
#include <QSettings>
#include <QDebug>

#include "conf.h"

void setDefaultSettings()
{
    QSettings s;

    s.setValue("pointMetric", ELLIPTIC); // Sets the drawing metric.
    s.setValue("cycleMetric", ELLIPTIC); // Sets the cycle metric.
    s.setValue("evaluationType", FLOATING); // Sets the figure evaluation type.
    s.setValue("showLabels", true); // Labels visibility. True - show, False - hide.
    s.setValue("dockInitialSizeRatio", 0.3); // Dock's size in relation to the size of the window.
    s.setValue("pointSize", 3); // Sets the size of a point.
    s.setValue("sceneSize", 30000); // Sets the size of the scene before it expands. NOTE: Increasing this by too large a factor could cause the application to run out of memory.
    s.setValue("floatingPointAccuracy", 3); // Adjust the accuracy which coordinates are displayed to.
    s.setValue("zoomFactorAmount", 0.1); // Set the zoom factor. Between (0 and 1).
    s.setValue("mouseStopWait", 200); // Set the amount of time to wait after the mouse stops to highlight the nearest cycle.
    s.setValue("initialZoomFactor", 40); // Set the initial zoom factor of the graphics view.
    s.setValue("highlightDistance", 0.25); // Set the distance in which a cycle can be hovered.
    s.setValue("debugBoundingRect", false); // Show the bounding rect of items on the graphicsScene.
    s.setValue("figureName", "unnamed"); // Set default the name of the figure.
    s.setValue("figureDescription", "no description"); // Set the default figure description.
    s.setValue("floatEvaluation", true); // Sets whether the application should use float evaluation or not.

    if (!s.contains("defaultsInitialised")) {
        s.setValue("defaultLineWidth", 2); // Sets the thickness of lines drawn in the scene.
        s.setValue("graphicsHoverColour", QColor(255, 0, 0)); // Set the hover colour of the graphics on the scene.
        s.setValue("defaultGraphicsColour", QColor(0, 0, 0)); // Set the default colour of the graphics in the scene.
        s.setValue("backgroundColour", QColor(255, 255, 255)); // Set the default background colour.
        QDir defaultPath = QDir(QStandardPaths::writableLocation(
            static_cast<QStandardPaths::StandardLocation>(QStandardPaths::DocumentsLocation)));
        s.setValue("defaultSaveDirectory", defaultPath.absolutePath()); // The default save directory for .gar files.
        s.setValue("automaticLabels", true); // Set automatic assignment of labels i.e. A, B, C, ...
        s.setValue("automaticOnlyReals", true); // Set whether the only reals relation is applied automatically to 'this'.
        s.setValue("undoLimit", 10); // Set the undo stack size limit.
        s.setValue("defaultLineStyle", SOLID); // Set the default line style.
    }

    s.setValue("session/defaultLineWidth", s.value("defaultLineWidth")); // Sets the thickness of lines drawn in the scene.
    s.setValue("session/graphicsHoverColour", s.value("graphicsHoverColour")); // Set the hover colour of the graphics on the scene.
    s.setValue("session/defaultGraphicsColour", s.value("defaultGraphicsColour")); // Set the default colour of the graphics in the scene.
    s.setValue("session/backgroundColour", s.value("backgroundColour")); // Set the default background colour.
    s.setValue("session/defaultSaveDirectory", s.value("defaultSaveDirectory")); // The default save directory for .gar files.
    s.setValue("session/automaticLabels", s.value("automaticLabels")); // Set automatic assignment of labels i.e. A, B, C, ...
    s.setValue("session/automaticOnlyReals", s.value("automaticOnlyReals")); // Set whether the only reals relation is applied automatically to 'this'.
    s.setValue("session/undoLimit", s.value("undoLimit")); // Set the undo stack size limit.
    s.setValue("session/defaultLineStyle", s.value("defaultLineStyle")); // Set the default line style.
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
