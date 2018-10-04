#ifndef MENURELATIONHANDLER_H
#define MENURELATIONHANDLER_H

#include <QSettings>
#include <QAction>
#include <QActionGroup>
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>
#include <stdexcept>

#include <figure.h>

#include "conf.h"
#include "matrix4dialog.h"
#include "matrix8dialog.h"

class menuRelActionGroup;

class menuRelAction : public QObject
{
    Q_OBJECT

public:
    menuRelAction(MoebInv::figure *f, MoebInv::ex cycle, GiNaC::lst *relationList,
        QString actionTitle, int params, bool checked,
        int relType, menuRelActionGroup *group = nullptr);
    GiNaC::ex getCycle();
    int getRelType();
    GiNaC::lst getInputList();
    GiNaC::lst getParams();
    menuRelActionGroup* getGroup();
    MoebInv::cycle_relation getRelation();
    void setRelation();
    bool hasRelation();
    QAction menuEntry();
    QAction checkMenuEntry();
    void actionHandler();
    void cycleMetricActionHandler();
    void checkActionHandler();
    QString node_label(GiNaC::ex name);
    void createCycleRelation(const GiNaC::lst &params, const bool &metric);
    QString checkCycleRelation(const GiNaC::ex &thisCycle, const GiNaC::ex &otherCycle);

    QAction *addRelation;
    QAction *addCycleRelation;
    QAction *checkRelation;

signals:
    void handleRelation(const bool &metric);

private:
    QSettings s;

    // input dialogs
    QInputDialog *inputDialog;
    matrix4dialog *matrix4;
    matrix8dialog *matrix8;

    MoebInv::figure *f;
    GiNaC::ex cycle;
    QString actionTitle;
    menuRelActionGroup *group;
    int relType;
    int inputType;
    MoebInv::cycle_relation relation;
    GiNaC::lst mostRecentParams;

    QMessageBox *msgBox;
};



class menuRelActionGroup : public QActionGroup {
    Q_OBJECT

public:
    menuRelActionGroup(QObject *parent = nullptr);
    void addRelAction(menuRelAction *action);
    QList<menuRelAction *> getRelActions();

signals:
    void handleRelation();

private:
    QSettings s;

    QList<menuRelAction *> actions;
};

#endif // MENURELATIONHANDLER_H
