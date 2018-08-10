#include <string>
#include <iostream>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "line.h"

using namespace GiNaC;
using namespace MoebInv;

QString ex_to_string(const ex & E)
{
    std::ostringstream drawing;
    drawing << E;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}

/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // generate graphics view
    scene = new graphicsScene();
    ui->graphicsView->setScene(scene);


    // set up new event
    connect(scene, &graphicsScene::newMousePress, this, &MainWindow::onMouseScenePress);
    connect(scene, &graphicsScene::newMouseHover, this, &MainWindow::onMouseSceneHover);

    // initialize figure
    initFigure();

    // create new labels object to create unique labels
    lblGen = new labels();

    // create new msgbox
    msgBox = new QMessageBox();

    initTreeModel();
    initMainMenu();

    //real line
    ex ln = f.get_real_line();
    QString label = "Re";
    line *ln2 = new line(&f, ln, label, scene->assignMinZIndex());
    scene->addItem(ln2);

    setContextMenuPolicy(Qt::NoContextMenu);
}

/*!
 * \brief MainWindow::~MainWindow MainWindow destructor.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief MainWindow::onMouseScenePress Mouse press on scene.
 * \param point Point at which the mouse was pressed, given in x and y corrdinates.
 */
void MainWindow::onMouseScenePress(QPointF location)
{
    addPoint(location);

    // future tools here..
    //
    //
}

void MainWindow::onMouseSceneHover(QPointF point)
{
    QString coordinates = QString("%1, %2")
      .arg(point.x())
      .arg(point.y());

    ui->statusBar->showMessage(coordinates);
}

/*!
 * \brief MainWindow::addCycle Add a cycle to the figure.
 * \param mousePos Coordinates of mouse on the scene.
 *
 * Adds a cycle to the figure then draws it on the scene.
 */
void MainWindow::addPoint(QPointF mousePos)
{
    // gen new label
    QString label = lblGen->genNextLabel();

    // add cycle to the figure
    ex cycle = f.add_point(lst{mousePos.x(), mousePos.y()}, qPrintable(label));

    // now draw the point
    point *p = new point(&f, cycle, label, scene->assignMaxZIndex());

    //set generation
    //p->setGeneration(1);

    connect(p, &point::removeFromTree, this, &MainWindow::removeFromTree);
    connect(p, &point::addRelationToList, this, &MainWindow::addOrthogonalToList);
    connect(p, &point::removeRelationFromList, this, &MainWindow::removeOrthogonalFromList);
    connect(this, &MainWindow::resetRelationalList, p, &point::resetRelationalList);

    scene->addItem(p);
    lblGen->advanceLabel();

    // now add to tree
    addToTree(p);
}

/*!
 * \brief MainWindow::on_actionCreate_Cycle_triggered
 *
 * Function to create cycle based on relations that have been added.
 */
void MainWindow::on_actionCreate_Cycle_triggered()
{
    double radius = 0;

    // make sure that the list isn't empty before adding cycle
    if (orthogonalList.nops() <= 0) {
        msgBox->warning(0, "No cycles in relation", "For a cycle to be created there must be cycles in the relation.");
        return;
    }

    // create cycle
    QString label = lblGen->genNextLabel();
    ex cycle = f.add_cycle_rel(orthogonalList, qPrintable(label));
    cycle2D c = ex_to<cycle2D>(f.get_cycle(cycle)[0]);

    // check to make sure cycle is not infinite
    if (ex_to<numeric>(c.radius_sq()) < 0) {
        msgBox->warning(0, "Infinite cycles", "The number of possible cycles for this relation is infinite, therefore it cannot be displayed");
        f.remove_cycle_node(cycle);
        return;
    }

    radius = sqrt(ex_to<numeric>(c.radius_sq()).to_double());

    // check that cycle exists
    if (radius == 0) {
        msgBox->warning(0, "Cycle non-existant", "Cycle for this relation does not exist.");
        f.remove_cycle_node(cycle);
        return;
    }

    // draw the new circle
    circle *circ = new circle(&f, cycle, label, scene->assignMinZIndex());
    scene->addItem(circ);
    lblGen->advanceLabel();
    addToTree(circ);

    connect(circ, &circle::removeFromTree, this, &MainWindow::removeFromTree);
    connect(circ, &circle::addRelationToList, this, &MainWindow::addOrthogonalToList);
    connect(circ, &circle::removeRelationFromList, this, &MainWindow::removeOrthogonalFromList);

    // reset relation list
    resetList(&orthogonalList);
    emit resetRelationalList();
}

