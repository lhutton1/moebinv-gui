#include "cyclecontextmenu.h"

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


cycleContextMenu::cycleContextMenu(MoebInv::ex cycle, GiNaC::lst *relationList, bool isDelete)
{
    this->cycle = cycle;
    this->relationList = relationList;

    actions.append(new menuRelationHandler(cycle, relationList, ORTHOGONAL, "Orthogonal", 0, true));
    actions.append(new menuRelationHandler(cycle, relationList, FORTHOGONAL, "F-Orthogonal", 0, true));
    actions.append(new menuRelationHandler(cycle, relationList, DIFFERENT, "Different", 0, true));
    actions.append(new menuRelationHandler(cycle, relationList, ADIFFERENT, "A-Different", 0, true));
    actions.append(new menuRelationHandler(cycle, relationList, TANGENT, "Tangent", 0, true));
    actions.append(new menuRelationHandler(cycle, relationList, TANGENT_I, "Tangent I", 0, true));
    actions.append(new menuRelationHandler(cycle, relationList, TANGENT_O, "Tangent O", 0, true));

    //loop through and connect signals to keep relation status string updated
    for (int x = 0; x < actions.length(); x++)
        connect(actions[x], &menuRelationHandler::triggered, this, &cycleContextMenu::relationsHaveChanged);


    for (int x = 0; x < 4; x++) {
        this->addAction(actions[x]);
    }

    this->addSeparator();

    QActionGroup *ag1 = new QActionGroup(this);
    for (int x = 4; x < 7; x++) {
        this->addAction(actions[x]);
        ag1->addAction(actions[x]);
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
    }
}

/*!
 * \brief cycleContextMenu::isChecked
 * \param relType the type of relation that has been checked
 *
 * This functions checks whether the menu item of the 'relType' relation
 * has been checked or unchecked. If it has been checked the cycle is added to the list,
 * if it has been unchecked the cycle is removed from the list.
 */
void cycleContextMenu::isChecked(int relType) {

}
