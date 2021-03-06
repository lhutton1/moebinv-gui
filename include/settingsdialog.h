#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QColorDialog>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDir>
#include <QAbstractButton>

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
    void applySettings();
    void saveSettings();
    void loadValues();
    ~settingsDialog();

private slots:
    void update();

    void on_automaticNaming_clicked(bool checked);
    void on_manualNaming_clicked(bool checked);
    void on_pushButton_pressed();
    void on_pushButton_2_pressed();
    void on_pushButton_3_pressed();
    void on_onlyRealsTrue_clicked(bool checked);
    void on_onlyRealsFalse_clicked(bool checked);
    void on_defaultPathLineEdit_textEdited(const QString &arg1);
    void on_pushButton_4_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_doubleSpinBox_2_valueChanged(double arg1);
    void on_comboBox_currentIndexChanged(int index);
    void on_buttonBox_clicked(QAbstractButton *button);

signals:
    void sceneInvalid();
    void setBackgroundColour(QColor colour);
    void saveDirectoryHasChanged();

private:
    QSettings s;
    Ui::settingsDialog *ui;

    QColorDialog *colourDialog;
    QList<QPushButton *> colourSelectionButtons;
    QMap<QString, QVariant> settingValues;
};

#endif // SETTINGSDIALOG_H
