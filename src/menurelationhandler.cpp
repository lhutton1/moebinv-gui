#include <QDebug>
#include "menurelationhandler.h"

#include <string>
#include <iostream>

using namespace GiNaC;
using namespace MoebInv;

menuRelationHandler::menuRelationHandler(MoebInv::ex cycle, GiNaC::lst *relationList, MoebInv::cycle_relation (*relFunction) (const GiNaC::ex &, bool), QString actionTitle, int params, bool checked)
{
    this->cycle = cycle;
    this->relationList = relationList;
    this->relFunction = relFunction;
    this->params = params;

    this->setIconText(actionTitle);
    this->setCheckable(checked);

    connect(this, &QAction::triggered, this, &menuRelationHandler::actionHandler);
}

void menuRelationHandler::actionHandler()
{
    switch (params) {
        case 0: // case where there are no additional parameters
            this->isChecked() ? addRelationToList() : removeRelationFromList();
            break;
    }
}

bool menuRelationHandler::checkActionHandler()
{

}

void menuRelationHandler::addRelationToList()
{
    this->relationList->append(relFunction(cycle, true));
}

void menuRelationHandler::removeRelationFromList()
{
    lst newRelationList;

    for (int x = 0; x < relationList->nops(); x++) {
        if (node_label(relationList->op(x)) != node_label(relFunction(cycle, true))) {
            newRelationList.append(relationList->op(x));
        }
    }

    *relationList = newRelationList;
}

QString menuRelationHandler::node_label(ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}
