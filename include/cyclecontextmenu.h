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

    GiNaC::ex getCycle();
    QList<menuRelAction *> getActions();
    QAction* getTitleAction();

    void setCycle(GiNaC::ex cycle);

    void removeRelationFromList(MoebInv::cycle_relation relation);
    void buildContextMenu();
    void buildActions();

    QString node_label(GiNaC::ex name);

    QPointer<QAction> changeColour = nullptr;
    QPointer<QAction> changeStyle = nullptr;
    QPointer<QAction> changeWeight = nullptr;
    QPointer<QAction> deletePoint = nullptr;

public slots:
    void confirmDeleteCycle();
    void amendRelationList();
    void displayColourDialog();

signals:
    void relationsHaveChanged();
    void colourSelected(QColor colour);
    void sceneInvalid();

private:
    QSettings *s;

    MoebInv::figure *f;
    GiNaC::ex cycle;
    GiNaC::lst *relationList;
    bool isDelete;

    QList<menuRelAction *> actions;
    QList<menuRelActionGroup *> groups;
    QMessageBox::StandardButton confirmationMessageBox;

    QColorDialog *colourDialog;
};



#endif // CYCLECONTEXTMENU_H
