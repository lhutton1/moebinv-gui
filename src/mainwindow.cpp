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
    initFigure();

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

void MainWindow::addToTree(ex cycle)
{
    // Add label and output to tree
    QString treeLabel = node_compact_string(cycle);

    QStandardItem *newItem = new QStandardItem(treeLabel);
    newItem->setToolTip(treeLabel);
    model->item(0)->appendRow(newItem);
}

void MainWindow::removeFromTree(graphicCycle *c)
{
//    QString treeLabel = c->getLabel() + " - " + ex_to_string(f.get_cycle_node(c->getCycle()));

//    QList<QStandardItem *> itemList = model->findItems(
//        treeLabel,
//        Qt::MatchExactly | Qt::MatchRecursive,
//        0
//    );

//    for (const auto &item : itemList) {
//        QStandardItem *parent = item->parent();
//        parent->removeRow(item->row());
//    }
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

    ex keys = f.get_all_keys();

    // for all items in the figure
    for (int x = 0; x < keys.nops(); x++) {
        // get cycle
        ex cycle = keys[x];

        // add cycles to scene
        graphicCycle *c = new graphicCycle(&f, cycle);
        scene->addItem(c);

        // connect events
        connect(c, &graphicCycle::removeFromTree, this, &MainWindow::removeFromTree);
        connect(c, &graphicCycle::addRelationToList, this, &MainWindow::addOrthogonalToList);
        connect(c, &graphicCycle::removeRelationFromList, this, &MainWindow::removeOrthogonalFromList);
        connect(this, &MainWindow::resetRelationalList, c, &graphicCycle::resetRelationalList);
        connect(c, &graphicCycle::sceneInvalid, this, &MainWindow::sceneInvalid);

        // add cycle to the tree
        addToTree(cycle);
    }
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
    ex cycle = f.add_cycle_rel(relationList, qPrintable(label));
    lblGen->advanceLabel();
    update();
    emit resetRelationalList();
    resetList(&relationList);
}

void MainWindow::sceneInvalid()
{
    update();
}
