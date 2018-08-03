#include <QDebug>
#include "labels.h"

/*!
 * \brief labels::labels Labels constructor.
 */
labels::labels()
{
    currentLetter = 1;
}

/*!
 * \brief labels::genNextLabel Generate next label.
 * \return New label.
 *
 * Generate the next label in the sequence i.e. A, B, C, ..., Z, AA, AB, ...
 */
QString labels::genNextLabel()
{
    QString lblString = "";
    int letterNumber = currentLetter;

    while (letterNumber > 0) {
        int current = (letterNumber - 1) % 26;
        char letter = static_cast<char>(current + 65);
        lblString = letter + lblString;
        letterNumber = (letterNumber - (current + 1)) / 26;
    }

    return lblString;
}

void labels::advanceLabel() {
    currentLetter += 1;
}
