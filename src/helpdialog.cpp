#include "helpdialog.h"
#include "ui_helpdialog.h"

#include <QDebug>

helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{
    ui->setupUi(this);
    this->helpEngine = new QHelpEngine(
                "/Users/lukehutton/OneDrive - University of Leeds/University/Computer Science/Internship/moebinv-gui/documentation/help.qhc");
    this->helpEngine->setupData();

    ui->tabWidget->setMaximumWidth(300);
    ui->tabWidget->addTab(helpEngine->contentWidget(), "Contents");
    ui->tabWidget->addTab(helpEngine->indexWidget(), "Index");

    ui->textBrowser->setHelpEngine(this->helpEngine);
    qDebug() << QUrl("qthelp://org.doxygen.project/doc/index.html").path();
    ui->textBrowser->setSource(QUrl("qthelp://org.doxygen.project/doc/index.html"));


    //connect(helpEngine->contentWidget(), &QHelpContentWidget::linkActivated, ui->textBrowser, &helpBrowser::setSource);
    //connect(helpEngine->indexWidget(), &QHelpIndexWidget::linkActivated, ui->textBrowser, &helpBrowser::setSource);
}

helpDialog::~helpDialog()
{
    delete ui;
}

// Help browser--------------------------------------------
helpBrowser::helpBrowser(QWidget* parent, QHelpEngine* helpEngine)
{
    this->helpEngine = helpEngine;
}

QVariant helpBrowser::loadResource(int type, const QUrl &name){
    if (name.scheme() == "qthelp") {
        return QVariant(helpEngine->fileData(name));
    } else {
        return QTextBrowser::loadResource(type, name);
    }
}

void helpBrowser::setHelpEngine(QHelpEngine *helpEngine)
{
    this->helpEngine = helpEngine;
}
