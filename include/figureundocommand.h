#ifndef FIGUREUNDOCOMMAND_H
#define FIGUREUNDOCOMMAND_H

#include <QUndoCommand>
#include <QSettings>

#include <figure.h>


class figureUndoCommand : public QObject, public QUndoCommand
{
    Q_OBJECT

public:
    figureUndoCommand(MoebInv::figure *mainFigure, MoebInv::figure originalFigure,  MoebInv::figure changedFigure, QUndoCommand *parent = nullptr);
    void undo();
    void redo();
    QString node_label(GiNaC::ex name);

signals:
    void sceneInvalid(const MoebInv::figure &replacementFigure);

private:
    MoebInv::figure originalFigure;
    MoebInv::figure changedFigure;
    MoebInv::figure *mainFigure;
};

#endif // FIGUREUNDOCOMMAND_H
