#ifndef CYCLECONTEXTMENU_H
#define CYCLECONTEXTMENU_H

#include <QMenu>
#include <QPointer>
#include <QAction>
#include <QObject>
#include <QSignalMapper>
#include <QMessageBox>
#include <QSettings>
#include <QColorDialog>

#include <figure.h>

class cStyleDialog;
class graphicCycle;
#include "conf.h"
#include "menurelationhandler.h"
#include "definecycledialog.h"
#include "cstyledialog.h"

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
    cycleContextMenu(MoebInv::figure *f, GiNaC::ex cycle, GiNaC::lst *relationList, bool isDelete = true, bool isThis = false, bool showEditMenu = false);

    GiNaC::ex getCycle();
    QList<menuRelAction *> getActions();
    QAction* getTitleAction();

    void setCycle(GiNaC::ex cycle);

    void removeRelationFromList(menuRelAction *actionTriggered);
    void buildContextMenu();
    void buildActions();

    QString node_label(GiNaC::ex name);
    struct cycleStyleData getCycleData(const GiNaC::ex &cycle);

    QPointer<QAction> cycleStyle= nullptr;
    QPointer<QAction> deletePoint = nullptr;
    QPointer<QAction> edit = nullptr;

public slots:
    void confirmDeleteCycle();
    void amendRelationList(const bool &metric);
    void editPoint();
    void showStyleDialog();
    void updateCycleData();

signals:
    void relationsHaveChanged();
    void colourSelected(QColor colour);
    void weightSelected(double weight);
    void styleSelected(int style);
    void cycleStyleChanged(const struct cycleStyleData &data);
    void sceneInvalid();
    void changesMadeToFigure(const MoebInv::figure &originalFigure, const MoebInv::figure &changedFigure);

private:
    QSettings s;

    MoebInv::figure *f;
    GiNaC::ex cycle;
    GiNaC::lst *relationList;

    bool isDelete;
    bool isThis;
    bool showEditMenu;
    struct cycleStyleData cycleData;

    QList<menuRelAction *> actions;
    QList<menuRelActionGroup *> groups;

    cStyleDialog *cycleStyleDialog;
    defineCycleDialog *defineDialog;
    QMessageBox::StandardButton confirmationMessageBox;
};



#endif // CYCLECONTEXTMENU_H
