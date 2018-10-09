#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>
#include <QSettings>

#include "conf.h"

namespace Ui {
class propertiesDialog;
}

class propertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit propertiesDialog(QWidget *parent = 0);
    void showEvent(QShowEvent *event);
    void update();
    ~propertiesDialog();

private slots:
    void on_figureDescriptionText_textChanged();
    void on_floatButton_clicked(bool checked);
    void on_exactButton_clicked(bool checked);
    void on_ellipticPointButton_clicked(bool checked);
    void on_parabolicPointButton_clicked(bool checked);
    void on_hyperbolicPointButton_clicked(bool checked);
    void on_ellipticCycleButton_clicked(bool checked);
    void on_parabolicCycleButton_clicked(bool checked);
    void on_hyperbolicCycleButton_clicked(bool checked);

signals:
    void metricChanged();

private:
    QSettings s;
    Ui::propertiesDialog *ui;
};

#endif // PROPERTIESDIALOG_H
