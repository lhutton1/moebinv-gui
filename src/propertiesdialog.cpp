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

/*!
 * \brief settingsDialog::loadValues This function takes the settings values
 * that are needed for this dialog and stores them in a map where they can be
 * edited without effecting the settings actual value.
 */
void propertiesDialog::loadValues()
{
    settingValues.insert("pointMetric", s.value("pointMetric"));
    settingValues.insert("cycleMetric", s.value("cycleMetric"));
    settingValues.insert("evaluationType", s.value("evaluationType"));
    settingValues.insert("figureDescription", s.value("figureDescription"));
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
    settingValues["figureDescription"] = ui->figureDescriptionText->toPlainText();
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}

void propertiesDialog::on_floatButton_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["evaluationType"] = FLOATING;
}

void propertiesDialog::on_exactButton_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["evaluationType"] = EXACT;
}

void propertiesDialog::on_ellipticPointButton_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["pointMetric"] = ELLIPTIC;
}

void propertiesDialog::on_parabolicPointButton_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["pointMetric"] = PARABOLIC;
}

void propertiesDialog::on_hyperbolicPointButton_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["pointMetric"] = HYPERBOLIC;
}

void propertiesDialog::on_ellipticCycleButton_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["cycleMetric"] = ELLIPTIC;
}

void propertiesDialog::on_parabolicCycleButton_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["cycleMetric"] = PARABOLIC;
}

void propertiesDialog::on_hyperbolicCycleButton_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["cycleMetric"] = HYPERBOLIC;
}

void propertiesDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button== ui->buttonBox->button(QDialogButtonBox::RestoreDefaults) ){
        // Change the values here if you need to change the default value of each of the settings
        /*!
         * Sets the drawing metric.
         */
        s.setValue("pointMetric", ELLIPTIC);

        /*!
         * Sets the cycle metric.
         */
        s.setValue("cycleMetric", ELLIPTIC);

        /*!
         * Sets the figure evaluation type.
         */
        s.setValue("evaluationType", FLOATING);

        /*!
         * Set the default figure description.
         */
        s.setValue("figureDescription", "no description");

        // update the dialog to display the default settings
        update();
        ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    } else if (button== ui->buttonBox->button(QDialogButtonBox::Apply)) {
        applySettings();
        ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
    } else if (button== ui->buttonBox->button(QDialogButtonBox::Ok)) {
        applySettings();
        this->close();
    } else if (button== ui->buttonBox->button(QDialogButtonBox::Cancel)) {
        this->close();
    }
}

void propertiesDialog::applySettings()
{
    // assign setting values to settings
    for (auto setting : settingValues.keys()) {
        s.setValue(setting, settingValues[setting]);
    }

    //apply settings
    emit metricChanged();
}
