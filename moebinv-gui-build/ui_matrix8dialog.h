/********************************************************************************
** Form generated from reading UI file 'matrix8dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIX8DIALOG_H
#define UI_MATRIX8DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_matrix8dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_value2;
    QLabel *label_2;
    QLineEdit *lineEdit_value3;
    QLabel *label;
    QLabel *label_4;
    QLineEdit *lineEdit_value4;
    QLabel *label_3;
    QLineEdit *lineEdit_value1;
    QLabel *label_5;
    QLineEdit *lineEdit_value8;
    QLineEdit *lineEdit_value7;
    QLineEdit *lineEdit_value5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_value6;

    void setupUi(QDialog *matrix8dialog)
    {
        if (matrix8dialog->objectName().isEmpty())
            matrix8dialog->setObjectName(QStringLiteral("matrix8dialog"));
        matrix8dialog->resize(361, 212);
        buttonBox = new QDialogButtonBox(matrix8dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 170, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit_value2 = new QLineEdit(matrix8dialog);
        lineEdit_value2->setObjectName(QStringLiteral("lineEdit_value2"));
        lineEdit_value2->setGeometry(QRect(230, 10, 113, 21));
        label_2 = new QLabel(matrix8dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 51, 21));
        lineEdit_value3 = new QLineEdit(matrix8dialog);
        lineEdit_value3->setObjectName(QStringLiteral("lineEdit_value3"));
        lineEdit_value3->setGeometry(QRect(80, 50, 113, 21));
        label = new QLabel(matrix8dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 51, 21));
        label_4 = new QLabel(matrix8dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(200, 50, 31, 21));
        lineEdit_value4 = new QLineEdit(matrix8dialog);
        lineEdit_value4->setObjectName(QStringLiteral("lineEdit_value4"));
        lineEdit_value4->setGeometry(QRect(230, 50, 113, 21));
        label_3 = new QLabel(matrix8dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(200, 10, 51, 21));
        lineEdit_value1 = new QLineEdit(matrix8dialog);
        lineEdit_value1->setObjectName(QStringLiteral("lineEdit_value1"));
        lineEdit_value1->setGeometry(QRect(80, 10, 113, 21));
        label_5 = new QLabel(matrix8dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 90, 51, 21));
        lineEdit_value8 = new QLineEdit(matrix8dialog);
        lineEdit_value8->setObjectName(QStringLiteral("lineEdit_value8"));
        lineEdit_value8->setGeometry(QRect(230, 130, 113, 21));
        lineEdit_value7 = new QLineEdit(matrix8dialog);
        lineEdit_value7->setObjectName(QStringLiteral("lineEdit_value7"));
        lineEdit_value7->setGeometry(QRect(80, 130, 113, 21));
        lineEdit_value5 = new QLineEdit(matrix8dialog);
        lineEdit_value5->setObjectName(QStringLiteral("lineEdit_value5"));
        lineEdit_value5->setGeometry(QRect(80, 90, 113, 21));
        label_6 = new QLabel(matrix8dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(200, 130, 31, 21));
        label_7 = new QLabel(matrix8dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 130, 51, 21));
        label_8 = new QLabel(matrix8dialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(200, 90, 31, 21));
        lineEdit_value6 = new QLineEdit(matrix8dialog);
        lineEdit_value6->setObjectName(QStringLiteral("lineEdit_value6"));
        lineEdit_value6->setGeometry(QRect(230, 90, 113, 21));
        QWidget::setTabOrder(lineEdit_value1, lineEdit_value2);
        QWidget::setTabOrder(lineEdit_value2, lineEdit_value5);
        QWidget::setTabOrder(lineEdit_value5, lineEdit_value7);
        QWidget::setTabOrder(lineEdit_value7, lineEdit_value3);
        QWidget::setTabOrder(lineEdit_value3, lineEdit_value4);
        QWidget::setTabOrder(lineEdit_value4, lineEdit_value6);
        QWidget::setTabOrder(lineEdit_value6, lineEdit_value8);

        retranslateUi(matrix8dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), matrix8dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), matrix8dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(matrix8dialog);
    } // setupUi

    void retranslateUi(QDialog *matrix8dialog)
    {
        matrix8dialog->setWindowTitle(QApplication::translate("matrix8dialog", "Dialog", nullptr));
        label_2->setText(QApplication::translate("matrix8dialog", "Value 2:", nullptr));
        label->setText(QApplication::translate("matrix8dialog", "Value 1:", nullptr));
        label_4->setText(QApplication::translate("matrix8dialog", "+ I *", nullptr));
        label_3->setText(QApplication::translate("matrix8dialog", "+ I *", nullptr));
        label_5->setText(QApplication::translate("matrix8dialog", "Value 3:", nullptr));
        label_6->setText(QApplication::translate("matrix8dialog", "+ I *", nullptr));
        label_7->setText(QApplication::translate("matrix8dialog", "Value 4:", nullptr));
        label_8->setText(QApplication::translate("matrix8dialog", "+ I *", nullptr));
    } // retranslateUi

};

namespace Ui {
    class matrix8dialog: public Ui_matrix8dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIX8DIALOG_H
