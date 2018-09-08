#include "matrix4dialog.h"
#include "ui_matrix4dialog.h"

matrix4dialog::matrix4dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matrix4dialog)
{
    ui->setupUi(this);
}

matrix4dialog::~matrix4dialog()
{
    delete ui;
}
