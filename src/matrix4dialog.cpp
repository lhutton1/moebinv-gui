#include <QDebug>
#include "matrix4dialog.h"
#include "ui_matrix4dialog.h"

matrix4dialog::matrix4dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matrix4dialog)
{
    QDoubleValidator *doubleValidate = new QDoubleValidator(-10000, 10000, 2, this);

    // build list of all line edit widgets
    this->lineEditList = QList<QLineEdit *>();
    this->lineEditList.append(ui->lineEdit_value1);
    this->lineEditList.append(ui->lineEdit_value2);
    this->lineEditList.append(ui->lineEdit_value3);
    this->lineEditList.append(ui->lineEdit_value4);

    ui->setupUi(this);

    ui->lineEdit_value1->setValidator(doubleValidate);
    ui->lineEdit_value2->setValidator(doubleValidate);
    ui->lineEdit_value3->setValidator(doubleValidate);
    ui->lineEdit_value4->setValidator(doubleValidate);

    //set validators on all of the line edit widgets
    //for (auto lineEdit : this->lineEditList) {
    //    qDebug() << "item";
    //    lineEdit->setValidator(doubleValidate);
    //}
    //qDebug() << "---";
}

matrix4dialog::~matrix4dialog()
{
    delete ui;
}

void matrix4dialog::getValues(GiNaC::lst *inputList)
{
    for (auto lineEdit : this->lineEditList) {
        if (lineEdit->text().isEmpty())
            inputList->append(0);
        else
            inputList->append(lineEdit->text().toDouble());
    }
}
