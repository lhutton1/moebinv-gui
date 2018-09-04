#ifndef MENURELATIONHANDLER_H
#define MENURELATIONHANDLER_H

#include <QSettings>
#include <QAction>
#include <QActionGroup>
#include <stdexcept>

#include "figure.h"

#include "conf.h"

class menuRelActionGroup;

class menuRelAction : public QAction
{
    Q_OBJECT

public:
    menuRelAction(MoebInv::ex *cycle, GiNaC::lst *relationList,
        QString actionTitle, int params, bool checked,
        MoebInv::cycle_relation (*relFunction) (const GiNaC::ex &, bool),
        menuRelActionGroup *group = nullptr);

    QAction menuEntry();
    QAction checkMenuEntry();
    bool hasRelation();
    MoebInv::cycle_relation getRelation();
    void actionHandler();
    bool checkActionHandler();
    GiNaC::ex getCycle();
    QString node_label(GiNaC::ex name);
    menuRelActionGroup* getGroup();

signals:
    void handleRelation();

private:
    QSettings s;

    GiNaC::ex *cycle;
    GiNaC::lst *relationList;
    MoebInv::cycle_relation (*relFunction) (const GiNaC::ex &, bool);
    QString actionTitle;
    menuRelActionGroup *group;
    int params;

};

class menuRelActionGroup : public QActionGroup {
    Q_OBJECT

public:
    menuRelActionGroup(QObject *parent = nullptr);
    void addRelAction(menuRelAction *action);
    QList<menuRelAction *> getRelActions();

private:
    QSettings s;

    QList<menuRelAction *> actions;
};

#endif // MENURELATIONHANDLER_H
