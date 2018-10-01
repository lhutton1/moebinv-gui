#include "definecycledialog.h"
#include "ui_definecycledialog.h"

defineCycleDialog::defineCycleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::defineCycleDialog)
{   
    QDoubleValidator *doubleValidate = new QDoubleValidator(-10000, 10000, 2, this);

    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Create");

    // build list of all line edit widgets
    this->lineEditList = QList<QLineEdit *>();
    this->lineEditList.append(ui->lineEdit_1);
    this->lineEditList.append(ui->lineEdit_2);
    this->lineEditList.append(ui->lineEdit_3);
    this->lineEditList.append(ui->lineEdit_4);
    this->lineEditList.append(ui->lineEdit_5);
    this->lineEditList.append(ui->lineEdit_6);
    this->lineEditList.append(ui->lineEdit_7);

    //set validators on all of the line edit widgets
    for (auto lineEdit : this->lineEditList) {
        lineEdit->setValidator(doubleValidate);
    }
}

defineCycleDialog::~defineCycleDialog()
{
    delete ui;
}

void defineCycleDialog::loadValues(const GiNaC::lst &values)
{
    for (int x = 0; x < 7; x++) {
        this->lineEditList[x]->setText(QString(QString::number(GiNaC::ex_to<GiNaC::numeric>(values.op(x)).to_double())));
    }
}

GiNaC::lst defineCycleDialog::getValues()
{
    GiNaC::lst inputList;

    if (ui->tabWidget->currentIndex() == 0) {
        for (int x = 0; x < 4; x++)
            inputList.append(GiNaC::numeric(lineEditList[x]->text().toDouble()));

    } else if (ui->tabWidget->currentIndex() == 1) {
        for (int x = 4; x < 7; x++)
            inputList.append(GiNaC::numeric(lineEditList[x]->text().toDouble()));
    }

    // reset each line edit
    for (auto item : lineEditList)
        item->setText("");

    return inputList;
}

void defineCycleDialog::setTab(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}
