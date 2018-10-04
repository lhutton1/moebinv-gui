#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QHelpEngine>
#include <QTextBrowser>
#include <QHelpContentWidget>
#include <QHelpIndexWidget>
#include <QStandardPaths>
#include <QFile>
#include <QDir>

namespace Ui {
class helpDialog;
}

class helpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit helpDialog(QWidget *parent = 0);
    ~helpDialog();

private:
    Ui::helpDialog *ui;

    QHelpEngine *helpEngine;
};

class helpBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    helpBrowser(QWidget* parent = 0, QHelpEngine* helpEngine = nullptr);
    QVariant loadResource(int type, const QUrl& name);
    void setHelpEngine(QHelpEngine *helpEngine);

private:
    QHelpEngine* helpEngine;
};

#endif // HELPDIALOG_H
