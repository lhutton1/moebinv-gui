#ifndef LABELS_H
#define LABELS_H

#include <QString>
#include <QPointer>
#include <QInputDialog>
#include <QSettings>

#include <figure.h>


/*!
 * \brief The labels class
 *
 * The labels class is a small class which generates a unique
 * label incrementing as such: A, B, C, ..., Z, AA, AB, ... ZZ, AAA, ect...
 */
class labels
{

public:
    labels(MoebInv::figure *f);
    QString genNextLabel();
    GiNaC::symbol genNextSymbol(GiNaC::ex nextSymbol, bool assignName = false);
    void advanceLabel();
    QString node_label(GiNaC::ex name);
    QString getManualName();

    GiNaC::ex unnamedSymbol;

private:
    QSettings s;
    MoebInv::figure *f;
    int currentLetter;
};

#endif // LABELS_H
