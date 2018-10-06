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

    this->addCycleRelation = new QAction(actionTitle, this);
    this->addCycleRelation->setCheckable(true);
    this->addCycleRelation->setChecked(checked);
    connect(this->addCycleRelation, &QAction::triggered, this, &menuRelAction::cycleMetricActionHandler);

    this->checkRelation = new QAction(actionTitle, this);
    this->checkRelation->setCheckable(false);
    connect(this->checkRelation, &QAction::triggered, this, &menuRelAction::checkActionHandler);

    this->checkCycleMetricRelation = new QAction(actionTitle, this);
    this->checkCycleMetricRelation->setCheckable(false);
    connect(this->checkCycleMetricRelation, &QAction::triggered, this, &menuRelAction::checkActionCycleHandler);
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
 * \brief menuRelAction::getCycle Get the cycle assigned to this relation.
 * \return GiNaC::ex
 */
ex menuRelAction::getCycle()
{
    return this->cycle;
}


/*!
 * \brief menuRelAction::getRelType Get the relation type assigned to the relation.
 * \return int
 */
int menuRelAction::getRelType()
{
    return this->relType;
}


/*!
 * \brief menuRelAction::getParams Get the parameters that have been provided to the relation.
 * \return GiNaC::lst
 */
lst menuRelAction::getParams()
{
    return this->mostRecentParams;
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
    const lst params = getInputList();

    // check the correct number of parameters have been provided
    if ((this->inputType == SINGLE_PARAM && params.nops() != 1) ||
            (this->inputType == MATRIX_4 && params.nops() != 4) ||
            (this->inputType == MATRIX_8 && params.nops() != 4)
    ) {
        emit handleRelation(true);
        return;
    }

    // build the required relation.
    createCycleRelation(params, true);
    emit handleRelation(true);
}


/*!
 * \brief menuRelAction::cycleMetricActionHandler Action handler for the cycle metric relation.
 *
 * Checks to make sure the correct number of parameters have been provided.
 * If so the relevent relation is built.
 */
void menuRelAction::cycleMetricActionHandler()
{
    const lst params = getInputList();

    // check the correct number of parameters have been provided
    if ((this->inputType == SINGLE_PARAM && params.nops() != 1) ||
            (this->inputType == MATRIX_4 && params.nops() != 4) ||
            (this->inputType == MATRIX_8 && params.nops() != 4)
    ) {
        emit handleRelation(false);
        return;
    }

    // build the required relation.
    createCycleRelation(params, false);
    emit handleRelation(false);
}


/*!
 * \brief menuRelAction::checkActionHandler Action handler to check the status of a
 * relation on 2 cycles. First the user is prompted to enter another cycle key, then
 * this function checks the status of this relation and outputs the result back to the user.
 */
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
    QString relationCheck = checkCycleRelation(this->cycle, checkCycle, false);

    QMessageBox msgBoxInfo;
    msgBoxInfo.setInformativeText("Relation check returned: " + relationCheck);
    msgBoxInfo.setStyleSheet("QLabel{min-width: 400px;}");
    msgBoxInfo.exec();
}


/*!
 * \brief menuRelAction::checkActionCycleHandler Action handler to check the status of a
 * relation on 2 cycles. First the user is prompted to enter another cycle key, then
 * this function checks the status of this relation and outputs the result back to the user.
 */
void menuRelAction::checkActionCycleHandler()
{
    QString inputDialogValue = QInputDialog::getText(nullptr, "Input cycle label", "Cycle key:");
    ex checkCycle = f->get_cycle_key(qPrintable(inputDialogValue));

    // check that key exists
    if (node_label(checkCycle) == "0") {
        this->msgBox->warning(0, "Key error", "The key entered does not exist.");
        return;
    }

    // find the relvent relation
    QString relationCheck = checkCycleRelation(this->cycle, checkCycle, true);

    QMessageBox msgBoxInfo;
    msgBoxInfo.setInformativeText("Relation check returned: " + relationCheck);
    msgBoxInfo.setStyleSheet("QLabel{min-width: 400px;}");
    msgBoxInfo.exec();
}


/*!
 * \brief menuRelAction::createCycleRelation creates the relevent relation based on the inputs.
 * \param params GiNaC::lst of the parameter entered by the user.
 * \param metric true = point metric relation, false = cycle metric relation
 */
