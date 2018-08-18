#include <string>
#include <iostream>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace GiNaC;

using namespace MoebInv;

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
    f = figure();

    // create new labels object to create unique labels
    lblGen = new labels();

    // create new msgbox
    msgBox = new QMessageBox();

    initTreeModel();
    initMainMenu();

    // remove menu from toolbars
    setContextMenuPolicy(Qt::NoContextMenu);

    // whether to add
    isAddPoint = true;

    REAL_CYCLES = true;

    update();
}

QString MainWindow::node_compact_string(GiNaC::ex name)
{
    std::ostringstream drawing;
    drawing << std::setprecision(FLOAT_PRECISION);
    ex_to<cycle_node>(f.get_cycle_node(name))
        .do_print_double(GiNaC::print_dflt(drawing,0), 0);
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}

QString MainWindow::node_label(GiNaC::ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
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
}

void MainWindow::onMouseSceneHover(QPointF point)
{
    QString coordinates = QString("%1, %2")
      .arg(point.x())
      .arg(point.y());

    ui->statusBar->showMessage(coordinates);
}

void MainWindow::addToList(int relType, ex cycle) {
    switch (relType) {
        case ORTHOGONAL:
            relationList.append(is_orthogonal(cycle));
            break;
        case FORTHOGONAL:
            relationList.append(is_f_orthogonal(cycle));
            break;
        case TANGENT:
            relationList.append(is_tangent(cycle));
            break;
        case DIFFERENT:
            relationList.append(is_different(cycle));
            break;
    }
}

void MainWindow::removeFromList(int relType, ex cycle) {
    lst newRelationList;
    cycle_relation relationToRemove;

    // build relation to remove
    switch(relType) {
        case ORTHOGONAL:
            relationToRemove = is_orthogonal(cycle);
            break;
        case FORTHOGONAL:
            relationToRemove = is_f_orthogonal(cycle);
            break;
        case TANGENT:
            relationToRemove = is_tangent(cycle);
            break;
        case DIFFERENT:
            relationToRemove = is_different(cycle);
            break;
    }


    // now loop through current list and build new list
    for (int x = 0; x < relationList.nops(); x++) {
        if (node_label(relationList.op(x)) != node_label(relationToRemove)) {
            newRelationList.append(relationList.op(x));
        }
    }

    relationList = newRelationList;
}

void MainWindow::resetList(GiNaC::lst *list) {
    list->remove_all();
}

void MainWindow::initTreeModel()
{
    model = new QStandardItemModel();
    QStandardItem *rootNode = model->invisibleRootItem();
    int genMax = f.get_max_generation() + 1;

    for(int x = 0; x < genMax; x++) {
        QStandardItem *genItem = new QStandardItem(QString::fromStdString("Generation " + std::to_string(x)));
        rootNode->appendRow(genItem);
    }

    //register the model
    ui->treeView->setModel(model);
    ui->treeView->expandAll();
}

void MainWindow::addToTree(ex cycle)
{
    // get the current generation of the cycle
    int cycleGeneration = ex_to<numeric>(f.get_generation(cycle)).to_int();

    // add label and output to tree
    QString treeLabel = node_label(cycle) + " - " + node_compact_string(cycle);

    QStandardItem *newItem = new QStandardItem(treeLabel);
    newItem->setToolTip(treeLabel);

    // add to correct place in the tree
    if (cycleGeneration < 0)
        model->appendRow(newItem);
    if (cycleGeneration >= 0)
        model->item(cycleGeneration)->appendRow(newItem);
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
    addToList(relType, f.get_infinity());
}

void MainWindow::addRealToList(int relType)
{
    addToList(relType, f.get_real_line());
}

void MainWindow::removeInfinityFromList()
{
    //removeFromList(relType, )
}

void MainWindow::removeRealFromList()
{
    //removeOrthogonalFromList(relType, )
}

void MainWindow::on_actionPan_toggled(bool pan)
{
    if (pan) {
        ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        isAddPoint = false;
    } else {
        ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
        isAddPoint = true;
    }
}

void MainWindow::update()
{
    // remove data
    scene->clear();
    initTreeModel();
    resetList(&relationList);

    ex keys = f.get_all_keys(REAL_LINE_GEN);

    // for all items in the figure
    for (int x = 0; x < keys.nops(); x++) {
        // get cycle
        ex cycle = keys[x];

        // add cycles to scene
        graphicCycle *c = new graphicCycle(&f, cycle, ui->graphicsView, &ui->graphicsView->relativeScaleFactor);
        scene->addItem(c);

        // connect events
        connect(c, &graphicCycle::addRelationToList, this, &MainWindow::addToList);
        connect(c, &graphicCycle::removeRelationFromList, this, &MainWindow::removeFromList);
        connect(this, &MainWindow::resetRelationalList, c, &graphicCycle::resetRelationalList);
        connect(c, &graphicCycle::sceneInvalid, this, &MainWindow::sceneInvalid);
        //connect(c, &graphicCycle::findCycleInTree, this, &MainWindow::findCycleInTree);

        // add cycle to the tree

        addToTree(cycle);
    }
    //addToTree(f.get_infinity());
}

/*!
 * \brief MainWindow::addCycle Add a cycle to the figure.
 * \param mousePos Coordinates of mouse on the scene.
 *
 * Adds a cycle to the figure then draws it on the scene.
 */
void MainWindow::addPoint(QPointF mousePos)
{
    if (isAddPoint) {
        double x = mousePos.x();
        double y = mousePos.y();

        // gen new label
        QString label = lblGen->genNextLabel();

        // add cycle to the figure
        ex cycle = f.add_point(lst{x, y}, qPrintable(label));

        lblGen->advanceLabel();

        // refresh
        update();
    }
}

/*!
 * \brief MainWindow::on_actionCreate_Cycle_triggered
 *
 * Function to create cycle based on relations that have been added.
 */
void MainWindow::on_actionCreate_Cycle_triggered()
{
    // make sure that the list isn't empty before adding cycle
    if (relationList.nops() <= 0) {
        msgBox->warning(0, "No cycles in relation", "For a cycle to be created there must be cycles in the relation.");
        return;
    }

    QString label = lblGen->genNextLabel();
    ex newName = symbol(qPrintable(label));

    // only real cycles
    if (REAL_CYCLES) {
        relationList.append(only_reals(newName));
    }

    ex cycle = f.add_cycle_rel(relationList, newName);

    lblGen->advanceLabel();
    update();

    emit resetRelationalList();
    resetList(&relationList);
}

void MainWindow::sceneInvalid()
{
    update();
}

void MainWindow::findCycleInTree(GiNaC::ex c)
{
    QString cycleString = node_label(c) + " - " + node_compact_string(c);

    QList<QStandardItem *> itemList = model->findItems(
        cycleString,
        Qt::MatchExactly | Qt::MatchRecursive,
        0
    );

    for (const auto &item : itemList) {
        QStandardItem *parent = item->parent();
        ui->treeView->setCurrentIndex(item->index());
    }
}
