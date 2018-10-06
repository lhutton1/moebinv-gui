/********************************************************************************
** Form generated from reading UI file 'propertiesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIESDIALOG_H
#define UI_PROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_propertiesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *figureDescriptionText;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *floatButton;
    QRadioButton *exactButton;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *ellipticPointButton;
    QRadioButton *parabolicPointButton;
    QRadioButton *hyperbolicPointButton;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *ellipticCycleButton;
    QRadioButton *parabolicCycleButton;
    QRadioButton *hyperbolicCycleButton;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *propertiesDialog)
    {
        if (propertiesDialog->objectName().isEmpty())
            propertiesDialog->setObjectName(QStringLiteral("propertiesDialog"));
        propertiesDialog->resize(700, 500);
        verticalLayout = new QVBoxLayout(propertiesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(propertiesDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        figureDescriptionText = new QTextEdit(groupBox);
        figureDescriptionText->setObjectName(QStringLiteral("figureDescriptionText"));
        figureDescriptionText->setMaximumSize(QSize(16777215, 70));

        verticalLayout_2->addWidget(figureDescriptionText);


        verticalLayout->addWidget(groupBox);

        groupBox_4 = new QGroupBox(propertiesDialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        floatButton = new QRadioButton(groupBox_4);
        floatButton->setObjectName(QStringLiteral("floatButton"));

        horizontalLayout_2->addWidget(floatButton);

        exactButton = new QRadioButton(groupBox_4);
        exactButton->setObjectName(QStringLiteral("exactButton"));

        horizontalLayout_2->addWidget(exactButton);


        verticalLayout->addWidget(groupBox_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_2 = new QGroupBox(propertiesDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        ellipticPointButton = new QRadioButton(groupBox_2);
        ellipticPointButton->setObjectName(QStringLiteral("ellipticPointButton"));

        verticalLayout_3->addWidget(ellipticPointButton);

        parabolicPointButton = new QRadioButton(groupBox_2);
        parabolicPointButton->setObjectName(QStringLiteral("parabolicPointButton"));

        verticalLayout_3->addWidget(parabolicPointButton);

        hyperbolicPointButton = new QRadioButton(groupBox_2);
        hyperbolicPointButton->setObjectName(QStringLiteral("hyperbolicPointButton"));

        verticalLayout_3->addWidget(hyperbolicPointButton);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(propertiesDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        ellipticCycleButton = new QRadioButton(groupBox_3);
        ellipticCycleButton->setObjectName(QStringLiteral("ellipticCycleButton"));

        verticalLayout_4->addWidget(ellipticCycleButton);

        parabolicCycleButton = new QRadioButton(groupBox_3);
        parabolicCycleButton->setObjectName(QStringLiteral("parabolicCycleButton"));

        verticalLayout_4->addWidget(parabolicCycleButton);

        hyperbolicCycleButton = new QRadioButton(groupBox_3);
        hyperbolicCycleButton->setObjectName(QStringLiteral("hyperbolicCycleButton"));

        verticalLayout_4->addWidget(hyperbolicCycleButton);


        horizontalLayout->addWidget(groupBox_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(propertiesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(propertiesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), propertiesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), propertiesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(propertiesDialog);
    } // setupUi

    void retranslateUi(QDialog *propertiesDialog)
    {
        propertiesDialog->setWindowTitle(QApplication::translate("propertiesDialog", "figure properties", nullptr));
        groupBox->setTitle(QApplication::translate("propertiesDialog", "Figure Description:", nullptr));
        groupBox_4->setTitle(QApplication::translate("propertiesDialog", "Evaluation type:", nullptr));
        floatButton->setText(QApplication::translate("propertiesDialog", "Floating", nullptr));
        exactButton->setText(QApplication::translate("propertiesDialog", "Exact", nullptr));
        groupBox_2->setTitle(QApplication::translate("propertiesDialog", "Point metric:", nullptr));
        ellipticPointButton->setText(QApplication::translate("propertiesDialog", "Elliptic", nullptr));
        parabolicPointButton->setText(QApplication::translate("propertiesDialog", "Parabolic", nullptr));
        hyperbolicPointButton->setText(QApplication::translate("propertiesDialog", "Hyperbolic", nullptr));
        groupBox_3->setTitle(QApplication::translate("propertiesDialog", "Cycle metric:", nullptr));
        ellipticCycleButton->setText(QApplication::translate("propertiesDialog", "Elliptic", nullptr));
        parabolicCycleButton->setText(QApplication::translate("propertiesDialog", "Parabolic", nullptr));
        hyperbolicCycleButton->setText(QApplication::translate("propertiesDialog", "Hyperbolic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class propertiesDialog: public Ui_propertiesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIESDIALOG_H
