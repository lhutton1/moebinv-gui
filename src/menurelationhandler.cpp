#include <QDebug>
#include "menurelationhandler.h"

#include <string>
#include <iostream>

using namespace GiNaC;
using namespace MoebInv;


/*!
 * \brief menuRelAction::menuRelAction
 * \param cycle cycle the action is related to.
 * \param relationList pointer to the relation list that stores curretly active relations
 * \param actionTitle title of the action.
 * \param params number of params the relation needs to take.
 * \param checked whether or not the relation is checked when created.
 * \param relType the type of relation the action represents.
 * \param group the group the relation is included within.
 *
 * Create a new relation QAction to be added to the context menu.
 */
menuRelAction::menuRelAction(MoebInv::figure *f, MoebInv::ex cycle, GiNaC::lst *relationList,
    QString actionTitle, int params, bool checked,
    int relType, menuRelActionGroup *group)
{
    this->f = f;
    this->cycle = cycle;
    this->relType = relType;
    this->inputType = params;
    this->group = group;
    this->relation = cycle_relation();

    this->inputDialog = new QInputDialog();
    this->matrix4 = new matrix4dialog();
    this->matrix8 = new matrix8dialog();

    // create actions
    this->addRelation = new QAction(actionTitle, this);
    this->addRelation->setCheckable(true);
    this->addRelation->setChecked(checked);
    connect(this->addRelation, &QAction::triggered, this, &menuRelAction::actionHandler);

    this->checkRelation = new QAction(actionTitle, this);
    this->checkRelation->setCheckable(false);
    connect(this->checkRelation, &QAction::triggered, this, &menuRelAction::checkActionHandler);
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


ex menuRelAction::getCycle()
{
    return this->cycle;
}

int menuRelAction::getRelType()
{
    return this->relType;
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
 * \brief menuRelAction::actionHandler Handles the action.
 *
 * Checks to make sure the correct number of parameters have been provided.
 * If so the relevent relation is built.
 */
void menuRelAction::actionHandler()
{
    qDebug() << sender()->objectName();
    const lst params = getInputList();

    // check the correct number of parameters have been provided
    if ((this->inputType == SINGLE_PARAM && params.nops() != 1) ||
            (this->inputType == MATRIX_4 && params.nops() != 4) ||
            (this->inputType == MATRIX_8 && params.nops() != 4)
    ) {
        emit handleRelation();
        return;
    }

    // build the required relation.
    createCycleRelation(params);
    emit handleRelation();
}

void menuRelAction::checkActionHandler()
{
    QString inputDialogValue = QInputDialog::getText(nullptr, "Input cycle label", "Cycle key:");
    ex checkCycle = f->get_cycle_key(qPrintable(inputDialogValue));

    // check that key exists
    if (node_label(checkCycle) == "0") {
        this->msgBox->warning(0, "Key error", "The key entered does not exist.");
        return;
    }

    // find the relvent relation
    QString relationCheck = checkCycleRelation(this->cycle, checkCycle);

    QMessageBox msgBoxInfo;
    msgBoxInfo.setInformativeText("Relation check returned: " + relationCheck);
    msgBoxInfo.setStyleSheet("QLabel{min-width: 400px;}");
    msgBoxInfo.exec();
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

QString menuRelAction::checkCycleRelation(const ex &thisCycle, const ex &otherCycle)
{
    QString output;

    switch (relType) {
        case ORTHOGONAL:
            output = node_label(f->check_rel(thisCycle, otherCycle, cycle_orthogonal).evalf());
            break;
        case FORTHOGONAL:
            output = node_label(f->check_rel(thisCycle, otherCycle, cycle_f_orthogonal).evalf());
            break;
        case DIFFERENT:
            output = node_label(f->check_rel(thisCycle, otherCycle, cycle_different).evalf());
            break;
        case ADIFFERENT:
            output = node_label(f->check_rel(thisCycle, otherCycle, cycle_adifferent).evalf());
            break;
        case REALS:
            output = node_label(f->check_rel(thisCycle, otherCycle, coefficients_are_real).evalf());
            break;
        case TANGENT:
            output = node_label(f->check_rel(thisCycle, otherCycle, check_tangent).evalf());
            break;
        case PRODUCT_SIGN:
            output = node_label(f->check_rel(thisCycle, otherCycle, product_sign).evalf());
            break;
        case STEINER_POWER:
            output = node_label(f->measure(thisCycle, otherCycle, power_is).evalf());
            break;
        case CYCLE_ANGLE:
            output = node_label(f->measure(thisCycle, otherCycle, angle_is).evalf());
            break;
        case CYCLE_CROSS_T_DISTANCE:
            output = node_label(f->measure(thisCycle, otherCycle, sq_cross_t_distance_is).evalf());
            break;
        default:
            output = "The relation could not be found. Make sure the relation has been added to the menuRelAction::checkCycleRelation() function";
            break;
    }

    return output;
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

            ex unit = f->get_point_metric(),
               unit0 = unit.subs(unit.op(1)==0),
               unit1 = unit.subs(unit.op(1)==1);

            if (ex_to<idx>(unit.op(1)).get_dim() == 2) {
                input = lst{dirac_ONE()*input.op(0)+unit1*unit0*input.op(1), unit0*input.op(2)+unit1*input.op(3),
                        -unit0*input.op(4)+unit1*input.op(5), dirac_ONE()*input.op(6)+unit1*unit0*input.op(7)};
            } else {
                input = lst{unit0*input.op(0)+unit1*input.op(1), unit0*input.op(2)+unit1*input.op(3),
                        unit0*input.op(4)+unit1*input.op(5), unit0*input.op(6)+unit1*input.op(7)};
            }
        }
    } else if (this->inputType == PRODUCT_COMBOBOX) {
        QStringList items;
        items << "Product is non positive" << "Product is positive";
        QString item = QInputDialog::getItem(nullptr, inputDialogTitle, "Value:", items, 0, false, &isInput);

        if (item == "Product is non positive")
            input = lst(true);
        else if (item == "Product is positive")
            input = lst(false);
    }

    // check if the input was successful, if not set the relation to unchecked.
    if (!isInput)
        this->addRelation->setChecked(false);

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
    this->addAction(action->addRelation);
}
