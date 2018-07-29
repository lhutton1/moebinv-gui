#include <QDebug>
#include "labels.h"

labels::labels()
{
    currentLetter = 1000;
}

QString labels::genNextLabel()
{
    QString lblString = "";
    int letterNumber = currentLetter;

    while (letterNumber > 0) {
        int x = (letterNumber - 1) % 26;
        char z = static_cast<char>(x + 65);
        lblString = z + lblString;
        letterNumber = (letterNumber - (x + 1)) / 26;
    }

    currentLetter += 1;

    return lblString;

}
