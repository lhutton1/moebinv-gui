#include <string>
#include <iostream>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief MainWindow::MainWindow Create the main window
 * \param parent - parent widget.
 *
 * Creates the main window, providing the MoebInv gui.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // when the window is created, return to the size that it was before closing
    this->resize(s.value("mainwindow-size", QSize(1000, 600)).toSize());
    this->move(s.value("mainwindow-pos", QPoint(200, 200)).toPoint());

    // fixes qt5.1 bug that causes dock to snap back to original size
    // https://bugreports.qt.io/browse/QTBUG-65592
    this->resizeDocks({ui->dockWidgetRight}, {200}, Qt::Horizontal);
    this->setContextMenuPolicy(Qt::NoContextMenu);

    // initialize objects
    this->scene = new graphicsScene();
    ui->graphicsView->setScene(scene);

    this->statusCoordinates = new QLabel();
    this->statusRelations = new QLabel();
    ui->statusBar->addWidget(statusCoordinates);
    ui->statusBar->addPermanentWidget(statusRelations);

    this->msgBox = new QMessageBox();
    this->saveDialog = new QFileDialog();
    this->settingDialog = new settingsDialog(this);
    this->settingDialog->setModal(true);
    this->propDialog = new propertiesDialog(this);
    this->applicationHelpDialog = new helpDialog(this);

    this->undoStack = new QUndoStack(this);
    this->undoStack->setUndoLimit(s.value("undoLimit").toInt());

    this->menus[0] = new cycleContextMenu(&f, f.get_infinity(), &relationList, false);
    this->menus[1] = new cycleContextMenu(&f, f.get_real_line(), &relationList, false);
    this->menus[2] = new cycleContextMenu(&f, nextSymbol, &relationList, true);
    buildToolBar();

    this->lblGen = new labels(&this->f);
    this->nextSymbol = lblGen->genNextSymbol(this->nextSymbol);

    this->isAddPoint = true;

    this->saveDirectory = QDir(s.value("defaultSaveDirectory").toString());
    this->saved = true;
    this->defaultDirectoryInUse = true;

    // PLACE NEW MENU ITEMS HERE....
    //
    //

    // tooltips
    ui->actionCreate_Cycle->setToolTip("Create a cycle by using the currently selected relations.");
    ui->actionDefine_cycle->setToolTip("Define a cycle by providing values, helping to create an accurate cycle.");
    ui->actionzoomIn->setToolTip("Zoom the view in by a factor of: " + s.value("zoomFactorAmount").toString());
    ui->actionzoomOut->setToolTip("Zoom the view out by a factor of: " + s.value("zoomFactorAmount").toString());
    ui->actionPan->setToolTip("Move the view around by grabbing it with the mouse");

    // connect signals to slots
    connect(scene, &graphicsScene::newMouseLeftPress, this, &MainWindow::addPoint);
    connect(scene, &graphicsScene::newMouseRightPress, this, &MainWindow::onMouseSceneRightPress);
    connect(scene, &graphicsScene::newMouseHover, this, &MainWindow::onMouseSceneHover);
    connect(ui->dockWidgetRight, &dockWidget::recenterView, ui->graphicsView, &view::recenterView);
    connect(ui->dockWidgetRight, &dockWidget::calculateDockToWindowPercentage, this, &MainWindow::onCalculateDockRatio);
    connect(ui->graphicsView, &view::highlightClosestCycle, this, &MainWindow::highlightClosestCycle);
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::onCustomContextMenu);
    connect(scene, &graphicsScene::unHighlightCycle, this, &MainWindow::unHighlightCycle);
    connect(settingDialog, &settingsDialog::setBackgroundColour, ui->graphicsView, &view::setBackgroundColour);
    connect(settingDialog, &settingsDialog::saveDirectoryHasChanged, this, &MainWindow::saveDirectoryHasChanged);
    connect(ui->actionUndo, &QAction::triggered, this->undoStack, &QUndoStack::undo);
    connect(ui->actionRedo, &QAction::triggered, this->undoStack, &QUndoStack::redo);
    connect(ui->actionUser_Manual, &QAction::triggered, this->applicationHelpDialog, &helpDialog::show);
    connect(ui->actionProperties, &QAction::triggered, this->propDialog, &propertiesDialog::show);
    connect(ui->actionSettings, &QAction::triggered, this->settingDialog, &settingsDialog::show);
    connect(this->propDialog, &propertiesDialog::metricChanged, this, &MainWindow::changeMetric);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::treeViewClicked);

    initTreeModel();
    initialiseDefaultSettings();
    update();
}


/*!
 * \brief MainWindow::~MainWindow MainWindow destructor.
 */
MainWindow::~MainWindow()
{
    // save window position before destroying
    s.setValue("mainwindow-size", this->size());
    s.setValue("mainwindow-pos", this->pos());

    // flag to say that tools/settings have been saved
    s.setValue("defaultsInitialised", true);

    delete ui;
}


/*!
 * \brief MainWindow::onMouseSceneRightPress Triggered on right click on scene.
 * \param location
 *
 * Triggered on right click on scene. Checks whether a cycle is currently being hovered,
 * if it is the cycles context menu is displayed.
 */
void MainWindow::onMouseSceneRightPress(const QPointF &point)
{
    if (!prevHoveredCycle.isNull()) {
        cycleContextMenu *cMenu = prevHoveredCycle->getContextMenu();

        // translate scene coordinates to global coordinates
        QPoint sceneCoordinates = ui->graphicsView->mapFromScene(point);
        QPoint globalCoordinates = ui->graphicsView->mapToGlobal(sceneCoordinates);

        cMenu->exec(globalCoordinates);
    }
}


/*!
 * \brief MainWindow::onMouseSceneHover Triggered when the scene is hovered.
 * \param point point at which the scene is being hovered.
 *
 * Once triggered, this slot updates the coordinates displayed in the status bar.
 */
void MainWindow::onMouseSceneHover(const QPointF &point)
{
    QString coordinates = QString("Coordinates: %1, %2")
      .arg(point.x())
      .arg(point.y());

    statusCoordinates->setText(coordinates);
}


/*!
 * \brief MainWindow::initTreeModel
 *
 * Create the tree model, setting up the labels for each generation that
 * currently exists in the figure.
 */
