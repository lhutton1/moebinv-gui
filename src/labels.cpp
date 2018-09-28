#include <QDebug>
#include "labels.h"

#include <string>
#include <iostream>

/*!
 * \brief labels::labels Labels constructor.
 */
labels::labels(MoebInv::figure *f)
{
    this->f = f;
    this->currentLetter = 1;
    this->unnamedSymbol = GiNaC::symbol("unnamed");
}


/*!
 * \brief labels::genNextLabel Generate next label.
 * \return New label.
 *
 * Generate the next label in the sequence i.e. A, B, C, ..., Z, AA, AB, ...
 */
QString labels::genNextLabel()
{
    QString lblString;
    int letterNumber;

    if (s.value("automaticLabels").toBool()) {
        letterNumber = currentLetter;
        lblString = "";

        while (letterNumber > 0) {
            int current = (letterNumber - 1) % 26;
            char letter = static_cast<char>(current + 65);
            lblString = letter + lblString;
            letterNumber = (letterNumber - (current + 1)) / 26;
        }
    } else {
        lblString = "unnamed";
    }

    return lblString;
}

GiNaC::symbol labels::genNextSymbol(GiNaC::ex nextSymbol, bool assignName)
{
    QString nextLabel = this->genNextLabel();

    // create the relevent symbol based on setting (manual/automatic) and
    // current state of the program
    if (!s.value("automaticLabels").toBool() && !assignName) {
        return GiNaC::ex_to<GiNaC::symbol>(this->unnamedSymbol);
    } else if (!s.value("automaticLabels").toBool() && assignName) {
        return GiNaC::symbol(qPrintable(this->getManualName()));
    } else if (s.value("automaticLabels").toBool() && nextLabel == "unnamed") {
        this->advanceLabel();
        return GiNaC::symbol(qPrintable(this->genNextLabel()));
    } else if (node_label(nextSymbol) == nextLabel) {
        return GiNaC::ex_to<GiNaC::symbol>(nextSymbol);
    } else {
        return GiNaC::symbol(qPrintable(this->genNextLabel()));
    }
}


/*!
 * \brief labels::advanceLabel Advance to the next free label
 */
void labels::advanceLabel() {
    GiNaC::ex currentKey;

    if (s.value("automaticLabels").toBool()) {
        currentLetter += 1;

        // test for duplicate labels. If there is a duplicate, run function recursively.
        currentKey = f->get_cycle_key(qPrintable(this->genNextLabel()));

        if (node_label(currentKey) == "0")
            return;
        else
            this->advanceLabel();
    }
}

QString labels::getManualName()
{
    return QInputDialog::getText(nullptr, "Label name", "Enter label name:");
}

QString labels::node_label(GiNaC::ex name) // REMOVE
{
    std::ostringstream drawing;
    drawing << name;
    std::string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}
