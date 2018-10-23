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
    settingValues.insert("automaticLabels", s.value("automaticLabels"));
    settingValues.insert("defaultSaveDirectory", s.value("defaultSaveDirectory"));
    settingValues.insert("automaticOnlyReals", s.value("automaticOnlyReals"));
    settingValues.insert("undoLimit", s.value("undoLimit"));
    settingValues.insert("defaultGraphicsColour", s.value("defaultGraphicsColour"));
    settingValues.insert("graphicsHoverColour", s.value("graphicsHoverColour"));
    settingValues.insert("backgroundColour", s.value("backgroundColour"));
    settingValues.insert("defualtLineStyle", s.value("defaultLineStyle"));
    settingValues.insert("defaultLineWidth", s.value("defaultLineWidth"));
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
    setButtonColour(ui->pushButton, s.value("defaultGraphicsColour").value<QColor>());
    setButtonColour(ui->pushButton_2, s.value("graphicsHoverColour").value<QColor>());
    setButtonColour(ui->pushButton_3, s.value("backgroundColour").value<QColor>());

    // get default styles
    ui->comboBox->setCurrentIndex(s.value("defaultLineStyle").toInt());
    ui->doubleSpinBox_2->setValue(s.value("defaultLineWidth").toDouble());

    //set radio buttons
    if (s.value("automaticLabels").toBool())
        ui->automaticNaming->setChecked(true);
    else
        ui->manualNaming->setChecked(true);

    if (s.value("automaticOnlyReals").toBool())
        ui->onlyRealsTrue->setChecked(true);
    else
        ui->onlyRealsFalse->setChecked(true);

    // set default directory
    QDir defaultPath = QDir(s.value("defaultSaveDirectory").toString());
    ui->defaultPathLineEdit->setText(defaultPath.absolutePath());
    ui->defaultPathLineEdit->selectAll();

    // get default stack undo size
    int undoSize = s.value("undoLimit").toInt();
    ui->spinBox->setValue(undoSize);
}

void settingsDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    update();
}

void settingsDialog::on_automaticNaming_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["automaticLabels"] = true;
}

void settingsDialog::on_manualNaming_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["automaticLabels"] = false;
}

void settingsDialog::on_pushButton_pressed()
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    QColor colour = colourDialog->getColor(s.value("defaultGraphicsColour").value<QColor>());
    setButtonColour(ui->pushButton, colour);
    settingValues["defaultGraphicsColour"] = colour;
}

void settingsDialog::on_pushButton_2_pressed()
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    QColor colour = colourDialog->getColor(s.value("graphicsHoverColour").value<QColor>());
    setButtonColour(ui->pushButton_2, colour);
    settingValues["graphicsHoverColour"] = colour;
}

void settingsDialog::on_pushButton_3_pressed()
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    QColor colour = colourDialog->getColor(s.value("backgroundColour").value<QColor>());
    setButtonColour(ui->pushButton_3, colour);
    settingValues["backgroundColour"] = colour;
}

void settingsDialog::on_onlyRealsTrue_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["automaticOnlyReals"] = true;
}

void settingsDialog::on_onlyRealsFalse_clicked(bool checked)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["automaticOnlyReals"] = false;
}

void settingsDialog::on_defaultPathLineEdit_textEdited(const QString &arg1)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    s.setValue("defaultSaveDirectory", QDir(arg1).absolutePath());
}

void settingsDialog::on_pushButton_4_clicked()
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    QDir filePath = QDir(QFileDialog::getExistingDirectory(nullptr, "hello",  QDir(ui->defaultPathLineEdit->text()).absolutePath()));

    if (filePath.absolutePath() != ".") {
        ui->defaultPathLineEdit->setText(filePath.absolutePath());
        settingValues["defaultSaveDirectory"] = filePath.absolutePath();
        ui->defaultPathLineEdit->selectAll();
    }
}

void settingsDialog::on_spinBox_valueChanged(int arg1)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["undoLimit"] = arg1;
}

void settingsDialog::on_doubleSpinBox_2_valueChanged(double arg1)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["defaultLineWidth"] = arg1;
}

void settingsDialog::on_comboBox_currentIndexChanged(int index)
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    settingValues["defaultLineStyle"] = index;
}

void settingsDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button== ui->buttonBox->button(QDialogButtonBox::RestoreDefaults) ){
        // Change the values here if you need to change the default value of each of the settings
        /*!
         * Sets the thickness of lines drawn in the scene.
         */
        s.setValue("defaultLineWidth", 2);

        /*!
         * Set the hover colour of the graphics on the scene.
         */
        s.setValue("graphicsHoverColour", QColor(255, 0, 0));

        /*!
         * Set the default colour of the graphics in the scene.
         */
        s.setValue("defaultGraphicsColour", QColor(0, 0, 0));

        /*!
         * Set the default background colour
         */
        s.setValue("backgroundColour", QColor(255, 255, 255));

        /*!
         * The default save directory for .gar files.
         */
        QDir defaultPath = QDir(QStandardPaths::writableLocation(
            static_cast<QStandardPaths::StandardLocation>(QStandardPaths::DocumentsLocation)));
        s.setValue("defaultSaveDirectory", defaultPath.absolutePath());

        /*!
         * Set automatic assignment of labels i.e. A, B, C, ...
         */
        s.setValue("automaticLabels", true);

        /*!
         * Set whether the only reals relation is applied automatically to 'this'.
         */
        s.setValue("automaticOnlyReals", true);

        /*!
         * Set the undo stack size limit.
         */
        s.setValue("undoLimit", 10);

        /*!
         * Set the default line style.
         */
        s.setValue("defaultLineStyle", SOLID);

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

void settingsDialog::applySettings()
{
    // assign setting values to settings
    for (auto setting : settingValues.keys()) {
        s.setValue(setting, settingValues[setting]);
    }

    // apply all the settings
    setBackgroundColour(s.value("backgroundColour").value<QColor>());
    emit saveDirectoryHasChanged();
    emit sceneInvalid();
}
