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
    void setButtonColour(QPushButton *buttonPushed, QColor colour);
    ~settingsDialog();

private slots:
    void update();

    void on_automaticNaming_clicked(bool checked);
    void on_manualNaming_clicked(bool checked);
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_figureDescriptionText_textChanged();

signals:
    void sceneInvalid();
    void setBackgroundColour(QColor colour);

private:
    QSettings s;
    Ui::settingsDialog *ui;

    QColorDialog *colourDialog;

    QList<QPushButton *> colourSelectionButtons;
};

#endif // SETTINGSDIALOG_H
