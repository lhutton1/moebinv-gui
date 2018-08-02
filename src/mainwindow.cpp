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
//    QString label = lblGen->genNextLabel();
//    ex cycle = f.add_point(lst{mousePos.x(), mousePos.y()}, qPrintable(label));
//    circle *c = new circle(&f, cycle, label);
//    scene->addItem(c);
    // gen new label
    QString label = lblGen->genNextLabel();

    // add cycle to the figure
    ex cycle = f.add_point(lst{mousePos.x(), mousePos.y()}, qPrintable(label));
    //ex cycle2 = f.add_cycle_rel(lst(is_orthogonal(cycle)), "B");

    // now draw the point
    point *p = new point(&f, cycle, label);

    connect(p, &point::removeFromTree, this, &MainWindow::removeFromTree);
    connect(p, &point::addOrthagonalToList, this, &MainWindow::addOrthagonalToList);
    connect(p, &point::removeOrthagonalFromList, this, &MainWindow::removeOrthagonalFromList);

    scene->addItem(p);
    // now add to tree
    addPointToTree(label);
}

/*!
 * \brief MainWindow::on_actionCreate_Cycle_triggered
 *
 * Function to create cycle based on relations that have been added.
 */
void MainWindow::on_actionCreate_Cycle_triggered()
{
    QString label = lblGen->genNextLabel();
    ex cycle = f.add_cycle_rel(orthagonalList, qPrintable(label));
    circle *c = new circle(&f, cycle, label);
    scene->addItem(c);
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
    ui->treeWidget->addTopLevelItem(item);
}

void MainWindow::removeFromTree(QString label)
{
    //ui->treeWidget->takeTopLevelItem(//needs index);
}

void MainWindow::addOrthagonalToList(GiNaC::ex cycle) {
    orthagonalList.append(is_orthogonal(cycle));
}

void MainWindow::removeOrthagonalFromList(GiNaC::ex cycle) {
    qDebug() << "rm orth";
}
