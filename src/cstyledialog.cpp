#include "cstyledialog.h"
#include "ui_cstyledialog.h"

#include <QDebug>

cStyleDialog::cStyleDialog(QWidget *parent, struct cycleStyleData *cycleData) :
    QDialog(parent),
    ui(new Ui::cStyleDialog)
{
    ui->setupUi(this);
    this->colourDialog = new QColorDialog();

    this->colour = s.value("defaultGraphicsColour").value<QColor>();
    this->style = s.value("defaultLineStyle").toInt();
    this->weight = s.value("defaultLineWidth").toDouble();
    this->cycleDataPtr = cycleData;
}

cStyleDialog::~cStyleDialog()
{
    delete ui;
}

void cStyleDialog::showEvent(QShowEvent *event) {
    emit updateCycleData();

    if (this->cycleDataPtr != nullptr)
        this->colour = this->cycleDataPtr->colour;
        this->style = this->cycleDataPtr->lineStyle;
        this->weight = this->cycleDataPtr->lineWidth;

    setButtonColour(this->ui->pushButton, this->colour);
    this->ui->doubleSpinBox->setValue(this->weight);
    this->ui->comboBox->setCurrentIndex(this->style);
}

QColor cStyleDialog::getColour() {
    return this->colour;
}

int cStyleDialog::getStyle() {
    return this->style;
}

double cStyleDialog::getWeight() {
    return this->weight;
}



void cStyleDialog::on_pushButton_clicked()
{
    QColor colour = colourDialog->getColor();
    setButtonColour(this->ui->pushButton, colour);
    this->colour = colour;
}

void cStyleDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    int style;

    if (arg1 == "Dashed")
        style = DASHED;
    else if (arg1 == "Dotted")
        style = DOTTED;
    else
        style = SOLID;

    this->style = style;

}

void cStyleDialog::on_doubleSpinBox_valueChanged(double arg1)
{
    this->weight = arg1;
}

void cStyleDialog::setButtonColour(QPushButton *buttonPushed, QColor colour)
{
    if(colour.isValid()) {
       QString qss = QString(
               "border: 1px; \
               border-radius: 6px; \
               background-color: " + colour.name());

       buttonPushed->setStyleSheet(qss);
    }
}
