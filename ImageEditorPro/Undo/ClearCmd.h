#ifndef CLEAR_COMMAND_H
#define CLEAR_COMMAND_H

#include <QUndoCommand>

class Roi;

class ClearCmd : public QUndoCommand
{
public:
	ClearCmd(QList<Roi*>& lstRoi, const QList<Roi*>& lstOrigRoi);

private:
	void redo() override;
	void undo() override;

private:
	QList<Roi*>& m_lstRoi;
	QList<Roi*> m_lstOrigRoi;
};

#endif
