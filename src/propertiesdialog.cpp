#include "propertiesdialog.h"
#include "ui_propertiesdialog.h"

propertiesDialog::propertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::propertiesDialog)
{
    ui->setupUi(this);
}

propertiesDialog::~propertiesDialog()
{
    delete ui;
}

void propertiesDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    update();
}

void propertiesDialog::update()
{
    // get current figure description
    ui->figureDescriptionText->setText(s.value("figureDescription").toString());
    ui->figureDescriptionText->moveCursor(QTextCursor::End);

    //get float evaluation
    switch (s.value("evaluationType").toInt()) {
        case FLOATING:
            ui->floatButton->setChecked(true);
            break;
        case EXACT:
            ui->exactButton->setChecked(true);
            break;
    }

    //get point metric
    switch (s.value("pointMetric").toInt()) {
        case ELLIPTIC:
            ui->ellipticPointButton->setChecked(true);
            break;
        case PARABOLIC:
            ui->parabolicPointButton->setChecked(true);
            break;
        case HYPERBOLIC:
            ui->hyperbolicPointButton->setChecked(true);
            break;
    }

    //get cycle metric
    switch (s.value("cycleMetric").toInt()) {
        case ELLIPTIC:
            ui->ellipticCycleButton->setChecked(true);
            break;
        case PARABOLIC:
            ui->parabolicCycleButton->setChecked(true);
            break;
        case HYPERBOLIC:
            ui->hyperbolicCycleButton->setChecked(true);
            break;
    }

}

void propertiesDialog::on_figureDescriptionText_textChanged()
{
    s.setValue("figureDescription", ui->figureDescriptionText->toPlainText());
}

void propertiesDialog::on_floatButton_clicked(bool checked)
{
    if (checked)
        s.setValue("evaluationType", FLOATING);
}

void propertiesDialog::on_exactButton_clicked(bool checked)
{
    if (checked)
        s.setValue("evaluationType", EXACT);
}

void propertiesDialog::on_ellipticPointButton_clicked(bool checked)
{
    if (checked) {
        s.setValue("pointMetric", ELLIPTIC);
        emit metricChanged();
    }
}

void propertiesDialog::on_parabolicPointButton_clicked(bool checked)
{
    if (checked) {
        s.setValue("pointMetric", PARABOLIC);
        emit metricChanged();
    }
}

void propertiesDialog::on_hyperbolicPointButton_clicked(bool checked)
{
    if (checked) {
        s.setValue("pointMetric", HYPERBOLIC);
        emit metricChanged();
    }
}

void propertiesDialog::on_ellipticCycleButton_clicked(bool checked)
{
    if (checked) {
        s.setValue("cycleMetric", ELLIPTIC);
        emit metricChanged();
    }
}

void propertiesDialog::on_parabolicCycleButton_clicked(bool checked)
{
    if (checked) {
        s.setValue("cycleMetric", PARABOLIC);
        emit metricChanged();
    }
}

void propertiesDialog::on_hyperbolicCycleButton_clicked(bool checked)
{
    if (checked) {
        s.setValue("cycleMetric", HYPERBOLIC);
        emit metricChanged();
    }
}
