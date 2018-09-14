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

    // fixes qt5.1 bug that causes dock to snap back to original size
    // https://bugreports.qt.io/browse/QTBUG-65592
    this->resizeDocks({ui->dockWidgetRight}, {200}, Qt::Horizontal);

    this->scene = new graphicsScene();
    ui->graphicsView->setScene(scene);

    //status bar
    statusCoordinates = new QLabel();
    statusRelations = new QLabel();
    ui->statusBar->addWidget(statusCoordinates);
    ui->statusBar->addPermanentWidget(statusRelations);

    // set up new event
    connect(scene, &graphicsScene::newMouseLeftPress, this, &MainWindow::addPoint);
    connect(scene, &graphicsScene::newMouseRightPress, this, &MainWindow::onMouseSceneRightPress);
    connect(scene, &graphicsScene::newMouseHover, this, &MainWindow::onMouseSceneHover);
    connect(ui->dockWidgetRight, &dockWidget::recenterView, ui->graphicsView, &view::recenterView);
    connect(ui->dockWidgetRight, &dockWidget::calculateDockToWindowPercentage, this, &MainWindow::onCalculateDockRatio);
    connect(ui->graphicsView, &view::highlightClosestCycle, this, &MainWindow::highlightClosestCycle);
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::onCustomContextMenu);

    // initialize figure
    if (s.value("setFloatEvaluation").toBool())
        f = figure().set_float_eval();
    else
        f = figure();

    menus[0] = new cycleContextMenu(&f, f.get_infinity(), &relationList, false);
    menus[1] = new cycleContextMenu(&f, f.get_real_line(), &relationList, false);
    menus[2] = new cycleContextMenu(&f, nextSymbol, &relationList, false);
    buildToolBar();

    // create new labels object to create unique labels
    lblGen = new labels(&this->f);
    // gen first symbol
    nextSymbol = symbol(qPrintable(lblGen->genNextLabel()));

    // create new msgbox
    msgBox = new QMessageBox();
    saveDialog = new QFileDialog();


    initTreeModel();

    // remove menu from toolbars
    setContextMenuPolicy(Qt::NoContextMenu);

    // whether to add
    isAddPoint = true;

    // update menu items
    ui->actionLabels->setChecked(true);

    update();
}


/*!
 * \brief MainWindow::~MainWindow MainWindow destructor.
 */
MainWindow::~MainWindow()
{
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
 * Create the tree model,
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
}


/*!
 * \brief MainWindow::initMainMenu
 *
 * Create menus for 3 custom relations: infinity, real line and this.
 */
void MainWindow::initMainMenu() {
    menus[0] = new cycleContextMenu(&f, f.get_infinity(), &relationList, false);
    menus[1] = new cycleContextMenu(&f, f.get_real_line(), &relationList, false);
    menus[2] = new cycleContextMenu(&f, nextSymbol, &relationList, false);

    connect(menus[0], &cycleContextMenu::relationsHaveChanged, this, &MainWindow::buildRelationStatus);
    connect(menus[1], &cycleContextMenu::relationsHaveChanged, this, &MainWindow::buildRelationStatus);
    connect(menus[2], &cycleContextMenu::relationsHaveChanged, this, &MainWindow::buildRelationStatus);
    this->thisItem->setMenu(menus[2]);
    connect(menus[2], &QMenu::aboutToShow, this, &MainWindow::thisContextMenuUpdate);
}

void MainWindow::thisContextMenuUpdate()
{
    qDebug() << "running";
    menus[2]->setCycle(nextSymbol);
}

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

void MainWindow::update()
{
    cycleContextMenu *menu;

    // remove data
    scene->clear();
    initTreeModel();
    relationList.remove_all();
    initMainMenu();

    ex keys = f.get_all_keys_sorted(REAL_LINE_GEN);

    // for all items in the figure
    for (lst::const_iterator key =ex_to<lst>(keys).begin(); key != ex_to<lst>(keys).end(); ++key) {
        // get cycle
        ex cycle = *key;

        if (cycle.is_equal(f.get_real_line()))
            menu = menus[1];
        else
            menu = new cycleContextMenu(&f, cycle, &relationList);

        connect(menu, &cycleContextMenu::relationsHaveChanged, this, &MainWindow::buildRelationStatus);
        connect(menu, &cycleContextMenu::sceneInvalid, this, &MainWindow::sceneInvalid);


        struct cycleStyleData d = getCycleData(cycle);

        // add cycles to scene
        graphicCycle *c = new graphicCycle(&f, cycle, &ui->graphicsView->relativeScaleFactor, menu, d);
        connect(c, &graphicCycle::sceneInvalid, this, &MainWindow::sceneInvalid);
        // add to map
        cyclesMap[node_label(cycle)] = QPointer<graphicCycle>(c);

        scene->addItem(c);

        // add cycle to the tree
        addToTree(cycle, d.colour);

        connect(c, &graphicCycle::findCycleInTree, this, &MainWindow::findCycleInTree);

        buildRelationStatus();
    }

    addToTree(f.get_infinity(), Qt::black);
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

        // add cycle to the figure
        ex cycle = f.add_point(lst{x, y}, nextSymbol);

        struct cycleStyleData cycleData;
        cycleData.colour = s.value("defaultGraphicsColour").value<QColor>();
        cycleData.lineStyle = s.value("defaultLineStyle").toDouble();
        cycleData.lineWidth = s.value("defaultLineWidth").toDouble();
        setCycleAsy(cycle, cycleData);

        // generate next symbol
        lblGen->advanceLabel();
        nextSymbol = symbol(qPrintable(lblGen->genNextLabel()));

        // refresh
        update();

    }
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

    if (!fileName.isEmpty() && !fileName.isNull()) {
        if (s.value("setFloatEvaluation").toBool())
            f = figure(qPrintable(fileName)).set_float_eval();
        else
            f = figure(qPrintable(fileName));

        // Now update the scene
        update();
    }

}


