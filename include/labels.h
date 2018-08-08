#ifndef LABELS_H
#define LABELS_H

#include <QString>
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

private:
    MoebInv::figure *fig;
    int currentLetter;
};

#endif // LABELS_H
