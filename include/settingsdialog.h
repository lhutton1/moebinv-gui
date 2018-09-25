#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QColorDialog>

#include "conf.h"

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsDialog(QWidget *parent = 0);
    void showEvent(QShowEvent* event);
    ~settingsDialog();

private slots:
    void getColourSelection();
    void update();

private:
    QSettings s;
    Ui::settingsDialog *ui;

    QColorDialog *colourDialog;

    QList<QPushButton *> colourSelectionButtons;
};

#endif // SETTINGSDIALOG_H