/*!
 * \brief MainWindow::on_actionNew_triggered
 *
 * Create a new empty figure. Called when the user selects 'new' from the application menu.
 */
void MainWindow::on_actionNew_triggered()
{
    f = figure();
    lblGen = new labels(&this->f);
    nextSymbol = symbol(qPrintable(lblGen->genNextLabel()));
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

ex MainWindow::shortestDistance(QPointF point, double dis)
{
    const ex x = point.x();
    const ex y = point.y();
    const ex K = f.get_all_keys(REAL_LINE_GEN);
    const ex E = f;
    double current_dis;
    double increment=.5*dis;
    ex P = lst{ex(x),ex(y)};
    ex selected_key;
    double reldis = dis * ui->graphicsView->relativeScaleFactor;

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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // keep initial event and extend
    QMainWindow::resizeEvent(event);

    // calculate new dock size
    int newDockSize = ui->dockWidgetRight->getSizeRatio() * this->width();
    resizeDocks({ui->dockWidgetRight}, {newDockSize}, Qt::Horizontal);
    ui->graphicsView->recenterView();
}

void MainWindow::onCalculateDockRatio()
{
    double sizeRatio = ui->dockWidgetRight->width() / (double)this->width();
    ui->dockWidgetRight->setSizeRatio(sizeRatio);
}

void MainWindow::highlightClosestCycle(QPointF point)
{
    double highlightDistance = s.value("highlightDistance").toDouble();

    if (!prevHoveredCycle.isNull() && !prevHoveredCycle->getItemIsGrabbed())
        prevHoveredCycle->unsetHover();

    GiNaC::ex closest = shortestDistance(point, highlightDistance);
    QPointer<graphicCycle> cycle = cyclesMap.value(node_label(closest));

    if (!cycle.isNull()) {
        cycle->setHover();
        scene->setPointIsHighlighted(true);
    } else {
        scene->setPointIsHighlighted(false);
    }

    prevHoveredCycle = cycle;
}

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

void MainWindow::on_actionzoomIn_triggered()
{
    ui->graphicsView->zoomIn();
}

void MainWindow::on_actionzoomOut_triggered()
{
    ui->graphicsView->zoomOut();
}

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

void MainWindow::on_actionDebug_bounding_rect_triggered(bool checked)
{
    if (checked) {
        s.setValue("debugBoundingRect", true);
    } else {
        s.setValue("debugBoundingRect", false);
    }

    update();
}


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


void MainWindow::on_actionDefine_by_center_and_radius_squared_triggered()
{
    this->on_actionDefine_cycle_triggered(1);
}

void MainWindow::on_actionDefine_by_values_triggered()
{
    this->on_actionDefine_cycle_triggered(0);
}

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
 * Function to create cycle based on relations that have been added.
 */
void MainWindow::on_actionCreate_Cycle_triggered()
{
    ex cycle;

    // make sure that the list isn't empty before adding cycle
    if (relationList.nops() <= 0) {
        msgBox->warning(0, "No cycles in relation", "For a cycle to be created there must be cycles in the relation.");
        return;
    }

    // only real cycles
    //if (s.value("realCycles", true).toBool()) {
    //  relationList.append(only_reals(nextSymbol));
    //}

    createCycle();
}

void MainWindow::createCycle(lst inputList)
{
    ex cycle;

    // add cycle by referencing relation list
    if (inputList.nops() == 0) {
        lst unpackedRelationList;

        try {
            //unpack relation list
            for (auto item : relationList)
                unpackedRelationList.append(item.op(2));
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
    setCycleAsy(cycle, cycleData);

    // creating cycle success
    lblGen->advanceLabel();
    nextSymbol = symbol(qPrintable(lblGen->genNextLabel()));
    update();

    emit resetRelationalList();
    relationList.remove_all();
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

