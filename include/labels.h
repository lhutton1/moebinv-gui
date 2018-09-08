#ifndef LABELS_H
#define LABELS_H

#include <QString>
#include <QPointer>
#include "figure.h"


/*!
 * \brief The labels class
 *
 * The labels class is a small class which generates a unique
 * label incrementing as such: A, B, C, ..., Z, AA, AB, ... ZZ, AAA, ect...
 */
class labels
{

public:
    labels();
    QString genNextLabel();
    void advanceLabel();
    QString node_label(GiNaC::ex name);

private:
    MoebInv::figure *f;
    int currentLetter;


};

#endif // LABELS_H
