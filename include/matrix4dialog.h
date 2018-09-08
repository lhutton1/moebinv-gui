#ifndef MATRIX4DIALOG_H
#define MATRIX4DIALOG_H

#include <QDialog>
#include <QDoubleValidator>
#include <QLineEdit>

#include <figure.h>

namespace Ui {
class matrix4dialog;
}

class matrix4dialog : public QDialog
{
    Q_OBJECT

public:
    explicit matrix4dialog(QWidget *parent = 0);
    void getValues(GiNaC::lst *inputList);
    ~matrix4dialog();

private:
    Ui::matrix4dialog *ui;

    QList<QLineEdit *> lineEditList;
};

#endif // MATRIX4DIALOG_H
