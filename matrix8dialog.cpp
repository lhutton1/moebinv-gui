#include "matrix8dialog.h"
#include "ui_matrix8dialog.h"

matrix8dialog::matrix8dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matrix8dialog)
{
    QDoubleValidator *doubleValidate = new QDoubleValidator(-10000, 10000, 2, this);

    ui->setupUi(this);

    // build list of all line edit widgets
    this->lineEditList = QList<QLineEdit *>();
    this->lineEditList.append(ui->lineEdit_value1);
    this->lineEditList.append(ui->lineEdit_value2);
    this->lineEditList.append(ui->lineEdit_value3);
    this->lineEditList.append(ui->lineEdit_value4);
    this->lineEditList.append(ui->lineEdit_value5);
    this->lineEditList.append(ui->lineEdit_value6);
    this->lineEditList.append(ui->lineEdit_value7);
    this->lineEditList.append(ui->lineEdit_value8);

    //set validators on all of the line edit widgets
    for (auto lineEdit : this->lineEditList) {
        lineEdit->setValidator(doubleValidate);
    }
}

matrix8dialog::~matrix8dialog()
{
    delete ui;
}

void matrix8dialog::getValues(GiNaC::lst *inputList)
{
    for (auto lineEdit : this->lineEditList) {
        if (lineEdit->text().isEmpty())
            inputList->append(0);
        else
            inputList->append(lineEdit->text().toDouble());
    }
}
