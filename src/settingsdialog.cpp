#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QDebug>

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);

    colourDialog = new QColorDialog(this);
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::setButtonColour(QPushButton *buttonPushed, QColor colour)
{
    if(colour.isValid()) {
       QString qss = QString(
               "border: 1px; \
               border-radius: 6px; \
               background-color: " + colour.name());

       buttonPushed->setStyleSheet(qss);
    }
}

void settingsDialog::update()
{
    // get current figure description
    ui->figureDescriptionText->setText(s.value("figureDescription").toString());
    ui->figureDescriptionText->moveCursor(QTextCursor::End);

    // get default colours
    setButtonColour(ui->pushButton, s.value("defaultGraphicsColour").value<QColor>());
    setButtonColour(ui->pushButton_2, s.value("graphicsHoverColour").value<QColor>());
    setButtonColour(ui->pushButton_3, s.value("defaultGraphicsColour").value<QColor>());
}

void settingsDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    update();
}

void settingsDialog::on_automaticNaming_clicked(bool checked)
{
    if (checked)
        s.setValue("automaticLabels", true);
}

void settingsDialog::on_manualNaming_clicked(bool checked)
{
    if (checked)
        s.setValue("automaticLabels", false);
}

void settingsDialog::on_pushButton_pressed()
{
    QColor colour = colourDialog->getColor();
    setButtonColour(ui->pushButton, colour);
    s.setValue("defaultGraphicsColour", colour);
}

void settingsDialog::on_pushButton_2_pressed()
{
    QColor colour = colourDialog->getColor();
    setButtonColour(ui->pushButton_2, colour);
    s.setValue("graphicsHoverColour", colour);
}

void settingsDialog::on_pushButton_3_pressed()
{
    QColor colour = colourDialog->getColor();
    setButtonColour(ui->pushButton_3, colour);
    s.setValue("backgroundColour", colour);
    setBackgroundColour(colour);
}
