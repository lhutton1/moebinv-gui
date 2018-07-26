#include "scene.h"
#include "zoom.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initialize new scene
    sc = new scene();
    zoom* z = new zoom(ui->graphicsView);
    z->set_modifiers(Qt::NoModifier);
    ui->graphicsView->setScene(sc->get());
    ui->graphicsView->show();
}


/*!
 * \brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief MainWindow::on_actionMove_Graphics_View_triggered
 */
void MainWindow::on_actionMove_Graphics_View_triggered(bool checked)
{
    if (checked)
        ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    else
        ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
}
