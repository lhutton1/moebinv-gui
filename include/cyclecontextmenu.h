#ifndef CYCLECONTEXTMENU_H
#define CYCLECONTEXTMENU_H

#include <QMenu>
#include <QPointer>
#include <QAction>
#include <QObject>
#include <QSignalMapper>
#include <QMessageBox>
#include <QSettings>

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
    cycleContextMenu(MoebInv::figure *f, GiNaC::ex cycle, GiNaC::lst *relationList, bool isDelete = true);

    // getters
    GiNaC::ex getCycle();
    QList<menuRelAction *> getActions();
    QAction* getTitleAction();

    // setters
    void setCycle(GiNaC::ex cycle);

    // functions
    void removeRelationFromList(MoebInv::cycle_relation relation);
    void buildCycleRelationList();
    void buildContextMenu();
    void buildActions();

    QString node_label(GiNaC::ex name);

    QPointer<QAction> changeColour = nullptr;
    QPointer<QAction> deletePoint = nullptr;

public slots:
    void confirmDeleteCycle();

signals:
    void relationsHaveChanged();
    void sceneInvalid();

private:
    QSettings *s;

    MoebInv::figure *f;
    GiNaC::ex cycle;
    GiNaC::lst *relationList;
    bool isDelete;

    QList<menuRelAction *> actions;
    QMessageBox::StandardButton confirmationMessageBox;
    menuRelActionGroup *tangentExclusive;

    // relation functions
    MoebInv::cycle_relation (*ORTHOGONAL) (const GiNaC::ex &, bool) = &MoebInv::is_orthogonal;
    MoebInv::cycle_relation (*FORTHOGONAL) (const GiNaC::ex &, bool) = &MoebInv::is_f_orthogonal;
    MoebInv::cycle_relation (*DIFFERENT) (const GiNaC::ex &, bool) = &MoebInv::is_different;
    MoebInv::cycle_relation (*ADIFFERENT) (const GiNaC::ex &, bool) = &MoebInv::is_adifferent;
    //MoebInv::cycle_relation (*REALS) (const GiNaC::ex &, bool, const GiNaC::ex &) = &MoebInv::is_real_cycle;
    MoebInv::cycle_relation (*TANGENT) (const GiNaC::ex &, bool) = &MoebInv::is_tangent;
    MoebInv::cycle_relation (*TANGENT_I) (const GiNaC::ex &, bool) = &MoebInv::is_tangent_i;
    MoebInv::cycle_relation (*TANGENT_O) (const GiNaC::ex &, bool) = &MoebInv::is_tangent_o;
    //MoebInv::cycle_relation (*STEINER_POWER) () = &MoebInv::ste;
    //CYCLE_ANGLE;
    //CYCLE_CROSS_T_DISTANCE;
    //PRODUCT_SIGN;
    //MoebInv::cycle_relation (*CYCLE_MOBIUS) (const GiNaC::ex &, bool, const GiNaC::ex &) = &MoebInv::moebius_transform;
    //CYCLE_SL2;
};

#endif // CYCLECONTEXTMENU_H
