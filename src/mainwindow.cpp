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

    // fixes qt5.1 bug that causes dock to snap back to original size
    // https://bugreports.qt.io/browse/QTBUG-65592
    resizeDocks({ui->dockWidget}, {s.value("dockMinSize").toInt()}, Qt::Horizontal);

    // generate graphics view
    scene = new graphicsScene();
    ui->graphicsView->setScene(scene);

    ui->graphicsView->recenterView();

    // set up new event
    connect(scene, &graphicsScene::newMousePress, this, &MainWindow::onMouseScenePress);
    connect(scene, &graphicsScene::newMouseHover, this, &MainWindow::onMouseSceneHover);
    connect(ui->dockWidget, &dockWidget::recenterView, ui->graphicsView, &view::recenterView);

    // initialize figure
    f = figure().set_float_eval();

    // create new labels object to create unique labels
    lblGen = new labels();

    // create new msgbox
    msgBox = new QMessageBox();
    saveDialog = new QFileDialog();

    initTreeModel();
    initMainMenu();

    // remove menu from toolbars
    setContextMenuPolicy(Qt::NoContextMenu);

    // whether to add
    isAddPoint = true;

    // update menu items
    ui->actionLabels->setChecked(true);

    REAL_CYCLES = true;

    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::onCustomContextMenu);

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

    //settings
    model->setColumnCount(2);

    //register the model
    ui->treeView->setModel(model);
    ui->treeView->setColumnWidth(0, 80);
    ui->treeView->expandAll();
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    //get generation tags to span multiple columns
    for (int x = 0; x < genMax; x++)
        ui->treeView->setFirstColumnSpanned(x, rootNode->index(), true);
}

void MainWindow::addToTree(ex cycle)
{
    QList<QStandardItem *> items;
    // get the current generation of the cycle
    int cycleGeneration = ex_to<numeric>(f.get_generation(cycle)).to_int();

    // cycle info
    QString treeLabel = node_compact_string(cycle);
    treeLabel.chop(1);

    QStandardItem *newItem = new QStandardItem(node_label(cycle));
    newItem->setTextAlignment(Qt::AlignVCenter);
    newItem->setToolTip(treeLabel);
    newItem->setEditable(false);

    items.append(newItem);

    QStandardItem *newItem2 = new QStandardItem(treeLabel);
    newItem->setTextAlignment(Qt::AlignVCenter);
    newItem->setToolTip(treeLabel);
    newItem->setEditable(false);

    items.append(newItem2);

    // add to correct place in the tree
    if (cycleGeneration < 0)
        model->insertRow(0, items);

    // search for correct generation to add sub item to
    if (cycleGeneration >= 0) {
        QString genString = QStringLiteral("Generation %1").arg(cycleGeneration);

        QList<QStandardItem *> itemList = model->findItems(
            genString,
            Qt::MatchExactly,
            0
        );

        if (itemList.length() == 1)
            itemList[0]->appendRow(items);
    }
}

void MainWindow::initMainMenu() {
    for (int x = 0; x < MENU_SIZE; x++)
        menus[x] = new cycleContextMenu(false);

    infinity = new QToolButton();
    infinity->setMenu(menus[0]);
    infinity->setText("Infinity");
    infinity->setPopupMode(QToolButton::InstantPopup);
    ui->mainToolBar->addWidget(infinity);

    real = new QToolButton();
    real->setMenu(menus[1]);
    real->setText("Real Line");
    real->setPopupMode(QToolButton::InstantPopup);
    ui->mainToolBar->addWidget(real);

    thisItem = new QToolButton();
    thisItem->setMenu(menus[2]);
    thisItem->setText("This");
    thisItem->setPopupMode(QToolButton::InstantPopup);
    ui->mainToolBar->addWidget(thisItem);

    connect(menus[0], &cycleContextMenu::addRelationToList, this, &MainWindow::addInfinityToList);
    connect(menus[0], &cycleContextMenu::removeRelationFromList, this, &MainWindow::removeInfinityFromList);
    connect(menus[1], &cycleContextMenu::addRelationToList, this, &MainWindow::addRealToList);
    connect(menus[1], &cycleContextMenu::removeRelationFromList, this, &MainWindow::removeRealFromList);
    connect(menus[2], &cycleContextMenu::addRelationToList, this, &MainWindow::addThisToList);
    connect(menus[2], &cycleContextMenu::removeRelationFromList, this, &MainWindow::removeThisFromList);
}

void MainWindow::addInfinityToList(int relType)
{
    addToList(relType, f.get_infinity());
}

void MainWindow::addRealToList(int relType)
{
    addToList(relType, f.get_real_line());
}

void MainWindow::removeInfinityFromList(int relType)
{
    removeFromList(relType, f.get_infinity());
}

void MainWindow::removeRealFromList(int relType)
{
    removeFromList(relType, f.get_real_line());
}

void MainWindow::addThisToList(int relType)
{
    // cycle doesn't exist yet so the next symbol needs to be fetched
    ex newLabel = symbol(qPrintable(lblGen->genNextLabel()));
    addToList(relType, newLabel);
}

