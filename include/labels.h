#ifndef LABELS_H
#define LABELS_H

#include <QString>

class labels
{

public:
    labels();
    QString genNextLabel();

private:
    int currentLetter;
};

#endif // LABELS_H
