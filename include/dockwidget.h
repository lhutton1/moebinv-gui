#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QObject>
#include <QDockWidget>
#include <QSettings>

class dockWidget : public QDockWidget
{
    Q_OBJECT


public:
    dockWidget(QObject *parent = 0);
    void resizeEvent(QResizeEvent *event);
    void setSizeRatio(double sizeRatio);
    double getSizeRatio();

signals:
    void recenterView();
    void calculateDockToWindowPercentage();

private:
    QSettings s;

    double sizeRatio;
};

#endif // DOCKWIDGET_H
