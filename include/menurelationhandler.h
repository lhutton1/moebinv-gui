#ifndef MENURELATIONHANDLER_H
#define MENURELATIONHANDLER_H

#include <QSettings>
#include <QAction>

#include "figure.h"

#include "conf.h"

class menuRelationHandler : public QAction
{
    Q_OBJECT

public:
    menuRelationHandler(MoebInv::ex cycle, GiNaC::lst *relationList, MoebInv::cycle_relation (*relFunction) (const GiNaC::ex &, bool), QString actionTitle, int params, bool checked);
    QAction menuEntry();
    QAction checkMenuEntry();
    void actionHandler();
    bool checkActionHandler();
    void getRelationFunction();

private:
    QSettings s;

    MoebInv::ex cycle;
    GiNaC::lst *relationList;
    MoebInv::cycle_relation (*relFunction) (const GiNaC::ex &, bool);
    QString actionTitle;
    int params;

};

#endif // MENURELATIONHANDLER_H
