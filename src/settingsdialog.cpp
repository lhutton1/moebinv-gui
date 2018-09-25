#include "settingsdialog.h"
#include "ui_settingsdialog.h"

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);

    colourDialog = new QColorDialog();

    // create a list of buttons that will be used for colour selection
    this->colourSelectionButtons = QList<QPushButton *>();
    this->colourSelectionButtons.append(ui->pushButton);
    this->colourSelectionButtons.append(ui->pushButton_2);
    this->colourSelectionButtons.append(ui->pushButton_3);

    for (auto button : this->colourSelectionButtons)
        connect(button, &QPushButton::pressed, this, &settingsDialog::getColourSelection);
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::getColourSelection()
{
    colourDialog->exec();
}

void settingsDialog::update()
{
    // get current figure description
    ui->figureDescriptionText->setText(s.value("figureDescription").toString());
    ui->figureDescriptionText->moveCursor(QTextCursor::End);

}

void settingsDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    update();
}
