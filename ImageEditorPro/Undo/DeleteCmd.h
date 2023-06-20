#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include <QUndoCommand>

class Roi;

class DeleteCmd : public QUndoCommand
{
public:
	DeleteCmd(QList<Roi*>& lstRoi, Roi* pRoi);

private:
	void redo() override;
	void undo() override;

private:
	QList<Roi*>& m_lstRoi;
	Roi* m_pRoi;
};

#endif
