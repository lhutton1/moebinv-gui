#ifndef CYCLECONTEXTMENU_H
#define CYCLECONTEXTMENU_H

#include <QMenu>
#include <QPointer>
#include <QAction>
#include <QObject>
#include <QSignalMapper>
#include <QMessageBox>

#include "figure.h"
#include "conf.h"

#include "menurelationhandler.h"

/*!
 * \brief The cycleContextMenu class
 *
 * This class creates a context menu which is then used by each of the
 * cycles created on the scene. It then connects each of the menu items
 * so they function as intended.
 */
class cycleContextMenu : public QMenu
{
    Q_OBJECT

public:
    cycleContextMenu(GiNaC::ex cycle, GiNaC::lst *relationList, bool isDelete = true);
    QString node_label(GiNaC::ex name);

    QPointer<QAction> changeColour = nullptr;
    QPointer<QAction> deletePoint = nullptr;

public slots:
    void isChecked(int relType);
    void confirmDeleteCycle();

signals:
    void relationsHaveChanged();

private:
    GiNaC::ex cycle;
    GiNaC::lst *relationList;

    QList<menuRelationHandler *> actions;
    QMessageBox::StandardButton confirmationMessageBox;

    // relation functions
    MoebInv::cycle_relation (*ORTHOGONAL) (const GiNaC::ex &, bool) = &MoebInv::is_orthogonal;
    MoebInv::cycle_relation (*FORTHOGONAL) (const GiNaC::ex &, bool) = &MoebInv::is_f_orthogonal;
    MoebInv::cycle_relation (*DIFFERENT) (const GiNaC::ex &, bool) = &MoebInv::is_different;
    MoebInv::cycle_relation (*ADIFFERENT) (const GiNaC::ex &, bool) = &MoebInv::is_adifferent;
    //MoebInv::cycle_relation (*REALS) (const GiNaC::ex &, bool) = &MoebInv::is_real_cycle;
    MoebInv::cycle_relation (*TANGENT) (const GiNaC::ex &, bool) = &MoebInv::is_tangent;
    MoebInv::cycle_relation (*TANGENT_I) (const GiNaC::ex &, bool) = &MoebInv::is_tangent_i;
    MoebInv::cycle_relation (*TANGENT_O) (const GiNaC::ex &, bool) = &MoebInv::is_tangent_o;
    //STEINER_POWER;
    //CYCLE_ANGLE;
    //CYCLE_CROSS_T_DISTANCE;
    //PRODUCT_SIGN;
    //CYCLE_MOBIUS;
    //CYCLE_SL2;
};

#endif // CYCLECONTEXTMENU_H