void MainWindow::initTreeModel()
{
    this->model = new treeModel();
    QStandardItem *rootNode = this->model->invisibleRootItem();
    int genMax = f.get_max_generation() + 1;

    // create a QStandardItem for each generation
    for(int x = 0; x < genMax; x++) {
        QStandardItem *genItem = new QStandardItem(QString::fromStdString("Generation " + std::to_string(x)));
        rootNode->appendRow(genItem);
    }

    // create 2 columns: 1 for the label the other for the description
    this->model->setColumnCount(2);

    // register the model
    ui->treeView->setModel(model);
    ui->treeView->setColumnWidth(0, 80);
    ui->treeView->expandAll();
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    // get generation items to span multiple columns
    for (int x = 0; x < genMax; x++)
        ui->treeView->setFirstColumnSpanned(x, rootNode->index(), true);
}


/*!
 * \brief MainWindow::addToTree
 * \param cycle cycle to add to the tree
 * \param colour colour of the cycle, to be displayed in a colour square
 *
 * Adds a cycle to the tree. The first item in a row is displays the colour and the label,
 * the second item in a row displays the cycle information.
 */
void MainWindow::addToTree(const ex &cycle, const QColor &colour)
{
    QList<QStandardItem *> items;

    // get the current generation of the cycle
    int cycleGeneration = ex_to<numeric>(f.get_generation(cycle)).to_int();

    // remove new line character
    QString itemDesc = node_compact_string(cycle);
    itemDesc.chop(1);

    QStandardItem *newItem1 = new QStandardItem(node_label(cycle));
    newItem1->setTextAlignment(Qt::AlignVCenter);
    newItem1->setData(QVariant(colour), Qt::DecorationRole);
    newItem1->setToolTip(node_compact_string(cycle));
    newItem1->setEditable(false);

    QStandardItem *newItem2 = new QStandardItem(itemDesc);
    newItem2->setTextAlignment(Qt::AlignVCenter);
    newItem2->setToolTip(itemDesc);
    newItem2->setEditable(false);

    items.append(newItem1);
    items.append(newItem2);

    // add to correct place in the tree
    // item doesn't belong to a generation
    if (cycleGeneration < 0)
        model->insertRow(0, items);

    // search for correct generation to add sub item to
    if (cycleGeneration >= 0) {
        QString genString = QStringLiteral("Generation %1").arg(cycleGeneration);
        QList<QStandardItem *> itemList = model->findItems(genString, Qt::MatchExactly, 0);

        if (itemList.length() == 1)
            itemList[0]->appendRow(items);
    }

    // make sure contents of columns are visible
    ui->treeView->resizeColumnToContents(0);
    ui->treeView->resizeColumnToContents(1);
}


/*!
 * \brief MainWindow::initMainMenu
 *
 * Create menus for 3 custom relations: infinity, real line and this.
 */
void MainWindow::initMainMenu() {
    menus[0] = new cycleContextMenu(&f, f.get_infinity(), &relationList, false);
    menus[1] = new cycleContextMenu(&f, f.get_real_line(), &relationList, false);
    menus[2] = new cycleContextMenu(&f, nextSymbol, &relationList, false, true);

    connect(menus[0], &cycleContextMenu::relationsHaveChanged, this, &MainWindow::buildRelationStatus);
    connect(menus[1], &cycleContextMenu::relationsHaveChanged, this, &MainWindow::buildRelationStatus);
    connect(menus[2], &cycleContextMenu::relationsHaveChanged, this, &MainWindow::buildRelationStatus);
    this->thisItem->setMenu(menus[2]);
    connect(menus[2], &QMenu::aboutToShow, this, &MainWindow::thisContextMenuUpdate);
}


/*!
 * \brief MainWindow::thisContextMenuUpdate
 *
 * Update the context menu displayed when 'this' is pressed to the most current symbol.
 * This means that the context menu will always display the symbol of the next cycle to be added.
 */
void MainWindow::thisContextMenuUpdate()
{
    menus[2]->setCycle(nextSymbol);
}


/*!
 * \brief MainWindow::on_actionPan_toggled toggle panning
 * \param pan
 *
 * When the pan button is clicked, enable it in the view and make sure
 * that clicking on the view doesn't add a new point.
 */
void MainWindow::on_actionPan_toggled(bool pan)
{
    if (pan) {
        isAddPoint = false;
        ui->graphicsView->setPanningEnabled(true);
        ui->graphicsView->setCursor(Qt::OpenHandCursor);
    } else {
        isAddPoint = true;
        ui->graphicsView->setPanningEnabled(false);
        ui->graphicsView->setCursor(Qt::ArrowCursor);
    }
}


/*!
 * \brief MainWindow::update Update the scene.
 *
 * Updates the scene, displaying any changes that need to be made.
 */
void MainWindow::update()
{
    cycleContextMenu *menu;
    bool isGen0;

    // remove data
    scene->clear();
    initTreeModel();
    relationList.remove_all();
    cyclesMap.clear();
    initMainMenu();

    // for all items in the figure
    for (auto key: f.get_all_keys_sorted(REAL_LINE_GEN)) {
        // get cycle
        ex cycle = key;

        // check cycle generation
        if (ex_to<numeric>(f.get_generation(cycle)).to_int() == 0)
            isGen0 = true;
        else
            isGen0 = false;

        // assign menu
        if (cycle.is_equal(f.get_real_line()))
            menu = menus[1];
        else
            menu = new cycleContextMenu(&f, cycle, &relationList, true, false, isGen0);

        connect(menu, &cycleContextMenu::relationsHaveChanged, this, &MainWindow::buildRelationStatus);
        connect(menu, &cycleContextMenu::sceneInvalid, this, &MainWindow::sceneInvalid);
        connect(menu, &cycleContextMenu::changesMadeToFigure, this, &MainWindow::changesMadeToFigure);

        struct cycleStyleData d = getCycleData(cycle);

        // add cycles to scene
        graphicCycle *c = new graphicCycle(&f, cycle, &ui->graphicsView->relativeScaleFactor, menu, d);
        connect(c, &graphicCycle::sceneInvalid, this, &MainWindow::sceneInvalid);
        connect(c, &graphicCycle::changesMadeToFigure, this, &MainWindow::changesMadeToFigure);
        connect(this, &MainWindow::escPressed, c, &graphicCycle::cancelMovement);

        // add to map
        cyclesMap[node_label(cycle)] = QPointer<graphicCycle>(c);

        // add item to the scene
        scene->addItem(c);

        // add cycle to the tree
        addToTree(cycle, d.colour);
        connect(c, &graphicCycle::findCycleInTree, this, &MainWindow::findCycleInTree);
    }

    // add the only reals cycle relation if automatic is selected, then build the relation status bar
    if (s.value("automaticOnlyReals").toBool()) {
        relationList.append(lst{nextSymbol, REALS, only_reals(nextSymbol), lst{}});
    }
    buildRelationStatus();

    // add all items to the tree
    addToTree(f.get_infinity(), Qt::black);
}


