/********************************************************************************
** Form generated from reading UI file 'matrix4dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIX4DIALOG_H
#define UI_MATRIX4DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_matrix4dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_value2;
    QLineEdit *lineEdit_value4;
    QLineEdit *lineEdit_value1;
    QLineEdit *lineEdit_value3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *matrix4dialog)
    {
        if (matrix4dialog->objectName().isEmpty())
            matrix4dialog->setObjectName(QStringLiteral("matrix4dialog"));
        matrix4dialog->resize(391, 140);
        buttonBox = new QDialogButtonBox(matrix4dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 100, 361, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit_value2 = new QLineEdit(matrix4dialog);
        lineEdit_value2->setObjectName(QStringLiteral("lineEdit_value2"));
        lineEdit_value2->setGeometry(QRect(260, 20, 113, 21));
        lineEdit_value4 = new QLineEdit(matrix4dialog);
        lineEdit_value4->setObjectName(QStringLiteral("lineEdit_value4"));
        lineEdit_value4->setGeometry(QRect(260, 60, 113, 21));
        lineEdit_value1 = new QLineEdit(matrix4dialog);
        lineEdit_value1->setObjectName(QStringLiteral("lineEdit_value1"));
        lineEdit_value1->setGeometry(QRect(70, 20, 113, 21));
        lineEdit_value3 = new QLineEdit(matrix4dialog);
        lineEdit_value3->setObjectName(QStringLiteral("lineEdit_value3"));
        lineEdit_value3->setGeometry(QRect(70, 60, 113, 21));
        label = new QLabel(matrix4dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 51, 21));
        label_2 = new QLabel(matrix4dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 51, 21));
        label_3 = new QLabel(matrix4dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(200, 20, 51, 21));
        label_4 = new QLabel(matrix4dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(200, 60, 51, 21));
        QWidget::setTabOrder(lineEdit_value1, lineEdit_value2);
        QWidget::setTabOrder(lineEdit_value2, lineEdit_value3);
        QWidget::setTabOrder(lineEdit_value3, lineEdit_value4);

        retranslateUi(matrix4dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), matrix4dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), matrix4dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(matrix4dialog);
    } // setupUi

    void retranslateUi(QDialog *matrix4dialog)
    {
        matrix4dialog->setWindowTitle(QApplication::translate("matrix4dialog", "Sl2 Relation", nullptr));
        label->setText(QApplication::translate("matrix4dialog", "Value 1:", nullptr));
        label_2->setText(QApplication::translate("matrix4dialog", "Value 3:", nullptr));
        label_3->setText(QApplication::translate("matrix4dialog", "Value 2:", nullptr));
        label_4->setText(QApplication::translate("matrix4dialog", "Value 4:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class matrix4dialog: public Ui_matrix4dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIX4DIALOG_H
