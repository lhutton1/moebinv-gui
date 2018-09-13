#ifndef MENURELATIONHANDLER_H
#define MENURELATIONHANDLER_H

#include <QSettings>
#include <QAction>
#include <QActionGroup>
#include <QInputDialog>
#include <stdexcept>

#include <figure.h>

#include "conf.h"
#include "matrix4dialog.h"
#include "matrix8dialog.h"

class menuRelActionGroup;

class menuRelAction : public QAction
{
    Q_OBJECT

public:
    menuRelAction(MoebInv::figure *f, MoebInv::ex cycle, GiNaC::lst *relationList,
        QString actionTitle, int params, bool checked,
        int relType, menuRelActionGroup *group = nullptr);
    GiNaC::ex getCycle();
    GiNaC::lst getInputList();
    menuRelActionGroup* getGroup();
    MoebInv::cycle_relation getRelation();
    void setRelation();
    bool hasRelation();
    QAction menuEntry();
    QAction checkMenuEntry();
    void actionHandler();
    bool checkActionHandler();
    QString node_label(GiNaC::ex name);
    void createCycleRelation(const GiNaC::lst &params);

signals:
    void handleRelation();

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
