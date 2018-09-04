#include <QDebug>
#include "menurelationhandler.h"

#include <string>
#include <iostream>

using namespace GiNaC;
using namespace MoebInv;

menuRelAction::menuRelAction(MoebInv::ex *cycle, GiNaC::lst *relationList,
    QString actionTitle, int params, bool checked,
    MoebInv::cycle_relation (*relFunction) (const GiNaC::ex &, bool),
    menuRelActionGroup *group)
{
    this->cycle = cycle;
    this->relationList = relationList;
    this->relFunction = relFunction;
    this->params = params;
    this->group = group;

    this->setIconText(actionTitle);
    this->setCheckable(true);
    this->setChecked(checked);

    connect(this, &QAction::triggered, this, &menuRelAction::actionHandler);
}

bool menuRelAction::hasRelation()
{
    if (relFunction == nullptr)
        return false;
    else
        return true;
}

cycle_relation menuRelAction::getRelation()
{
    if (relFunction == nullptr) {
        throw std::invalid_argument("relFunction has no function assigned");
    } else {
        return relFunction(*cycle, true);
    }
}

menuRelActionGroup* menuRelAction::getGroup()
{
    return this->group;
}

void menuRelAction::actionHandler()
{
    switch (params) {
        case 0: // case where there are no additional parameters
            emit handleRelation();
            break;
    }
}

bool menuRelAction::checkActionHandler()
{

}

QString menuRelAction::node_label(ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}

menuRelActionGroup::menuRelActionGroup(QObject *parent) : QActionGroup(parent)
{

}

QList<menuRelAction *> menuRelActionGroup::getRelActions()
{
    return this->actions;
}

void menuRelActionGroup::addRelAction(menuRelAction *action)
{
    // add item to action list of types 'menuRelAction'
    this->actions.append(action);
    // now add to standard QActionGroup like normal
    this->addAction(action);
}