void MainWindow::removeThisFromList(int relType)
{
    // cycle doesn't exist yet so the next symbol needs to be fetched
    ex newLabel = symbol(qPrintable(lblGen->genNextLabel()));
    removeFromList(relType, newLabel);
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

        //create new context menu
        cycleContextMenu *menu = new cycleContextMenu();

        // add cycles to scene
        graphicCycle *c = new graphicCycle(&f, cycle, ui->graphicsView, &ui->graphicsView->relativeScaleFactor, menu);

        // add to map
        cyclesMap[node_label(cycle)] = QPointer<graphicCycle>(c);

        // connect events
        connect(c, &graphicCycle::addRelationToList, this, &MainWindow::addToList);
        connect(c, &graphicCycle::removeRelationFromList, this, &MainWindow::removeFromList);
        connect(c, &graphicCycle::sceneInvalid, this, &MainWindow::sceneInvalid);
        connect(this, &MainWindow::resetRelationalList, c, &graphicCycle::resetRelationalList);

        scene->addItem(c);

        //reset infinity, real, this relations
        for (int x = 0; x < MENU_SIZE; x++) {
            menus[x]->isOrthogonal->setChecked(false);
            menus[x]->isfOrthogonal->setChecked(false);
            menus[x]->isDifferent->setChecked(false);
            menus[x]->isTangent->setChecked(false);
        }

        // add cycle to the tree
        addToTree(cycle);

        connect(c, &graphicCycle::findCycleInTree, this, &MainWindow::findCycleInTree);
    }
    addToTree(f.get_infinity());

    //shortestDistance(QPointF(3, 3), 7);
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
    QString cycleString = node_label(c);

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

/*!
 * \brief MainWindow::on_actionSave_triggered
 *
 * Save figure in the current state. Called when the user selects 'save' from the application menu.
 */
void MainWindow::on_actionSave_triggered()
{
    QString fileName;

    fileName = saveDialog->getSaveFileName(this, tr("Save Figure"), QDir::homePath(), tr("*.gar"));
    f.save(qPrintable(fileName));
}


/*!
 * \brief MainWindow::on_actionOpen_triggered
 *
 * Open figure from a '.gar' file. Called when the user selects 'open' from the application menu.
 */
void MainWindow::on_actionOpen_triggered()
{
    QString fileName;

    fileName = saveDialog->getOpenFileName(this, tr("Open Figure"), QDir::homePath(), tr("*.gar"));
    f = figure(qPrintable(fileName));
    update();
}


/*!
 * \brief MainWindow::on_actionNew_triggered
 *
 * Create a new empty figure. Called when the user selects 'new' from the application menu.
 */
void MainWindow::on_actionNew_triggered()
{
    f = figure();
    update();
}


/*!
 * \brief MainWindow::onCustomContextMenu
 * \param point Point at which the right click occured.
 *
 * Displays the context menu for the relevent cycle in the tree view.
 */
void MainWindow::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = ui->treeView->indexAt(point);
    QStandardItem *item = model->itemFromIndex(index);


    // standard case for cycles being drawn graphically
    if (item->parent() && item->parent()->hasChildren()) {
        QString itemText = item->parent()->child(item->row())->text();

        if (cyclesMap.contains(itemText)) {
            QPointer<cycleContextMenu> cMenu = cyclesMap[itemText]->getContextMenu();
            cMenu->exec(ui->treeView->viewport()->mapToGlobal(point));
        }

    // special cases for ininity and real cycles
    } else {
        index = model->index(index.row(), 0, QModelIndex());
        QString item = model->itemFromIndex(index)->text();

        if (item == "infty")
            menus[0]->exec(ui->treeView->viewport()->mapToGlobal(point));

        if (item == "R")
            menus[1]->exec(ui->treeView->viewport()->mapToGlobal(point));
    }
}

/*!
 * \brief MainWindow::on_actionLabels_toggled
 * \param labels
 *
 * Set labels as showing or hidden.
 */
void MainWindow::on_actionLabels_toggled(bool labels)
{
    if (labels)
        s.setValue("showLabels", true);
    else
        s.setValue("showLabels", false);

    s.sync();
    update();
}

ex MainWindow::shortestDistance(QPointF point,
                 double dis // This is level of sensitivity, it shall set to some fraction (say 1/40)
                 // of the current drawing width and thus depens on current zooming factor
                 )
{
    const ex x = point.x();
    const ex y = point.y();
    const ex K = f.get_all_keys(REAL_LINE_GEN);
    const ex E = f;
    double current_dis;
    double increment=.25*dis;
    ex P = lst{ex(x),ex(y)};
    ex selected_key;

    // iterator over all keys
    for (lst::const_iterator itk =ex_to<lst>(K).begin(); itk != ex_to<lst>(K).end(); ++itk) {
        ex L=ex_to<figure>(E).get_cycle(*itk);

        // This is a ginac list thus we need iteration through its components
        for (lst::const_iterator it =ex_to<lst>(L).begin(); it != ex_to<lst>(L).end(); ++it) {
            cycle2D C=ex_to<cycle2D>(*it);
            double radius2=ex_to<numeric>(C.radius_sq().evalf()).to_double();

            if (ex_to<numeric>(abs(C.get_k())).to_double() < EPSILON) {
                if (radius2 < EPSILON)
                    break; // Skipping the infinity
                // To make a point on a line selectable we disadvantage lines by adding 1
                current_dis = ex_to<numeric>(abs(C.normalize_det().val(P)).evalf()).to_double()/2.0+increment;
            } else {
                current_dis = abs(std::sqrt(ex_to<numeric>(C.normalize().val(P).evalf()).to_double()
                                                      +radius2)-std::sqrt(radius2));
                // To make a point on a circle selectable we disadvantage real circles
                if (radius2  > EPSILON)
                    current_dis+=increment;
            }
            if (current_dis < dis) {
                dis = current_dis;
                selected_key = *itk;
            }

            qDebug() << node_label(selected_key);
        }
    }
    // Returns the key for closest cycle and the distance
    // if there is no a cycle closer than dis, then zero is returned as the key
    return lst{selected_key,dis};
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // keep initial event and extend
    QMainWindow::resizeEvent(event);

    resizeDocks({ui->dockWidget}, {this->width() / 3}, Qt::Horizontal);
    ui->graphicsView->recenterView();
}
