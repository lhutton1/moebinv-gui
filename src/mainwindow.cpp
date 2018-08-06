#include <string>
#include <iostream>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace GiNaC;
using namespace MoebInv;

//void ex_to_string(const ex & E)
//{
//    std::ostringstream drawing;
//    drawing << E;
//    string dr = drawing.str().c_str();

//    QString drw = QString::fromStdString(dr);
//    qDebug() << drw;
//}


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
    scene->setSceneRect(0,0,ui->graphicsView->frameSize().width(),ui->graphicsView->frameSize().height());

    // set up new event
    connect(scene, &graphicsScene::newMousePress, this, &MainWindow::onMouseScenePress);

    // initialize figure
    initFigure();

    // create new labels object to create unique labels
    lblGen = new labels();

    gen1 = new QTreeWidgetItem();
    gen1->setText(0, "1st Generation");
    ui->treeWidget->addTopLevelItem(gen1);
    gen2 = new QTreeWidgetItem();
    gen2->setText(0, "2nd Generation");
    ui->treeWidget->addTopLevelItem(gen2);
    gen3 = new QTreeWidgetItem();
    gen3->setText(0, "3rd Generation");
    ui->treeWidget->addTopLevelItem(gen3);

    msgBox = new QMessageBox();

    currentTreeIndex = 0;

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
    point *p = new point(&f, cycle, label, currentTreeIndex);

    connect(p, &point::removeFromTree, this, &MainWindow::removeFromTree);
    connect(p, &point::addOrthogonalToList, this, &MainWindow::addOrthogonalToList);
    connect(p, &point::removeOrthogonalFromList, this, &MainWindow::removeOrthogonalFromList);
    connect(this, &MainWindow::resetRelationalList, p, &point::resetRelationalList);

    scene->addItem(p);
    lblGen->advanceLabel();

    // now add to tree
    addPointToTree(label);
    currentTreeIndex++;
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

    //
    // Find better check..................
    //
    //
    // check to make sure cycle is not infinite
    try {
        radius = qSqrt(ex_to<numeric>(c.radius_sq()).to_double());
    }
    catch (...) {
        msgBox->warning(0, "Infinite cycles", "The number of possible cycles for this relation is infinite, therefore it cannot be displayed");
        f.remove_cycle_node(cycle);
        return;
    }

    // check that cycle exists
    if (radius == 0) {
        msgBox->warning(0, "Cycle non-existant", "Cycle for this relation does not exist.");
        f.remove_cycle_node(cycle);
        return;
    }

    // draw the new circle
    circle *circ = new circle(&f, cycle, label);
    scene->addItem(circ);
    lblGen->advanceLabel();
    addPointToTree(label);

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

/*!
 * \brief MainWindow::addPointToTree Add new point to the tree
 * \param itemName point label value.
 */
void MainWindow::addPointToTree(QString itemName)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, itemName);
    gen1->addChild(item);

    if (gen1->childCount() == 1)
        gen1->setExpanded(true);
}

void MainWindow::removeFromTree(QString label, int index)
{
    //ui->treeWidget->removeItemWidget();
    //ui->treeWidget->setRowHidden(index, ui->treeWidget->, true);
}

void MainWindow::addOrthogonalToList(ex cycle) {
    orthogonalList.append(is_orthogonal(cycle));
}

void MainWindow::removeOrthogonalFromList(ex cycle) {
    qDebug() << "rm orth";
}

void MainWindow::resetList(GiNaC::lst *list) {
    list->remove_all();
}