/*!
 * \brief MainWindow::addPoint Add a point to the figure.
 * \param mousePos Coordinates of mouse on the scene.
 *
 * Adds a point to the figure then draws it on the scene.
 */
void MainWindow::addPoint(QPointF mousePos)
{
    MoebInv::figure originalFigure = this->f;

    if (isAddPoint) {
        double x = mousePos.x();
        double y = mousePos.y();

        // add cycle to the figure
        nextSymbol = lblGen->genNextSymbol(this->nextSymbol, true);

        ex cycle = f.add_point(lst{x, y}, nextSymbol);

        struct cycleStyleData cycleData;
        cycleData.colour = s.value("defaultGraphicsColour").value<QColor>();
        cycleData.lineStyle = s.value("defaultLineStyle").toDouble();
        cycleData.lineWidth = s.value("defaultLineWidth").toDouble();
        setCycleAsy(cycle, cycleData);

        // generate next symbol
        lblGen->advanceLabel();
        nextSymbol = lblGen->genNextSymbol(this->nextSymbol);

        // refresh
        changesMadeToFigure(originalFigure, this->f);
        update();

    }
}


/*!
 * \brief MainWindow::sceneInvalid a slot that is called when
 * the scene needs to be updated.
 */
void MainWindow::sceneInvalid()
{
    update();
}


/*!
 * \brief MainWindow::findCycleInTree Find a cycle in the tree.
 * \param c cycle to be found
 *
 * Use qt's recursive item search to find an item in the tree.
 */
void MainWindow::findCycleInTree(const GiNaC::ex &cycle)
{
    QString cycleString = node_label(cycle);

    QList<QStandardItem *> itemList = model->findItems(
        cycleString,
        Qt::MatchExactly | Qt::MatchRecursive,
        0
    );

    for (const auto &item : itemList) {
        ui->treeView->setCurrentIndex(item->index());
    }
}


/*!
 * \brief MainWindow::on_actionSave_triggered
 *
 * Save figure in the current state. Called when the user selects 'save'
 * from the application menu. This save functions checks whether the figure
 * has previously been saved before. If it hasn't then the function will act
 * like 'save as' by making a file dialog pop up. If it has been saved before
 * the figure is saved to the location it was previously saved to.
 */
void MainWindow::on_actionSave_triggered()
{
    this->checkDescription();

    QDir defaultPath = QDir(s.value("defaultSaveDirectory").toString());

    if (s.value("figureName").toString() == "unnamed" || s.value("figureName").toString() == "."
        || defaultPath.absolutePath() == this->saveDirectory.absolutePath()) {

        QDir filePath = QDir(saveDialog->getSaveFileName(this, tr("Save Figure"), defaultPath.absolutePath(), tr("*.gar")));

        if (filePath.path() == ".")
            return;

        this->saveDirectory = filePath;
        s.setValue("figureName", filePath.dirName());
    }

    f.set_metric(getMetricType(s.value("pointMetric").toInt()), getMetricType(s.value("cycleMetric").toInt()));
    f.info_write(qPrintable(s.value("figureDescription").toString()));
    f.save(qPrintable(this->saveDirectory.absolutePath()), qPrintable(s.value("figureName").toString()));
    this->saved = true;
    this->defaultDirectoryInUse = false;
    this->setWindowTitle(this->saveDirectory.dirName() + " - moebinv-gui");
}


/*!
 * \brief MainWindow::getMetricType get the metric type as represented in moebinv.
 * \param metric integer representic a metric type.
 * \return GiNaC::ex
 */
GiNaC::ex MainWindow::getMetricType(const int &metric) {
    switch (metric) {
        case ELLIPTIC:
            return metric_e;
            break;
        case PARABOLIC:
            return metric_p;
            break;
        case HYPERBOLIC:
            return metric_h;
            break;
        default:
            return ex();
            break;
    }
    return ex();
}


/*!
 * \brief MainWindow::on_actionSave_As_triggered
 *
 * 'Save as' saves the figure by forcing the user to select a location to save to.
 */
void MainWindow::on_actionSave_As_triggered()
{
    this->checkDescription();

    QDir defaultPath = QDir(s.value("defaultSaveDirectory").toString());
    QDir filePath = QDir(saveDialog->getSaveFileName(this, tr("Save Figure"), defaultPath.absolutePath(), tr("*.gar")));

    if (filePath.path() == ".")
        return;

    this->saveDirectory = filePath;
    s.setValue("figureName", filePath.dirName());
    f.set_metric(getMetricType(s.value("pointMetric").toInt()), getMetricType(s.value("cycleMetric").toInt()));
    f.info_write(qPrintable(s.value("figureDescription").toString()));
    f.save(qPrintable(this->saveDirectory.absolutePath()), qPrintable(s.value("figureName").toString()));
    this->saved = true;
    this->defaultDirectoryInUse = false;
    this->setWindowTitle(this->saveDirectory.dirName() + " - moebinv-gui");
}


/*!
 * \brief MainWindow::checkDescription
 *
 * Check that the the user has provided a description for the figure. If they haven't
 * and they want to then they can enter a description to be saved with the figure.
 */
void MainWindow::checkDescription()
{
    // if figure doesn't have a description prompt user for one
    if (s.value("figureDescription").toString() == "" || s.value("figureDescription").toString() == "no description") {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Desctription", "Would you like to add a description to the figure?",
            QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            QString description = QInputDialog::getText(nullptr, "Description", "Enter description:");

            if (description == "")
                description = "no description";

            s.setValue("figureDescription", description);
        }
    }
}


/*!
 * \brief MainWindow::on_actionOpen_triggered
 *
 * Open figure from a '.gar' file. Called when the user selects 'open' from the application menu.
 */
