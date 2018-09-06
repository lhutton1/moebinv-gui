#include "cyclecontextmenu.h"
#include <QDebug>

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief cycleContextMenu::cycleContextMenu Context menu constructor
 * \param f - pointer to the figure.
 * \param cycle - cycle the context menu is related to.
 * \param relationList - pointer to the list that stores the current selected relations from every cycle in the figure.
 * \param isDelete - does the cycle have the delete option or not? (some cycles cannot be deleted e.g. infy)
 *
 * Creates a cycle context menu. This allows for the selection and input of relations and
 * allows the properties of a relation to be changed.
 *
 * Current context menu:
 * -----------
 * title
 * -----------
 * standard
 * relations
 * -----------
 * exclusive
 * tangent
 * -----------
 * relations
 * with inputs
 * -----------
 * colour
 * -----------
 * delete
 * -----------
 */
cycleContextMenu::cycleContextMenu(figure *f, ex cycle, lst *relationList, bool isDelete)
{
    this->f = f;
    this->cycle = cycle;
    this->relationList = relationList;
    this->isDelete = isDelete;

    this->colourDialog = new QColorDialog();

    // build the context menu
    this->buildActions();
    this->buildContextMenu();
}


/*!
 * \brief cycleContextMenu::getCycle get cycle related to the context menu.
 * \return GiNaC::ex.
 */
ex cycleContextMenu::getCycle() {
    return this->cycle;
}


/*!
 * \brief cycleContextMenu::getActions get actions in the context menu.
 * \return QList<menuRelAction *> list of menuRelAction pointers.
 */
QList<menuRelAction *> cycleContextMenu::getActions() {
    return this->actions;
}


/*!
 * \brief cycleContextMenu::getTitleAction get the action that will be used as
 * the title of the context menu. This has been created due to the fact that cross
 * compatability for 'addSection()' isn't well established.
 *
 * \return QAction* - A pointer to the QAction.
 */
QAction* cycleContextMenu::getTitleAction()
{
    QAction *title = new QAction(node_label(cycle));
    title->setEnabled(false);
    return title;
}


/*!
 * \brief cycleContextMenu::setCycle set the cycle that the context menu represents.
 * \param cycle - the cycle in which the context menu will be 'linked' to.
 */
void cycleContextMenu::setCycle(ex cycle) {
    this->cycle = cycle;
}


/*!
 * \brief cycleContextMenu::confirmDeleteCycle slot that asks the user whether they would
 * like to delete the cycle. If they select yes the cycle is deleted from the figure
 * and the scene is updated.
 */
void cycleContextMenu::confirmDeleteCycle()
{
    QString confirmMsg = QString("Are you sure you would like to delete cycle '%1'")
            .arg(node_label(cycle));

    confirmationMessageBox = QMessageBox::question(nullptr, "Delete cycle", confirmMsg,
            QMessageBox::Yes|QMessageBox::No);

    if (confirmationMessageBox == QMessageBox::Yes) {
        f->remove_cycle_node(cycle);
        emit sceneInvalid();
    }
}


/*!
 * \brief cycleContextMenu::amendRelationList This slot corrects the relation list
 * after a new relation has been selected. First the sender object is identified. If the
 * sender action is in a group then the whole of the group is searched removing any
 * relations that are not checked (since anyone of them could have been checked before).
 * Then the relation is added to the relation list if it has been checked and removed if
 * it hasn't. The relationsHaveChanged signal is emmitted to update the status bar text
 * at the bottom of the application.
 */
void cycleContextMenu::amendRelationList()
{
    menuRelAction *actionTriggered = qobject_cast<menuRelAction *>(sender());

    // remove all relations in the triggered cycles group, if it is in one and it is exclusive.
    if (actionTriggered->getGroup() != nullptr && actionTriggered->getGroup()->isExclusive()) {
        for (auto action : actionTriggered->getGroup()->getRelActions()) {
            if (!action->isChecked() && action->hasRelation()) {
                this->removeRelationFromList(action->getRelation());
            }
        }
    }

    // check whether the cycle triggered needs adding or removing.
    if (actionTriggered->hasRelation()) {
        if (actionTriggered->isChecked()) {
            relationList->append(actionTriggered->getRelation());
        } else {
            this->removeRelationFromList(actionTriggered->getRelation());
        }
    }

    // emit signal to update status bar.
    emit relationsHaveChanged();
}


/*!
 * \brief cycleContextMenu::removeRelationFromList This function removes a relation
 * from the list by creating a new list and adding every item except the item that
 * needs to be removed. The 'relationList' from MainWindow is then updated so that
 * 'relation' is no longer in the list.
 *
 * \param relation - the cycle_relation that is to be removed.
 */
