#include <QDebug>
#include "matrix4dialog.h"
#include "ui_matrix4dialog.h"

/*!
 * \brief matrix4dialog::matrix4dialog
 * \param parent
 *
 * Creates a new matrix4dialog. Allows the user to enter 4 double values.
 */
matrix4dialog::matrix4dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matrix4dialog)
{
    QDoubleValidator *doubleValidate = new QDoubleValidator(-10000, 10000, 2, this);

    ui->setupUi(this);

    // build list of all line edit widgets
    this->lineEditList = QList<QLineEdit *>();
    this->lineEditList.append(ui->lineEdit_value1);
    this->lineEditList.append(ui->lineEdit_value2);
    this->lineEditList.append(ui->lineEdit_value3);
    this->lineEditList.append(ui->lineEdit_value4);

    //set validators on all of the line edit widgets
    for (auto lineEdit : this->lineEditList) {
        lineEdit->setValidator(doubleValidate);
    }
}


/*!
 * \brief matrix4dialog::~matrix4dialog
 *
 * Destructor for the matrix4dialog
 */
matrix4dialog::~matrix4dialog()
{
    delete ui;
}


/*!
 * \brief matrix4dialog::getValues
 * \param inputList
 *
 * Gets the values input into the dialog and appends each value to a GiNaC::lst.
 */
void matrix4dialog::getValues(GiNaC::lst *inputList)
{
    for (auto lineEdit : this->lineEditList) {
        if (lineEdit->text().isEmpty())
            inputList->append(0);
        else
            inputList->append(GiNaC::numeric(lineEdit->text().toDouble()));
    }
}