void menuRelAction::createCycleRelation(const lst &params, const bool &metric)
{
    this->mostRecentParams = params;

    switch (relType) {
        case ORTHOGONAL:
            this->relation = is_orthogonal(cycle, metric);
            break;
        case FORTHOGONAL:
            this->relation = is_f_orthogonal(cycle, metric);
            break;
        case DIFFERENT:
            this->relation = is_different(cycle, metric);
            break;
        case ADIFFERENT:
            this->relation = is_adifferent(cycle, metric);
            break;
        case REALS:
            this->relation = only_reals(cycle, metric);
            break;
        case TANGENT:
            this->relation = is_tangent(cycle, metric);
            break;
        case TANGENT_I:
            this->relation = is_tangent_i(cycle, metric);
            break;
        case TANGENT_O:
            this->relation = is_tangent_o(cycle, metric);
            break;
        case STEINER_POWER:
            this->relation = cycle_power(cycle, metric, params.op(0));
            break;
        case CYCLE_ANGLE:
            this->relation = make_angle(cycle, metric, params.op(0));
            break;
        case CYCLE_CROSS_T_DISTANCE:
            this->relation = cross_t_distance(cycle, metric, params.op(0));
            break;
        case PRODUCT_SIGN:
            this->relation = product_nonpositive(cycle, metric, params.op(0));
            break;
        case CYCLE_MOBIUS:
            this->relation = moebius_transform(cycle, metric, params);
            break;
        case CYCLE_SL2:
            this->relation = sl2_transform(cycle, metric, params);
            break;
    }
}


/*!
 * \brief menuRelAction::checkCycleRelation used to check a relation.
 * \param thisCycle the cycle this relation belongs to.
 * \param otherCycle the other cycle entered by the user.
 * \return QString
 */
QString menuRelAction::checkCycleRelation(const ex &thisCycle, const ex &otherCycle, const bool &metric)
{
    QString output;

    switch (relType) {
        case ORTHOGONAL:
            output = node_label(f->check_rel(thisCycle, otherCycle, cycle_orthogonal, metric).evalf());
            break;
        case FORTHOGONAL:
            output = node_label(f->check_rel(thisCycle, otherCycle, cycle_f_orthogonal, metric).evalf());
            break;
        case DIFFERENT:
            output = node_label(f->check_rel(thisCycle, otherCycle, cycle_different, metric).evalf());
            break;
        case ADIFFERENT:
            output = node_label(f->check_rel(thisCycle, otherCycle, cycle_adifferent, metric).evalf());
            break;
        case REALS:
            output = node_label(f->check_rel(thisCycle, otherCycle, coefficients_are_real, metric).evalf());
            break;
        case TANGENT:
            output = node_label(f->check_rel(thisCycle, otherCycle, check_tangent, metric).evalf());
            break;
        case PRODUCT_SIGN:
            output = node_label(f->check_rel(thisCycle, otherCycle, product_sign, metric).evalf());
            break;
        case STEINER_POWER:
            output = node_label(f->measure(thisCycle, otherCycle, power_is, metric).evalf());
            break;
        case CYCLE_ANGLE:
            output = node_label(f->measure(thisCycle, otherCycle, angle_is, metric).evalf());
            break;
        case CYCLE_CROSS_T_DISTANCE:
            output = node_label(f->measure(thisCycle, otherCycle, sq_cross_t_distance_is, metric).evalf());
            break;
        default:
            output = "The relation could not be found. Make sure the relation has been added to the menuRelAction::checkCycleRelation() function";
            break;
    }

    return output;
}


/*!
 * \brief menuRelAction::getInputList gets a list of inputs based on the
 * number of parameters required.
 * \return GiNaC::lst
 */
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

/*!
 * \brief menuRelActionGroup::menuRelActionGroup
 * \param parent
 *
 * Create a new relation group. Subclassed from QActionGroup
 */
menuRelActionGroup::menuRelActionGroup(QObject *parent) : QActionGroup(parent)
{

}

/*!
 * \brief menuRelActionGroup::getRelActions Get the actions that have been added to
 * the group and return as a list of menuRelAction objects.
 * \return QList<menuRelAction *>
 */
QList<menuRelAction *> menuRelActionGroup::getRelActions()
{
    return this->actions;
}


/*!
 * \brief menuRelActionGroup::addRelAction Add a new action to the group.
 * \param action action to add to the group.
 */
void menuRelActionGroup::addRelAction(menuRelAction *action)
{
    // add item to action list of types 'menuRelAction'
    this->actions.append(action);
    // now add to standard QActionGroup like normal
    this->addAction(action->addRelation);
    this->addAction(action->addCycleRelation);
}