void MainWindow::on_actionOpen_triggered()
{
    MoebInv::figure originalFigure = this->f;

    // check to make sure current file has been saved
    if (!this->saved) {
        if (!this->saveCheck())
            return;
    }

    QDir filePath;
    QDir defaultPath = QDir(s.value("defaultSaveDirectory").toString());

    filePath = QDir(saveDialog->getOpenFileName(this, tr("Open Figure"), defaultPath.absolutePath(), tr("*.gar")));

    if (filePath.path() == ".")
        return;

    QString fileName = filePath.dirName();

    if (!fileName.isEmpty() && !fileName.isNull()) {
        if (s.value("setFloatEvaluation").toBool())
            f = figure(qPrintable(filePath.absolutePath()), qPrintable(fileName)).set_float_eval();
        else
            f = figure(qPrintable(filePath.absolutePath()), qPrintable(fileName));

        this->saveDirectory = filePath;
        s.setValue("figureName", filePath.dirName());
        this->setWindowTitle(fileName + " - moebinv-gui");
        this->saved = true;
        this->defaultDirectoryInUse = false;

        // get figure metric
        s.setValue("pointMetric", ex_to<numeric>(ex_to<clifford>(f.get_point_metric()).get_metric(idx(0,2),idx(0,2))
          *ex_to<clifford>(f.get_point_metric()).get_metric(idx(1,2),idx(1,2)).eval()).to_int());

        s.setValue("cycleMetric", ex_to<numeric>(ex_to<clifford>(f.get_cycle_metric()).get_metric(idx(0,2),idx(0,2))
          *ex_to<clifford>(f.get_cycle_metric()).get_metric(idx(1,2),idx(1,2)).eval()).to_int());

        // get figure description
        s.setValue("figureDescription", QString::fromStdString(f.info_read()));

        // gen first symbol
        lblGen->advanceLabel();
        nextSymbol = lblGen->genNextSymbol(this->nextSymbol);

        // Now update the scene
        changesMadeToFigure(originalFigure, this->f);
        initialiseDefaultSettings();
        update();
    }
}


/*!
 * \brief MainWindow::saveCheck
 * \return bool
 *
 * Check with the user whether they would like to save the figure if it us unsaved.
 * Returns true if the user wants to save and false if not.
 */
bool MainWindow::saveCheck()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Test", "The current figure is not saved. Are you sure you would like to continue?",
        QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        return true;
    }

    return false;
}


/*!
 * \brief MainWindow::on_actionNew_triggered
 *
 * Create a new empty figure. Called when the user selects 'new' from the
 * application menu.
 */
void MainWindow::on_actionNew_triggered()
{
    MoebInv::figure originalFigure = this->f;

    if (!this->saved) {
        if (!this->saveCheck())
            return;
    } else {
        if (QMessageBox::No == QMessageBox(QMessageBox::Warning, "title",
            "Are you sure you would like to create a new figure?", QMessageBox::Yes|QMessageBox::No).exec())

            return;
    }

    this->defaultDirectoryInUse = true;
    this->f = figure();
    this->lblGen = new labels(&this->f);
    this->nextSymbol = lblGen->genNextSymbol(this->nextSymbol);

    changesMadeToFigure(originalFigure, this->f);
    initialiseDefaultSettings();

    // reset default figure settings
    s.setValue("pointMetric", ELLIPTIC);
    s.setValue("cycleMetric", ELLIPTIC);
    s.setValue("figureDescription", "no description");

    update();
}


/*!
 * \brief MainWindow::onCustomContextMenu
 * \param point Point at which the right click occured.
 *
 * Displays the context menu for the relevent cycle in the tree view
 * when right mouse button is clicked on.
 */