/*!
 * \brief MainWindow::initFigure Initialize figure
 *
 * Create a new figure and apply any additional settings.
 */
void MainWindow::initFigure()
{
    f = figure();

    // Add any additional settings here
    //
    //
}

void MainWindow::addOrthogonalToList(int relType, ex cycle) {
    switch (relType) {
        case ORTHOGONAL:
            orthogonalList.append(is_orthogonal(cycle));
            break;
        case FORTHOGONAL:
            orthogonalList.append(is_f_orthogonal(cycle));
            break;
        case TANGENT:
            orthogonalList.append(is_tangent(cycle));
            break;
        case DIFFERENT:
            orthogonalList.append(is_different(cycle));
            break;
    }
}

void MainWindow::removeOrthogonalFromList(ex cycle) {

}

void MainWindow::resetList(GiNaC::lst *list) {
    list->remove_all();
}

void MainWindow::initTreeModel()
{
        model = new QStandardItemModel();
        QStandardItem *rootNode = model->invisibleRootItem();

        //defining generations
        QStandardItem *gen0Item = new QStandardItem("Generation 0");
        QStandardItem *gen1Item = new QStandardItem("Generation 1");
        QStandardItem *gen2Item = new QStandardItem("Generation 2");

        //building up the hierarchy
        rootNode->appendRow(gen0Item);
        rootNode->appendRow(gen1Item);
        rootNode->appendRow(gen2Item);

        //register the model
        ui->treeView->setModel(model);
        ui->treeView->expandAll();
}

void MainWindow::addToTree(graphicCycle *p)
{
    // Add label and output to tree
    QString treeLabel = p->getLabel() + " - " + ex_to_string(f.get_cycle_node(p->getCycle()));

    QStandardItem *newItem = new QStandardItem(treeLabel);
    newItem->setToolTip(treeLabel);
    model->item(0)->appendRow(newItem);
}

void MainWindow::removeFromTree(graphicCycle *c)
{
    QString treeLabel = c->getLabel() + " - " + ex_to_string(f.get_cycle_node(c->getCycle()));

    QList<QStandardItem *> itemList = model->findItems(
        treeLabel,
        Qt::MatchExactly | Qt::MatchRecursive,
        0
    );

    for (const auto &item : itemList) {
        QStandardItem *parent = item->parent();
        parent->removeRow(item->row());
    }
}

void MainWindow::initMainMenu() {
    for (int x = 0; x < MENU_SIZE; x++)
        menus[x] = new cycleContextMenu(false);

    QToolButton *infinity = new QToolButton();
    infinity->setMenu(menus[0]);
    infinity->setText("Infinity");
    infinity->setPopupMode(QToolButton::InstantPopup);
    ui->mainToolBar->addWidget(infinity);

    QToolButton *real = new QToolButton();
    real->setMenu(menus[1]);
    real->setText("Real Line");
    real->setPopupMode(QToolButton::InstantPopup);
    ui->mainToolBar->addWidget(real);

    QToolButton *thisItem = new QToolButton();
    thisItem->setMenu(menus[2]);
    thisItem->setText("This");
    thisItem->setPopupMode(QToolButton::InstantPopup);
    ui->mainToolBar->addWidget(thisItem);

    connect(menus[0], &cycleContextMenu::addRelationToList, this, &MainWindow::addInfinityToList);
    connect(menus[0], &cycleContextMenu::removeRelationFromList, this, &MainWindow::removeInfinityFromList);
    connect(menus[1], &cycleContextMenu::addRelationToList, this, &MainWindow::addRealToList);
    connect(menus[1], &cycleContextMenu::removeRelationFromList, this, &MainWindow::removeRealFromList);
    //connect(menus[2], &cycleContextMenu::addRelationToList, this, &MainWindow::addThisToList);
    //connect(menus[2], &cycleContextMenu::removeRelationFromList, this, &MainWindow::removeThisFromList);
}

void MainWindow::addInfinityToList(int relType)
{
    addOrthogonalToList(relType, f.get_infinity());
}

void MainWindow::addRealToList(int relType)
{
    addOrthogonalToList(relType, f.get_real_line());
}

void MainWindow::removeInfinityFromList()
{
    //removeOrthogonalFromList(relType, )
}

void MainWindow::removeRealFromList()
{
    //removeOrthogonalFromList(relType, )
}
