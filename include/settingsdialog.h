#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsDialog(QWidget *parent = 0);
    ~settingsDialog();

private slots:
    void getColourSelection();

private:
    Ui::settingsDialog *ui;

    QColorDialog *colourDialog;

    QList<QPushButton *> colourSelectionButtons;
};

#endif // SETTINGSDIALOG_H
