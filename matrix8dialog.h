#ifndef MATRIX8DIALOG_H
#define MATRIX8DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleValidator>

#include <figure.h>

namespace Ui {
class matrix8dialog;
}

class matrix8dialog : public QDialog
{
    Q_OBJECT

public:
    explicit matrix8dialog(QWidget *parent = 0);
    void getValues(GiNaC::lst *inputList);
    ~matrix8dialog();

private:
    Ui::matrix8dialog *ui;

    QList<QLineEdit *> lineEditList;

};

#endif // MATRIX8DIALOG_H
