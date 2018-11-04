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

/*!
 * \brief settingsDialog::loadValues This function takes the settings values
 * that are needed for this dialog and stores them in a map where they can be
 * edited without effecting the settings actual value.
 */
void settingsDialog::loadValues()
{
    settingValues.insert("automaticLabels", s.value("session/automaticLabels"));
    settingValues.insert("defaultSaveDirectory", s.value("session/defaultSaveDirectory"));
    settingValues.insert("automaticOnlyReals", s.value("session/automaticOnlyReals"));
    settingValues.insert("undoLimit", s.value("session/undoLimit"));
    settingValues.insert("defaultGraphicsColour", s.value("session/defaultGraphicsColour"));
    settingValues.insert("graphicsHoverColour", s.value("session/graphicsHoverColour"));
    settingValues.insert("backgroundColour", s.value("session/backgroundColour"));
    settingValues.insert("defualtLineStyle", s.value("session/defaultLineStyle"));
    settingValues.insert("defaultLineWidth", s.value("session/defaultLineWidth"));
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
    // get default colours
    setButtonColour(ui->pushButton, settingValues["defaultGraphicsColour"].value<QColor>());
    setButtonColour(ui->pushButton_2, settingValues["graphicsHoverColour"].value<QColor>());
    setButtonColour(ui->pushButton_3, settingValues["backgroundColour"].value<QColor>());

    // get default styles
    ui->comboBox->setCurrentIndex(settingValues["defaultLineStyle"].toInt());
    ui->doubleSpinBox_2->setValue(settingValues["defaultLineWidth"].toDouble());

    //set radio buttons
    if (settingValues["automaticLabels"].toBool())
        ui->automaticNaming->setChecked(true);
    else
        ui->manualNaming->setChecked(true);

    if (settingValues["automaticOnlyReals"].toBool())
        ui->onlyRealsTrue->setChecked(true);
    else
        ui->onlyRealsFalse->setChecked(true);

    // set default directory
    QDir defaultPath = QDir(settingValues["defaultSaveDirectory"].toString());
    ui->defaultPathLineEdit->setText(defaultPath.absolutePath());
    ui->defaultPathLineEdit->selectAll();

    // get default stack undo size
    int undoSize = settingValues["undoLimit"].toInt();
    ui->spinBox->setValue(undoSize);
}

void settingsDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    loadValues();
    update();
}

void settingsDialog::on_automaticNaming_clicked(bool checked)
{
    settingValues["automaticLabels"] = true;
}

void settingsDialog::on_manualNaming_clicked(bool checked)
{
    settingValues["automaticLabels"] = false;
}

void settingsDialog::on_pushButton_pressed()
{
    QColor colour = colourDialog->getColor(settingValues["defaultGraphicsColour"].value<QColor>());
    setButtonColour(ui->pushButton, colour);
    settingValues["defaultGraphicsColour"] = colour;
}

void settingsDialog::on_pushButton_2_pressed()
{
    QColor colour = colourDialog->getColor(settingValues["graphicsHoverColour"].value<QColor>());
    setButtonColour(ui->pushButton_2, colour);
    settingValues["graphicsHoverColour"] = colour;
}

void settingsDialog::on_pushButton_3_pressed()
{
    QColor colour = colourDialog->getColor(settingValues["backgroundColour"].value<QColor>());
    setButtonColour(ui->pushButton_3, colour);
    settingValues["backgroundColour"] = colour;
}

void settingsDialog::on_onlyRealsTrue_clicked(bool checked)
{
    settingValues["automaticOnlyReals"] = true;
}

void settingsDialog::on_onlyRealsFalse_clicked(bool checked)
{
    settingValues["automaticOnlyReals"] = false;
}

void settingsDialog::on_defaultPathLineEdit_textEdited(const QString &arg1)
{
    settingValues["defaultSaveDirectory"] = QDir(arg1).absolutePath();
}

void settingsDialog::on_pushButton_4_clicked()
{
    QDir filePath = QDir(QFileDialog::getExistingDirectory(nullptr, "hello",  QDir(ui->defaultPathLineEdit->text()).absolutePath()));

    if (filePath.absolutePath() != ".") {
        ui->defaultPathLineEdit->setText(filePath.absolutePath());
        settingValues["defaultSaveDirectory"] = filePath.absolutePath();
        ui->defaultPathLineEdit->selectAll();
    }
}

void settingsDialog::on_spinBox_valueChanged(int arg1)
{
    settingValues["undoLimit"] = arg1;
}

void settingsDialog::on_doubleSpinBox_2_valueChanged(double arg1)
{
    settingValues["defaultLineWidth"] = arg1;
}

void settingsDialog::on_comboBox_currentIndexChanged(int index)
{
    settingValues["defaultLineStyle"] = index;
}

void settingsDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button== ui->buttonBox->button(QDialogButtonBox::RestoreDefaults) ){
        // Change the values here if you need to change the default value of each of the settings
        settingValues["defaultLineWidth"] = 2;
        settingValues["graphicsHoverColour"] = QColor(255, 0, 0);
        settingValues["defaultGraphicsColour"] = QColor(0, 0, 0);
        settingValues["backgroundColour"] = QColor(255, 255, 255);

        QDir defaultPath = QDir(QStandardPaths::writableLocation(
            static_cast<QStandardPaths::StandardLocation>(QStandardPaths::DocumentsLocation)));
        settingValues["defaultSaveDirectory"] = defaultPath.absolutePath();
        settingValues["automaticLabels"] = true;
        settingValues["automaticOnlyReals"] = true;
        settingValues["undoLimit"] = 10;
        settingValues["defaultLineStyle"] = SOLID;

        // update the dialog to display the default settings
        update();
    } else if (button== ui->buttonBox->button(QDialogButtonBox::Apply)) {
        applySettings();
        this->close();
    } else if (button== ui->buttonBox->button(QDialogButtonBox::Ok)) {
        saveSettings();
        this->close();
    } else if (button== ui->buttonBox->button(QDialogButtonBox::Cancel)) {
        this->close();
    }
}

void settingsDialog::applySettings()
{
    // assign setting values to settings
    for (auto setting : settingValues.keys()) {
        s.setValue("session/" + setting, settingValues[setting]);
    }

    // apply all the settings
    setBackgroundColour(s.value("session/backgroundColour").value<QColor>());
    emit saveDirectoryHasChanged();
    emit sceneInvalid();
}

void settingsDialog::saveSettings()
{
    applySettings();

    // save the settings for next time
    for (auto setting : settingValues.keys()) {
        s.setValue(setting, settingValues[setting]);
    }
}
