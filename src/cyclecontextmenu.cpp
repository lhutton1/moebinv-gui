#include "cyclecontextmenu.h"
#include <QDebug>

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief cycleContextMenu::cycleContextMenu Context menu constructor
 *
 * Create a new context menu.
 *      orthogonal
 *      forthogonal
 *      different
 *      tangent
 *      -----------
 *      delete
 */


cycleContextMenu::cycleContextMenu(figure *f, ex cycle, lst *relationList, bool isDelete)
{
    this->f = f;
    this->cycle = cycle;
    this->relationList = relationList;

    tangentExclusive = new menuRelActionGroup(this);

    actions.append(new menuRelAction(&this->cycle, relationList, "Orthogonal", 0, false, ORTHOGONAL));
    actions.append(new menuRelAction(&this->cycle, relationList, "F-Orthogonal", 0, false, FORTHOGONAL));
    actions.append(new menuRelAction(&this->cycle, relationList, "Different", 0, false, DIFFERENT));
    actions.append(new menuRelAction(&this->cycle, relationList, "A-Different", 0, false, ADIFFERENT));
    actions.append(new menuRelAction(&this->cycle, relationList, "No Tangent", 0, true, nullptr, tangentExclusive));
    actions.append(new menuRelAction(&this->cycle, relationList, "Tangent Both", 0, false, TANGENT, tangentExclusive));
    actions.append(new menuRelAction(&this->cycle, relationList, "Tangent Inner", 0, false, TANGENT_I, tangentExclusive));
    actions.append(new menuRelAction(&this->cycle, relationList, "Tangent Outer", 0, false, TANGENT_O, tangentExclusive));

    //loop through and connect signals to keep relation status string updated
    for (int x = 0; x < actions.length(); x++)
        connect(actions[x], &menuRelAction::triggered, this, &cycleContextMenu::buildCycleRelationList);


    for (int x = 0; x < 4; x++) {
        this->addAction(actions[x]);
    }

    this->addSeparator();

    for (int x = 4; x < 8; x++) {
        this->addAction(actions[x]);
        tangentExclusive->addRelAction(actions[x]);
    }

    this->addSeparator();

    // Change colour option
    changeColour = new QAction("Change Colour...", this);
    this->addAction(changeColour);

    // Loop through items that have been added
    if (isDelete) {
        this->addSeparator();

        deletePoint = new QAction("Delete");
        this->addAction(deletePoint);

        connect(deletePoint, &QAction::triggered, this, &cycleContextMenu::confirmDeleteCycle);
    }
}

void cycleContextMenu::setCycle(ex cycle)
{
    this->cycle = cycle;
}

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

void cycleContextMenu::buildCycleRelationList()
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

    // check whether the cycle triggered needs adding or removing
    if (actionTriggered->hasRelation()) {
        if (actionTriggered->isChecked()) {
            relationList->append(actionTriggered->getRelation());
        } else {
            this->removeRelationFromList(actionTriggered->getRelation());
        }
    }

    emit relationsHaveChanged();
}

void cycleContextMenu::removeRelationFromList(cycle_relation relation)
{
    GiNaC::lst newRelationList;

    // linear search through list to find item to remove
    for (int x = 0; x < relationList->nops(); x++) {
        if (node_label(relationList->op(x)) != node_label(relation)) {
            newRelationList.append(relationList->op(x));
        }
    }

    *relationList = newRelationList;
}

QString cycleContextMenu::node_label(ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}

