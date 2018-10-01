#include "figureundocommand.h"
#include <QDebug>
#include <string>
#include <iostream>

using namespace std;

/*!
 * \brief figureUndoCommand::figureUndoCommand
 * \param originalFigure
 * \param changedFigure
 * \param parent
 *
 * Figure undo command constructor. This object is inherited from QUndoCommand and
 * allows any changes made to a figure to be stored in the undo stack.
 */
figureUndoCommand::figureUndoCommand(MoebInv::figure originalFigure,  MoebInv::figure changedFigure, QUndoCommand *parent) :
    QUndoCommand(parent)
{
    this->originalFigure = originalFigure;
    this->changedFigure = changedFigure;
    this->mainFigure = mainFigure;
}


/*!
 * \brief figureUndoCommand::undo
 *
 * Undo an action and resore the previous figure before the change.
 */
void figureUndoCommand::undo()
{
    emit sceneInvalid(originalFigure);
}


/*!
 * \brief figureUndoCommand::redo
 *
 * Redo an action and resore the figure after it has been changed.
 */
void figureUndoCommand::redo()
{
    emit sceneInvalid(changedFigure);
}


// REMOVE....
QString figureUndoCommand::node_label(GiNaC::ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}
