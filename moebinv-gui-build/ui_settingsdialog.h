/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingsDialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *automaticNaming;
    QRadioButton *manualNaming;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QDoubleSpinBox *doubleSpinBox;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *defaultPathLineEdit;
    QPushButton *pushButton_4;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *onlyRealsTrue;
    QRadioButton *onlyRealsFalse;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_6;
    QSpinBox *spinBox;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *comboBox;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *settingsDialog)
    {
        if (settingsDialog->objectName().isEmpty())
            settingsDialog->setObjectName(QStringLiteral("settingsDialog"));
        settingsDialog->resize(700, 500);
        verticalLayout_4 = new QVBoxLayout(settingsDialog);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tabWidget = new QTabWidget(settingsDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        automaticNaming = new QRadioButton(groupBox);
        automaticNaming->setObjectName(QStringLiteral("automaticNaming"));
        automaticNaming->setChecked(true);

        horizontalLayout->addWidget(automaticNaming);

        manualNaming = new QRadioButton(groupBox);
        manualNaming->setObjectName(QStringLiteral("manualNaming"));

        horizontalLayout->addWidget(manualNaming);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        doubleSpinBox = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        verticalLayout_3->addWidget(doubleSpinBox);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        defaultPathLineEdit = new QLineEdit(groupBox_6);
        defaultPathLineEdit->setObjectName(QStringLiteral("defaultPathLineEdit"));

        horizontalLayout_3->addWidget(defaultPathLineEdit);

        pushButton_4 = new QPushButton(groupBox_6);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_3->addWidget(pushButton_4);


        verticalLayout_2->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_7);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        onlyRealsTrue = new QRadioButton(groupBox_7);
        onlyRealsTrue->setObjectName(QStringLiteral("onlyRealsTrue"));
        onlyRealsTrue->setChecked(true);

        horizontalLayout_2->addWidget(onlyRealsTrue);

        onlyRealsFalse = new QRadioButton(groupBox_7);
        onlyRealsFalse->setObjectName(QStringLiteral("onlyRealsFalse"));

        horizontalLayout_2->addWidget(onlyRealsFalse);


        verticalLayout_2->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_6 = new QVBoxLayout(groupBox_8);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        spinBox = new QSpinBox(groupBox_8);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        verticalLayout_6->addWidget(spinBox);


        verticalLayout_2->addWidget(groupBox_8);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(50, 0));
        pushButton_2->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(50, 0));
        pushButton->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(50, 0));
        pushButton_3->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(pushButton_3, 2, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(285, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        comboBox = new QComboBox(groupBox_4);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));

        gridLayout_2->addWidget(doubleSpinBox_2, 1, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_4->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(settingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);


        retranslateUi(settingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), settingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), settingsDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(settingsDialog);
    } // setupUi

    void retranslateUi(QDialog *settingsDialog)
    {
        settingsDialog->setWindowTitle(QApplication::translate("settingsDialog", "moebinv-gui settings", nullptr));
        groupBox->setTitle(QApplication::translate("settingsDialog", "Naming of cycles:", nullptr));
        automaticNaming->setText(QApplication::translate("settingsDialog", "Automatic", nullptr));
        manualNaming->setText(QApplication::translate("settingsDialog", "Manual", nullptr));
        groupBox_2->setTitle(QApplication::translate("settingsDialog", "Figure redraw delay:", nullptr));
        groupBox_6->setTitle(QApplication::translate("settingsDialog", "Default save directory:", nullptr));
        pushButton_4->setText(QApplication::translate("settingsDialog", "Browse...", nullptr));
        groupBox_7->setTitle(QApplication::translate("settingsDialog", "Only reals:", nullptr));
        onlyRealsTrue->setText(QApplication::translate("settingsDialog", "Enabled", nullptr));
        onlyRealsFalse->setText(QApplication::translate("settingsDialog", "Dissabled", nullptr));
        groupBox_8->setTitle(QApplication::translate("settingsDialog", "Undo stack size:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("settingsDialog", "Figure", nullptr));
        groupBox_3->setTitle(QApplication::translate("settingsDialog", "Default Colours:", nullptr));
        label->setText(QApplication::translate("settingsDialog", "Cycle colour:", nullptr));
        pushButton_2->setText(QString());
        label_2->setText(QApplication::translate("settingsDialog", "Cycle hover colour:", nullptr));
        label_3->setText(QApplication::translate("settingsDialog", "Background colour:", nullptr));
        pushButton->setText(QString());
        pushButton_3->setText(QString());
        groupBox_4->setTitle(QApplication::translate("settingsDialog", "Default style:", nullptr));
        label_4->setText(QApplication::translate("settingsDialog", "Cycle line style:", nullptr));
        comboBox->setItemText(0, QApplication::translate("settingsDialog", "Solid", nullptr));
        comboBox->setItemText(1, QApplication::translate("settingsDialog", "Dotted", nullptr));
        comboBox->setItemText(2, QApplication::translate("settingsDialog", "Dashed", nullptr));

        label_5->setText(QApplication::translate("settingsDialog", "Cycle line width:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("settingsDialog", "Graphics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingsDialog: public Ui_settingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
