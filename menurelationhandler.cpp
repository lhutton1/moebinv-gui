#include <QDebug>
#include "menurelationhandler.h"

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
            relationList->append(relFunction(cycle, true));
            break;
    }
}

bool menuRelationHandler::checkActionHandler()
{

}

void menuRelationHandler::getRelationFunction()
{

}
