#ifndef CSTYLEDIALOG_H
#define CSTYLEDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QSettings>

class graphicCycle;
#include "graphiccycle.h"


namespace Ui {
class cStyleDialog;
}

class cStyleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cStyleDialog(QWidget *parent = nullptr, struct cycleStyleData *cycleData = nullptr);
    void showEvent(QShowEvent *event);
    void setButtonColour(QPushButton *buttonPushed, QColor colour);
    QColor getColour();
    int getStyle();
    double getWeight();
    ~cStyleDialog();

private slots:
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_doubleSpinBox_valueChanged(double arg1);

signals:
    void changeColour(QColor colour);
    void changeStyle(int style);
    void changeWeight(double weight);
    void updateCycleData();

private:
    QSettings s;
    Ui::cStyleDialog *ui;

    QColorDialog *colourDialog;
    QColor colour;
    int style;
    double weight;
    struct cycleStyleData *cycleDataPtr;
};

#endif // CSTYLEDIALOG_H