void cycleContextMenu::removeRelationFromList(cycle_relation relation)
{
    GiNaC::lst newRelationList;

    // linear search through list to find item to remove
    for (int x = 0; x < relationList->nops(); x++) {
        if (node_label(relationList->op(x)) != node_label(relation)) {
            newRelationList.append(relationList->op(x));
        }
    }

    // update list with new list
    *relationList = newRelationList;
}


/*!
 * \brief cycleContextMenu::buildContextMenu Build the layout of the contextmenu.
 *
 * Note: If a new relation or action is added this layout function will need to
 * be adapted to suit the new layout.
 */
void cycleContextMenu::buildContextMenu()
{
    this->addAction(getTitleAction());
    this->addSeparator();

    // first 5 relations are non-exclusive and don't require additional parameters.
    for (int x = 0; x < 5; x++)
        this->addAction(actions[x]);

    this->addSeparator();

    // the next 4 actions are exclusive, so they are added to a group.
    for (int x = 5; x < 9; x++) {
        this->addAction(actions[x]);
        groups[0]->addRelAction(actions[x]);
    }

    this->addSeparator();

    // the following relations need additional values.
    for (int x = 9; x < actions.length(); x++)
        this->addAction(actions[x]);

    this->addSeparator();

    // change colour preference
    this->addAction(changeColour);

    // add delete action if needed
    if (this->isDelete) {
        this->addSeparator();
        this->addAction(deletePoint);
    }
}


/*!
 * \brief cycleContextMenu::buildActions initialize all the actions that will be
 * displayed in the context menu and connect their trigger signals to slots.
 */
void cycleContextMenu::buildActions()
{
    // tangent action group
    groups.append(new menuRelActionGroup(this));

    actions.append(new menuRelAction(this->cycle, relationList, "Orthogonal", NO_PARAMS, false, ORTHOGONAL));
    actions.append(new menuRelAction(this->cycle, relationList, "F-Orthogonal", NO_PARAMS, false, FORTHOGONAL));
    actions.append(new menuRelAction(this->cycle, relationList, "Different", NO_PARAMS, false, DIFFERENT));
    actions.append(new menuRelAction(this->cycle, relationList, "A-Different", NO_PARAMS, false, ADIFFERENT));
    actions.append(new menuRelAction(this->cycle, relationList, "Only Reals", NO_PARAMS, false, REALS));
    actions.append(new menuRelAction(this->cycle, relationList, "No Tangent", NO_PARAMS, true, NORELATION, groups[0]));
    actions.append(new menuRelAction(this->cycle, relationList, "Tangent Both", NO_PARAMS, false, TANGENT, groups[0]));
    actions.append(new menuRelAction(this->cycle, relationList, "Tangent Inner", NO_PARAMS, false, TANGENT_I, groups[0]));
    actions.append(new menuRelAction(this->cycle, relationList, "Tangent Outer", NO_PARAMS, false, TANGENT_O, groups[0]));
    actions.append(new menuRelAction(this->cycle, relationList, "Steiner Power...", SINGLE_PARAM, false, STEINER_POWER));
    actions.append(new menuRelAction(this->cycle, relationList, "Cycle Angle...", SINGLE_PARAM, false, CYCLE_ANGLE));
    actions.append(new menuRelAction(this->cycle, relationList, "Cycle Cross T Distance...", SINGLE_PARAM, false, CYCLE_CROSS_T_DISTANCE));
    actions.append(new menuRelAction(this->cycle, relationList, "Product Sign...", SINGLE_PARAM, false, PRODUCT_SIGN));
    actions.append(new menuRelAction(this->cycle, relationList, "Cycle Mobius...", MATRIX_8, false, CYCLE_MOBIUS));
    actions.append(new menuRelAction(this->cycle, relationList, "Cycle Sl2...", MATRIX_4, false, CYCLE_SL2));

    // loop through and connect signals to keep relation status string updated
    for (int x = 0; x < actions.length(); x++)
        connect(actions[x], &menuRelAction::handleRelation, this, &cycleContextMenu::amendRelationList);

    // change colour action
    changeColour = new QAction("Change Colour...", this);
    connect(changeColour, &QAction::triggered, this, &cycleContextMenu::displayColourDialog);
    connect(colourDialog, &QColorDialog::colorSelected, this, &cycleContextMenu::colourSelected);

    // delete cycle action
    if (this->isDelete) {
        deletePoint = new QAction("Delete");
        connect(deletePoint, &QAction::triggered, this, &cycleContextMenu::confirmDeleteCycle);
    }
}

/*!
 * \brief cycleContextMenu::displayColourDialog Displays the colour dialog so the
 * user can select a colour for the cycle.
 */
void cycleContextMenu::displayColourDialog()
{
    colourDialog->show();
}

QString cycleContextMenu::node_label(ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}

