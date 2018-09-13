#ifndef DEFINECYCLEDIALOG_H
#define DEFINECYCLEDIALOG_H

#include <QDialog>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>

#include <figure.h>

namespace Ui {
class defineCycleDialog;
}

class defineCycleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit defineCycleDialog(QWidget *parent = 0);
    void setTab(int index);
    GiNaC::lst getValues();
    ~defineCycleDialog();

private:
    Ui::defineCycleDialog *ui;

    QList<QLineEdit *> lineEditList;
};

#endif // DEFINECYCLEDIALOG_H
