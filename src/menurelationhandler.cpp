#include <QDebug>
#include "menurelationhandler.h"

#include <string>
#include <iostream>

using namespace GiNaC;
using namespace MoebInv;

menuRelAction::menuRelAction(MoebInv::ex cycle, GiNaC::lst *relationList,
    QString actionTitle, int params, bool checked,
    int relType, menuRelActionGroup *group)
{
    this->cycle = cycle;
    this->relationList = relationList;
    this->relType = relType;
    this->inputType = params;
    this->group = group;

    this->relation = cycle_relation();

    this->setIconText(actionTitle);
    this->setCheckable(true);
    this->setChecked(checked);

    connect(this, &QAction::triggered, this, &menuRelAction::actionHandler);

    this->inputDialog = new QInputDialog();
    this->matrix4 = new matrix4dialog();
    this->matrix8 = new matrix8dialog();
}


/*!
 * \brief menuRelAction::hasRelation Check whether the action has a
 * relation that has been assigned to it.
 *
 * \return bool
 */
bool menuRelAction::hasRelation()
{
    if (node_label(this->relation) == "0|o")
        return false;
    else
        return true;
}


/*!
 * \brief menuRelAction::getRelation Get the relation that has been assigned
 * to the action.
 *
 * \return cycle_relation
 */
cycle_relation menuRelAction::getRelation()
{
    if (node_label(this->relation) == "0|o") {
        throw std::invalid_argument("A relation has not been constructed. Maybe arguments were missing?");
    } else {
        return relation;
    }
}


/*!
 * \brief menuRelAction::getGroup Get the group the relation has been assigned to.
 * \return  menuRelActionGroup*
 */
menuRelActionGroup* menuRelAction::getGroup()
{
    return this->group;
}


/*!
 * \brief menuRelAction::actionHandler
 */
void menuRelAction::actionHandler()
{
    lst params;

    params = getInputList();

    if (this->inputType == SINGLE_PARAM && params.nops() != 1 ||
            this->inputType == MATRIX_4 && params.nops() != 4 ||
            this->inputType == MATRIX_8 && params.nops() != 8
    ) {
        return;
    }

    createCycleRelation(params);
    emit handleRelation();
}

void menuRelAction::createCycleRelation(const lst &params)
{
    switch (relType) {
        case ORTHOGONAL:
            this->relation = is_orthogonal(cycle, true);
            break;
        case FORTHOGONAL:
            this->relation = is_f_orthogonal(cycle, true);
            break;
        case DIFFERENT:
            this->relation = is_different(cycle, true);
            break;
        case ADIFFERENT:
            this->relation = is_adifferent(cycle, true);
            break;
        case REALS:
            this->relation = only_reals(cycle, true);
            break;
        case TANGENT:
            this->relation = is_tangent(cycle, true);
            break;
        case TANGENT_I:
            this->relation = is_tangent_i(cycle, true);
            break;
        case TANGENT_O:
            this->relation = is_tangent_o(cycle, true);
            break;
        case STEINER_POWER:
            this->relation = cycle_power(cycle, true, params.op(0));
            break;
        case CYCLE_ANGLE:
            this->relation = make_angle(cycle, true, params.op(0));
            break;
        case CYCLE_CROSS_T_DISTANCE:
            this->relation = cross_t_distance(cycle, true, params.op(0));
            break;
        case PRODUCT_SIGN:
            this->relation = product_nonpositive(cycle, true, params.op(0));
            break;
        case CYCLE_MOBIUS:
            this->relation = moebius_transform(cycle, true, params);
            break;
        case CYCLE_SL2:
            this->relation = sl2_transform(cycle, true, params);
            break;
    }
}

lst menuRelAction::getInputList()
{
    bool isInput = false;
    lst input = lst();
    QString inputDialogTitle = this->actionTitle;

    // get the inputs needed for the relation
    if (this->inputType == NO_PARAMS) {
        isInput = true;

    } else if (this->inputType == SINGLE_PARAM) {
        double inputDialogValue = QInputDialog::getDouble(nullptr, inputDialogTitle,
                                        "Value:", 0, -10000, 10000, 2, &isInput);

        input = lst(inputDialogValue);

    } else if (this->inputType == MATRIX_4) {
        if (matrix4->exec() == QDialog::Accepted ) {
            isInput = true;
            matrix4->getValues(&input);
        }

    } else if (this->inputType == MATRIX_8) {
        if (matrix8->exec() == QDialog::Accepted ) {
            isInput = true;
            matrix8->getValues(&input);
        }
    }

    // check if the input was successful, if not set the relation to unchecked.
    if (!isInput)
        this->setChecked(false);

    return input;
}

QString menuRelAction::node_label(ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}



//////////////////
// Action Group //
//////////////////

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
