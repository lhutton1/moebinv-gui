#include "figureundocommand.h"
#include <QDebug>
#include <string>
#include <iostream>

using namespace std;

figureUndoCommand::figureUndoCommand(MoebInv::figure *mainFigure, MoebInv::figure originalFigure,  MoebInv::figure changedFigure, QUndoCommand *parent) :
    QUndoCommand(parent)
{
    this->originalFigure = originalFigure;
    this->changedFigure = changedFigure;
    this->mainFigure = mainFigure;
}

void figureUndoCommand::undo()
{
    emit sceneInvalid(originalFigure);
}

void figureUndoCommand::redo()
{
    emit sceneInvalid(changedFigure);
}

QString figureUndoCommand::node_label(GiNaC::ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}