void MainWindow::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = ui->treeView->indexAt(point);
    QStandardItem *item = model->itemFromIndex(index);

    if (item == nullptr)
        return;

    // standard case for cycles being drawn graphically
    if (item->parent() && item->parent()->hasChildren()) {
        QString itemText = item->parent()->child(item->row())->text();

        if (cyclesMap.contains(itemText)) {
            cycleContextMenu *cMenu = cyclesMap[itemText]->getContextMenu();
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
 * \brief MainWindow::treeViewClicked Called when the tree view is clicked.
 * Highlights a cycle on the scene when its counterpart is clicked on the tree view.
 *
 * \param index index that was clicked in the tree view.
 */
void MainWindow::treeViewClicked(const QModelIndex &index)
{
    QStandardItem *item = model->itemFromIndex(index);

    // make sure the place clicked on the tree view is an item.
    if (item == nullptr)
        return;

    if (!item->parent() || !item->parent()->hasChildren())
        return;

    // get the cycle linked to the item and set its hover.
    QString itemText = item->parent()->child(item->row())->text();
    QPointer<graphicCycle> cycleClicked = cyclesMap[itemText];
    scene->unHighlightCycle();
    cycleClicked->setHover();
}



/*!
 * \brief MainWindow::on_actionLabels_toggled
 * \param labels
 *
 * Set labels as showing or hidden. If labels are hidden then they are not
 * displayed in the graphical view.
 */
void MainWindow::on_actionLabels_toggled(bool labels)
{
    if (labels)
        s.setValue("showLabels", true);
    else
        s.setValue("showLabels", false);

    update();
}


/*!
 * \brief MainWindow::shortestDistance find the shortest distance to a cycle.
 * \param point point at which to check the distance from
 * \param dis distance threshhold
 * \return GiNaC::ex
 *
 * This function takes a point and finds the shortest distance to a cycle given
 * that cycle being within a certain distance.
 */
ex MainWindow::shortestDistance(QPointF point, double dis)
{
    const ex x = point.x();
    const ex y = point.y();
    const ex K = f.get_all_keys(REAL_LINE_GEN);
    const ex E = f;
    double current_dis;
    double increment=(0.5 * dis);
    ex P = lst{ex(x),ex(y)};
    ex selected_key;

    // iterator over all keys
    for (lst::const_iterator itk =ex_to<lst>(K).begin(); itk != ex_to<lst>(K).end(); ++itk) {
        ex L=ex_to<figure>(E).get_cycles(*itk);

        // This is a ginac list thus we need iteration through its components
        for (lst::const_iterator it =ex_to<lst>(L).begin(); it != ex_to<lst>(L).end(); ++it) {
            cycle2D C=ex_to<cycle2D>(*it);

            //try to get circle coordinates
            try {
                double radius2=ex_to<numeric>(C.radius_sq().evalf()).to_double();

                if (ex_to<numeric>(abs(C.get_k().evalf())).to_double() < EPSILON) {
                    if (radius2 < EPSILON)
                        break; // Skipping the infinity
                    // To make a point on a line selectable we disadvantage lines by adding 1
                    current_dis = ex_to<numeric>(abs(C.normalize_det().val(P)).evalf()).to_double()/2.0+increment;
                } else {
                    current_dis = abs(std::sqrt(ex_to<numeric>(C.normalize().val(P).evalf()).to_double()+radius2)-std::sqrt(radius2));
                    // To make a point on a circle selectable we disadvantage real circles
                    if (radius2  > EPSILON)
                        current_dis+=increment;
                }
                if (current_dis < dis) {
                    dis = current_dis;
                    selected_key = *itk;
                }
            } catch (...) {
                qDebug() << "Too many or too little conditions are specified";
            }
        }
    }
    // Returns the key for closest cycle and the distance
    // if there is no a cycle closer than dis, then zero is returned as the key
    return selected_key;
}


/*!
 * \brief MainWindow::resizeEvent triggered when the window resizes.
 * \param event
 *
 * Triggered when the window resizes and used to keep dock in proportion to
 * the rest of the window when expanding.
 */
void MainWindow::resizeEvent(QResizeEvent *event)
{
    // keep initial event and extend
    QMainWindow::resizeEvent(event);

    // calculate new dock size
    int newDockSize = ui->dockWidgetRight->getSizeRatio() * this->width();
    resizeDocks({ui->dockWidgetRight}, {newDockSize}, Qt::Horizontal);
    ui->graphicsView->recenterView();
}


/*!
 * \brief MainWindow::onCalculateDockRatio
 *
 * Calculates the percentage ratio of the dock compared to the rest of the window.
 */
void MainWindow::onCalculateDockRatio()
{
    double sizeRatio = ui->dockWidgetRight->width() / (double)this->width();
    ui->dockWidgetRight->setSizeRatio(sizeRatio);
}


/*!
 * \brief MainWindow::highlightClosestCycle highlight the clostest cycle to the mouse.
 * \param point current mouse position
 *
 * finds the clostest cycle to the mouse and highlights it based on the
 * hover colour set in the settings.
 */
void MainWindow::highlightClosestCycle(QPointF point)
{
    double highlightDistance = s.value("highlightDistance").toDouble();

    // unhighlight all previously highlighted cycles
    this->unHighlightCycle();

    GiNaC::ex closest = shortestDistance(point, highlightDistance);
    QPointer<graphicCycle> cycle = cyclesMap.value(node_label(closest));

    if (!cycle.isNull()) {
        cycle->setHover();
        scene->setPointIsHighlighted(true);
        ui->graphicsView->setCurrentHighlightedCycle(cycle);
    } else {
        scene->setPointIsHighlighted(false);
    }

    this->prevHoveredCycle = cycle;
}


/*!
 * \brief MainWindow::unHighlightCycle
 *
 * Loop through all cycles and dissable their hovers. This makes them go back to
 * their base colour, which was set before applying the hover.
 */
void MainWindow::unHighlightCycle() {
    for (auto cycle : cyclesMap) {
        cycle->unsetHover();
    }
}


/*!
 * \brief MainWindow::buildRelationStatus
 *
 * Create the relation list displayed in the bottom right corner.
 * Adds the currently selected relations to the list.
 */
void MainWindow::buildRelationStatus()
{
    QString relationString;
    relationString = "Current selected relations: [";

    if (relationList.nops() == 0) {
        relationString += "]";
        statusRelations->setText(relationString);
        return;
    }

    if (relationList.nops() != 1) {
        for (int x = 0; x < relationList.nops() - 1; x++) {
            try {
                cycle_relation cycleRelation = ex_to<cycle_relation>(relationList.op(x).op(2));
                relationString += node_label(cycleRelation);
                relationString += ", ";

            } catch (...) {
                // catch invalid relation in relationList and move onto the next item
                continue;
            }
        }
    }

    // add final item in list
    relationString += node_label(relationList.op(relationList.nops() - 1).op(2));

    relationString += "]";
    statusRelations->setText(relationString);
}


/*!
 * \brief MainWindow::on_actionzoomIn_triggered
 *
 * When zoom in buttom is pressed, zoom the view in.
 */
void MainWindow::on_actionzoomIn_triggered()
{
    ui->graphicsView->zoomIn();
}


/*!
 * \brief MainWindow::on_actionzoomOut_triggered
 *
 * When the zoom out button is pressed, zoom the view out.
 */
void MainWindow::on_actionzoomOut_triggered()
{
    ui->graphicsView->zoomOut();
}


/*!
 * \brief MainWindow::getCycleData get the cycles appearance data.
 * \param cycle cycle to get data from
 * \return struct cycleStyleData
 *
 * Get the cycle data stored as ASY. This function splits a string into 3 different
 * components: colour, style and width.
 */
struct cycleStyleData MainWindow::getCycleData(const ex &cycle)
{
    QString style;
    QStringList styleList;
    QString colour, lineWidth, lineStyle;
    struct cycleStyleData data;

    style = QString::fromStdString(f.get_asy_style(cycle));

    // construct regular expressions to identify each element
    QRegularExpression rgbRegex("^rgb\\((0|0\\.\\d+|1|1\\.0*|\\.\\d+),\\s*(0|0\\.\\d+|1|1\\.0*|\\.\\d+),\\s*(0|0\\.\\d+|1|1\\.0*|\\.\\d+)\\)$",
        QRegularExpression::CaseInsensitiveOption);
    QRegularExpression lineStyleRegex("^(solid|dotted|dashed)$",
        QRegularExpression::CaseInsensitiveOption);
    QRegularExpression lineWidthRegex("^(\\d+\\.?\\d*pt)$",
        QRegularExpression::CaseInsensitiveOption);

    styleList = style.split("+");

    // assign strings
    for (auto item : styleList) {
        if (rgbRegex.match(item).hasMatch())
            colour = item;
        else if (lineStyleRegex.match(item).hasMatch())
            lineStyle = item;
        else if (lineWidthRegex.match(item).hasMatch())
            lineWidth = item;
    }

    // check to make sure that each element string has been assigned
    if (colour.isNull() || colour.isEmpty() ||
        lineWidth.isNull() || lineWidth.isEmpty() ||
        lineStyle.isNull() || lineStyle.isEmpty()) {

        // set defaults
        data.colour = s.value("defaultGraphicsColour").value<QColor>();
        data.lineStyle = s.value("defaultLineStyle").toInt();
        data.lineWidth = s.value("defaultLineWidth").toDouble();

        return data;
    }

    // assign line style to data
    if (lineStyle == "solid")
        data.lineStyle = SOLID;
    else if (lineStyle == "dotted")
        data.lineStyle = DOTTED;
    else if (lineStyle == "dashed")
        data.lineStyle = DASHED;

    // assign line width to data
    lineWidth.chop(2);
    data.lineWidth = lineWidth.toDouble();

    // assign colour to data
    colour.chop(1);
    colour.remove(0, 4);
    QStringList rgbList = colour.split(",");
    data.colour = QColor(rgbList[0].toDouble() * 255, rgbList[1].toDouble() * 255, rgbList[2].toDouble() * 255);
    return data;
}


/*!
 * \brief MainWindow::setCycleAsy sets the cycles appearance.
 * \param new_cycle cycle the data is going to be set on.
 * \param data the data the cycle will be set with.
 * \return bool
 *
 * sets the cycles appearance given a cycleStyleData struct containing colour, style and width.
 */
bool MainWindow::setCycleAsy(const ex &new_cycle, const struct cycleStyleData &data)
{
    QString asyString;
    QString red, green, blue;
    QString lineWidth;
    QString lineStyle;

    red = QString::number(data.colour.red() / 255.0);
    green = QString::number(data.colour.green() / 255.0);
    blue = QString::number(data.colour.blue() / 255.0);
    lineWidth = QString::number(data.lineWidth) + "pt";

    switch (data.lineStyle) {
        case SOLID:
            lineStyle = "solid";
            break;
        case DOTTED:
            lineStyle = "dotted";
            break;
        case DASHED:
            lineStyle = "dashed";
            break;
    }

    asyString = "rgb(" + red + "," + green + "," + blue + ")" + "+" +
                lineStyle + "+" +
                lineWidth;

    try {
        f.set_asy_style(new_cycle, qPrintable(asyString));
    } catch (...) {
        return false;
    }

    return true;
}


/*!
 * \brief MainWindow::on_actionDebug_bounding_rect_triggered
 * \param checked
 *
 * show the bounding rectangles of all the elements on the scene.
 * This is used to debug items in the graphics view.
 */
void MainWindow::on_actionDebug_bounding_rect_triggered(bool checked)
{
    if (checked) {
        s.setValue("debugBoundingRect", true);
    } else {
        s.setValue("debugBoundingRect", false);
    }

    update();
}


/*!
 * \brief MainWindow::buildToolBar
 *
 * build the main tool bar adding elements: create cycle, define cycle, zoom in, zoom out, pan, 'this'.
 */
void MainWindow::buildToolBar()
{
    QToolBar *tb = this->ui->mainToolBar;

    tb->addAction(ui->actionCreate_Cycle);
    tb->addAction(ui->actionDefine_cycle);

    tb->addSeparator();

    tb->addAction(ui->actionzoomIn);
    tb->addAction(ui->actionzoomOut);
    tb->addAction(ui->actionPan);

    tb->addSeparator();

    this->thisItem = new QToolButton();
    this->thisItem->setText("This");
    this->thisItem->setPopupMode(QToolButton::InstantPopup);
    this->thisItem->setMenu(menus[2]);
    tb->addWidget(this->thisItem);
}


/*!
 * \brief MainWindow::on_actionDefine_by_center_and_radius_squared_triggered
 *
 * define a cycle given the center and radius squared.
 */
void MainWindow::on_actionDefine_by_center_and_radius_squared_triggered()
{
    this->on_actionDefine_cycle_triggered(1);
}


/*!
 * \brief MainWindow::on_actionDefine_by_values_triggered
 *
 * define a cycle given the values k,l,n,m.
 */
void MainWindow::on_actionDefine_by_values_triggered()
{
    this->on_actionDefine_cycle_triggered(0);
}


/*!
 * \brief MainWindow::on_actionDefine_cycle_triggered
 * \param pageIndex
 *
 * define a cycle to be added to the scene. This is useful when the cycle must have
 * an exact location which would be difficult to create by hand on the scene.
 */
void MainWindow::on_actionDefine_cycle_triggered(int pageIndex)
{
    defineCycleDialog *defCycleDialog = new defineCycleDialog(this);
    defCycleDialog->setTab(pageIndex);

    if (defCycleDialog->exec() == QDialog::Accepted) {
        GiNaC::lst inputList = defCycleDialog->getValues();
        this->createCycle(inputList);
    }

    delete defCycleDialog;
}


/*!
 * \brief MainWindow::on_actionCreate_Cycle_triggered
 *
 * Triggered when the create cycle button is presssed. Checks that there is actually
 * a cycle to add to the scene, then adds it.
 */
void MainWindow::on_actionCreate_Cycle_triggered()
{
    ex cycle;

    // make sure that the list isn't empty before adding cycle
    if (relationList.nops() <= 0) {
        msgBox->warning(0, "No cycles in relation", "For a cycle to be created there must be cycles in the relation.");
        return;
    }

    createCycle();
}


/*!
 * \brief MainWindow::createCycle
 * \param inputList
 *
 * Creates a cycle to add to the figure. The cycle generated is based upon
 * the number of inputs to the list. If the list is empty then a new cycle
 * is created based on the relations that have been selected.
 */
void MainWindow::createCycle(lst inputList)
{
    MoebInv::figure originalFigure = this->f;
    ex cycle;

    nextSymbol = lblGen->genNextSymbol(this->nextSymbol, true);

    // add cycle by referencing relation list
    if (inputList.nops() == 0) {
        lst unpackedRelationList;

        try {
            //unpack relation list
            for (auto item : relationList) {
                // if relation is from unnamed cycle
                if (item.op(0).is_equal(lblGen->unnamedSymbol))
                    unpackedRelationList.append(refactorCycleRelation(item, nextSymbol));
                else
                    unpackedRelationList.append(item.op(2));
            }
            cycle = f.add_cycle_rel(unpackedRelationList, nextSymbol);
        } catch (...) {
            msgBox->warning(0, "Cycle relation(s) invalid", "The cycle couldn't be created. Double check your relations and try again");
            return;
        }
    } else if (inputList.nops() == 3) {
        try {
            cycle = f.add_cycle(cycle2D(lst{inputList.op(0),inputList.op(1)},f.get_point_metric(),inputList.op(2)), nextSymbol);
        } catch (...) {
            msgBox->warning(0, "Cycle relation(s) invalid", "The cycle couldn't be created. Double check your relations and try again");
            return;
        }
    } else if (inputList.nops() == 4) {
        try {
            cycle = f.add_cycle(cycle2D(inputList.op(0),lst{inputList.op(1),inputList.op(2)},inputList.op(3),f.get_point_metric()),nextSymbol);
        } catch (...) {
            msgBox->warning(0, "Cycle relation(s) invalid", "The cycle couldn't be created. Double check your relations and try again");
            return;
        }
    }

    // add default styling to the cycle
    struct cycleStyleData cycleData;
    cycleData.colour = s.value("defaultGraphicsColour").value<QColor>();
    cycleData.lineStyle = s.value("defaultLineStyle").toDouble();
    cycleData.lineWidth = s.value("defaultLineWidth").toDouble();
    cycleData.isDefault = true;
    setCycleAsy(cycle, cycleData);

    // creating cycle success
    lblGen->advanceLabel();
    nextSymbol = lblGen->genNextSymbol(this->nextSymbol);
    changesMadeToFigure(originalFigure, this->f);
    update();

    emit resetRelationalList();
    relationList.remove_all();
}


/*!
 * \brief MainWindow::refactorCycleRelation refactor a relation.
 * \param relationItem the relation to be changed.
 * \param newSymbol the new cycle symbol to replace the old one.
 * \return cycle_relation
 *
 * This function allows you to change the symbol a cycle_relation relation uses.
 * This means the cycle can be changed after the original relation has been created.
 */
cycle_relation MainWindow::refactorCycleRelation(const ex &relationItem, const ex &newSymbol)
{
    ex cycleSymbol = newSymbol;
    GiNaC::ex relationType = relationItem.op(1);
    GiNaC::ex parameters = relationItem.op(3);
    cycle_relation relation;

    switch (ex_to<numeric>(relationType).to_int()) {
        case ORTHOGONAL:
            relation = is_orthogonal(cycleSymbol, true);
            break;
        case FORTHOGONAL:
            relation = is_f_orthogonal(cycleSymbol, true);
            break;
        case DIFFERENT:
            relation = is_different(cycleSymbol, true);
            break;
        case ADIFFERENT:
            relation = is_adifferent(cycleSymbol, true);
            break;
        case REALS:
            relation = only_reals(cycleSymbol, true);
            break;
        case TANGENT:
            relation = is_tangent(cycleSymbol, true);
            break;
        case TANGENT_I:
            relation = is_tangent_i(cycleSymbol, true);
            break;
        case TANGENT_O:
            relation = is_tangent_o(cycleSymbol, true);
            break;
        case STEINER_POWER:
            relation = cycle_power(cycleSymbol, true, parameters.op(0));
            break;
        case CYCLE_ANGLE:
            relation = make_angle(cycleSymbol, true, parameters.op(0));
            break;
        case CYCLE_CROSS_T_DISTANCE:
            relation = cross_t_distance(cycleSymbol, true, parameters.op(0));
            break;
        case PRODUCT_SIGN:
            relation = product_nonpositive(cycleSymbol, true, parameters.op(0));
            break;
        case CYCLE_MOBIUS:
            relation = moebius_transform(cycleSymbol, true, parameters);
            break;
        case CYCLE_SL2:
            relation = sl2_transform(cycleSymbol, true, parameters);
            break;
    }

    return relation;
}


/*!
 * \brief MainWindow::on_actionFigure_Description_triggered
 *
 * Display the current figure description in a message box.
 * If there is no description set then the message box will display
 * how to set a description.
 */
void MainWindow::on_actionFigure_Description_triggered()
{
    if (s.value("figureDescription").toString() != "" && s.value("figureDescription").toString() != "no description") {
        msgBox->setText("Figure description");
        msgBox->setInformativeText(s.value("figureDescription").toString());
        msgBox->exec();
    } else {
        msgBox->information(nullptr, "Figure description", "There is no description to display. Please set one by going to edit > properties.");
    }
}


/*!
 * \brief MainWindow::on_actionQuit_triggered
 *
 * Quit the application. Makes sure that the figure has been saved first.
 */
void MainWindow::on_actionQuit_triggered()
{
    // check to make sure current file has been saved
    if (!this->saved) {
        if (!this->saveCheck())
            return;
    }

    QApplication::quit();
}


/*!
 * \brief MainWindow::on_actionDelete_cycle_triggered
 *
 * Delete a cycle by providing a the name of its label.
 * If the label cannot be found an error message will be output.
 */
void MainWindow::on_actionDelete_cycle_triggered()
{
    QString inputCycleLabel = QInputDialog::getText(nullptr, "Delete cycle", "Cycle:");
    MoebInv::figure originalFigure = this->f;

    try {
        f.remove_cycle_node(f.get_cycle_key(qPrintable(inputCycleLabel)));
    } catch (...) {
        msgBox->warning(0, "Cycle label not found", "Cycle label not found - are you sure you entered it correctly?");
        return;
    }

    // success
    changesMadeToFigure(originalFigure, this->f);
    update();
}


/*!
 * \brief MainWindow::changesMadeToFigure
 * \param originalFigure the figure before changes were made.
 * \param changedFigure the figure after changes were made.
 *
 * Called when there are changes that have been made to a figure. The first part of this
 * function ensures the title of the main window displays whether the current figure has
 * been saved of not. The second part of the function adds the change to the undo stack.
 */
void MainWindow::changesMadeToFigure(const MoebInv::figure &originalFigure, const MoebInv::figure &changedFigure)
{
    QDir defaultPath = QDir(s.value("defaultSaveDirectory").toString());

    if (this->defaultDirectoryInUse)
        this->setWindowTitle("unnamed-figure* - moebinv-gui");
    else
        this->setWindowTitle(this->saveDirectory.dirName() + "* - moebinv-gui");

    this->saved = false;

    //push current figure onto the undo stack
    if (this->undoStack->count() == 0)
        this->undoStack->setUndoLimit(s.value("undoLimit").toInt());

    figureUndoCommand *command = new figureUndoCommand(originalFigure, changedFigure);
    this->undoStack->push(command);
    connect(command, &figureUndoCommand::sceneInvalid, this, &MainWindow::replaceFigure);
}


/*!
 * \brief MainWindow::saveDirectoryHasChanged
 *
 * Called when the save directory needs updating. The save directory can be changed in the
 * GUI through the settings dialog.
 */
void MainWindow::saveDirectoryHasChanged()
{
    this->saveDirectory = QDir(s.value("defaultSaveDirectory").toString());
}


/*!
 * \brief MainWindow::replaceFigure
 * \param replacementFigure
 *
 * replace the figure with another figure. Used by the undo stack.
 */
void MainWindow::replaceFigure(const MoebInv::figure &replacementFigure)
{
    this->f = replacementFigure;
    update();
}


/*!
 * \brief MainWindow::keyPressEvent
 * \param event
 *
 * Detects a key press event.
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // emit a signal when the escape key is pressed.
    if (event->key() == Qt::Key_Escape) {
        emit escPressed();
    }
}


/*!
 * \brief MainWindow::initialiseDefaultSettings
 *
 * Initialse any default settings by obtaining the information from
 * values stored in settings.
 */
void MainWindow::initialiseDefaultSettings()
{
    // update ui items
    ui->actionLabels->setChecked(true);

    if (s.value("floatEvaluation").toBool())
        ui->actionFloating->setChecked(true);

    QMenu *pointMenu = new QMenu();
    QActionGroup *pointGroup = new QActionGroup(pointMenu);

    QMenu *cycleMenu = new QMenu();
    QActionGroup *cycleGroup = new QActionGroup(cycleMenu);

    QMenu *evalTypeMenu = new QMenu();
    QActionGroup *evalTypeGroup = new QActionGroup(evalTypeMenu);

    ui->actionPointMetric->setMenu(pointMenu);
    ui->actionCycleMetric->setMenu(cycleMenu);
    ui->actionEvaluationType->setMenu(evalTypeMenu);

    pointGroup->addAction(ui->actionEllipticPointMetric);
    pointGroup->addAction(ui->actionParabolicPointMetric);
    pointGroup->addAction(ui->actionHyperbolicPointMetric);
    pointMenu->addActions(pointGroup->actions());

    cycleGroup->addAction(ui->actionEllipticCycleMetric);
    cycleGroup->addAction(ui->actionParabolicCycleMetric);
    cycleGroup->addAction(ui->actionHyperbolicCycleMetric);
    cycleMenu->addActions(cycleGroup->actions());

    evalTypeGroup->addAction(ui->actionFloating);
    evalTypeGroup->addAction(ui->actionExact);
    evalTypeMenu->addActions(evalTypeGroup->actions());

    switch (s.value("evaluationType").toInt()) {
        case EXACT:
            f.set_exact_eval();
            break;
        case FLOATING:
            f.set_float_eval();
            break;
    }

    // set scene background colour
    ui->graphicsView->setBackgroundBrush(QBrush(s.value("backgroundColour").value<QColor>(), Qt::SolidPattern));
}


/*!
 * \brief MainWindow::on_actionEllipticPointMetric_triggered
 *
 * Triggered when the elliptic point metric is clicked.
 */
void MainWindow::on_actionEllipticPointMetric_triggered()
{
    s.setValue("pointMetric", ELLIPTIC);
    changeMetric();
    ui->graphicsView->viewport()->update();
}


/*!
 * \brief MainWindow::on_actionParabolicPointMetric_triggered
 *
 * Triggered when the parabolic point metric is clicked.
 */
void MainWindow::on_actionParabolicPointMetric_triggered()
{
    s.setValue("pointMetric", PARABOLIC);
    changeMetric();
    ui->graphicsView->viewport()->update();
}


/*!
 * \brief MainWindow::on_actionHyperbolicPointMetric_triggered
 *
 * Triggered when the hyperbolic point metric is clicked.
 */
void MainWindow::on_actionHyperbolicPointMetric_triggered()
{
    s.setValue("pointMetric", HYPERBOLIC);
    changeMetric();
    ui->graphicsView->viewport()->update();
}


/*!
 * \brief MainWindow::on_actionEllipticCycleMetric_triggered
 *
 * Triggered when the elliptic cycle metric is clicked.
 */
void MainWindow::on_actionEllipticCycleMetric_triggered()
{
    s.setValue("cycleMetric", ELLIPTIC);
    changeMetric();
    ui->graphicsView->viewport()->update();
}


/*!
 * \brief MainWindow::on_actionParabolicCycleMetric_triggered
 *
 * Triggered when the parabolic cycle metric is clicked.
 */
void MainWindow::on_actionParabolicCycleMetric_triggered()
{
    s.setValue("cycleMetric", PARABOLIC);
    changeMetric();
    ui->graphicsView->viewport()->update();
}


/*!
 * \brief MainWindow::on_actionHyperbolicCycleMetric_triggered
 *
 * Triggered when the hyperbolic cycle metric is clicked.
 */
void MainWindow::on_actionHyperbolicCycleMetric_triggered()
{
    s.setValue("cycleMetric", HYPERBOLIC);
    changeMetric();
    ui->graphicsView->viewport()->update();
}


/*!
 * \brief MainWindow::on_actionPointMetric_hovered
 *
 * Triggered before the point metric menu is opened. This allows the
 * correct option in the menu to be displayed.
 */
void MainWindow::on_actionPointMetric_hovered()
{
    switch(s.value("pointMetric").toInt()) {
        case ELLIPTIC:
            ui->actionEllipticPointMetric->setChecked(true);
            break;
        case PARABOLIC:
            ui->actionParabolicPointMetric->setChecked(true);
            break;
        case HYPERBOLIC:
            ui->actionHyperbolicPointMetric->setChecked(true);
            break;
    }
}


/*!
 * \brief MainWindow::on_actionCycleMetric_hovered
 *
 * Triggered before the cycle metric menu is opened. This allows the
 * correct option in the menu to be displayed.
 */
void MainWindow::on_actionCycleMetric_hovered()
{
    switch(s.value("cycleMetric").toInt()) {
        case ELLIPTIC:
            ui->actionEllipticCycleMetric->setChecked(true);
            break;
        case PARABOLIC:
            ui->actionParabolicCycleMetric->setChecked(true);
            break;
        case HYPERBOLIC:
            ui->actionHyperbolicCycleMetric->setChecked(true);
            break;
    }
}


/*!
 * \brief MainWindow::on_actionEvaluationType_hovered
 *
 * Triggered before the evaluation type menu is opened. This allows the
 * correct option in the menu to be displayed.
 */
void MainWindow::on_actionEvaluationType_hovered()
{
    switch (s.value("evaluationType").toInt()) {
        case EXACT:
            ui->actionExact->setChecked(true);
            break;
        case FLOATING:
            ui->actionFloating->setChecked(true);
            break;
    }
}


/*!
 * \brief MainWindow::on_actionFloating_triggered
 *
 * When triggered, set the evaluation type to floating.
 */
void MainWindow::on_actionFloating_triggered()
{
    s.setValue("evaluationType", FLOATING);
}


/*!
 * \brief MainWindow::on_actionExact_triggered
 *
 * When triggered, set the evaluation type to exact.
 */
void MainWindow::on_actionExact_triggered()
{
    s.setValue("evaluationType", EXACT);
}


/*!
 * \brief MainWindow::changeMetric
 *
 * Set the metric on the figure once it has been changed in properties
 * or the menu line.
 */
void MainWindow::changeMetric()
{
    f.set_metric(getMetricType(s.value("pointMetric").toInt()), getMetricType(s.value("cycleMetric").toInt()));
    update();
}


// REMOVE...
QString MainWindow::node_compact_string(GiNaC::ex name)
{
    std::ostringstream drawing;
    drawing << std::setprecision(s.value("floatPrecision").toInt());
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
