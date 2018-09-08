#ifndef MATRIX4DIALOG_H
#define MATRIX4DIALOG_H

#include <QDialog>

namespace Ui {
class matrix4dialog;
}

class matrix4dialog : public QDialog
{
    Q_OBJECT

public:
    explicit matrix4dialog(QWidget *parent = 0);
    ~matrix4dialog();

private:
    Ui::matrix4dialog *ui;
};

#endif // MATRIX4DIALOG_H
