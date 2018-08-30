#ifndef CYCLECONTEXTMENU_H
#define CYCLECONTEXTMENU_H

#include <QMenu>
#include <QPointer>
#include <QAction>
#include <QObject>
#include <QSignalMapper>

#include "figure.h"

#include "conf.h"

//struct relationPairings {
//    GiNaC::lst ORTHAGONAL = is_orthogonal(cycle);
//    GiNaC::lst FORTHAGONAL = is_f_orthogonal(cycle);
//    GiNaC::lst DIFFERENT = is_different(cycle);
//    GiNaC::lst ADIFFERENT = is_adifferent(cycle);
//    GiNaC::lst REALS = only_reals(cycle);

//    GiNaC::lst TANGENT = is_tangent(cycle);
//    GiNaC::lst TANGENT_I = is_tangent_i(cycle);
//    GiNaC::lst TANGENT_O = is_tangent_o(cycle);

//    GiNaC::lst STEINER_POWER = steiner_power();
//    GiNaC::lst CYCLE_ANGLE = cycle_angle();
//    GiNaC::lst STEINER_POWER = cycle_cross_t_distance();
//    GiNaC::lst STEINER_POWER = product_sign();
//    GiNaC::lst STEINER_POWER = cycle_mobius();
//    GiNaC::lst STEINER_POWER = cycle_sl2();
//};

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
    cycleContextMenu(bool deleteAction = true, QObject *parent = 0);

    // Mutually compatible relations
    QPointer<QAction> isOrthogonal = nullptr;
    QPointer<QAction> isfOrthogonal = nullptr;
    QPointer<QAction> isDifferent = nullptr;
    QPointer<QAction> isADifferent = nullptr;
    QPointer<QAction> onlyReals = nullptr;

    // Mutually excluding relations
    QPointer<QAction> isTangent = nullptr;
    QPointer<QAction> isTangent_i = nullptr;
    QPointer<QAction> isTangent_o = nullptr;

    // Relations with a value
    QPointer<QAction> steinerPower = nullptr;
    QPointer<QAction> cycleAngle = nullptr;
    QPointer<QAction> cycleCrossTDistance = nullptr;
    QPointer<QAction> productSign = nullptr;
    QPointer<QAction> cycleMobius = nullptr;
    QPointer<QAction> cycleSl2 = nullptr;

    QPointer<QAction> changeColour = nullptr;
    QPointer<QAction> deletePoint = nullptr;

public slots:
    void isChecked(int relType);

signals:
    void addRelationToList(int relType);
    void removeRelationFromList(int relType);

};

#endif // CYCLECONTEXTMENU_H
