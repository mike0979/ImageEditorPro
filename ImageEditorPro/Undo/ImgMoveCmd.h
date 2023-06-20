#ifndef IMG_MOVE_CMD_H
#define IMG_MOVE_CMD_H

#include <QUndoCommand>
#include <QPoint>

class ImgMoveCmd : public QUndoCommand
{
public:
	ImgMoveCmd(QPoint& picOffset, const QPoint& dis);

private:
	void redo() override;
	void undo() override;

private:
	QPoint& m_picOffset;
	QPoint m_dis;
	QPoint m_redoDis{0, 0};
};

#endif
