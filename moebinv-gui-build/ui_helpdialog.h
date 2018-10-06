/********************************************************************************
** Form generated from reading UI file 'helpdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include "helpdialog.h"

QT_BEGIN_NAMESPACE

class Ui_helpDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    helpBrowser *textBrowser;

    void setupUi(QDialog *helpDialog)
    {
        if (helpDialog->objectName().isEmpty())
            helpDialog->setObjectName(QStringLiteral("helpDialog"));
        helpDialog->resize(700, 500);
        horizontalLayout = new QHBoxLayout(helpDialog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(helpDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        splitter->addWidget(tabWidget);
        textBrowser = new helpBrowser(splitter);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        splitter->addWidget(textBrowser);

        horizontalLayout->addWidget(splitter);


        retranslateUi(helpDialog);

        QMetaObject::connectSlotsByName(helpDialog);
    } // setupUi

    void retranslateUi(QDialog *helpDialog)
    {
        helpDialog->setWindowTitle(QApplication::translate("helpDialog", "moebinv-gui help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class helpDialog: public Ui_helpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDIALOG_H
