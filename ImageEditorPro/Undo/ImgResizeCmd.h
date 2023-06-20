#ifndef IMG_RESIZE_CMD_H
#define IMG_RESIZE_CMD_H

#include <QUndoCommand>
#include <QPoint>

class Roi;

class ImgResizeCmd : public QUndoCommand
{
public:
	ImgResizeCmd(QPoint& picOffset, const QPoint& dis, double& dScale, 
		double dOldScale, QList<Roi*>& lstRoi, int nDelta);

private:
	void redo() override;
	void undo() override;
	void resize(int nDelta);

private:
	QPoint& m_picOffset;
	QPoint m_dis;
	double m_dOldScale;
	double m_dChangedScale;
	double& m_dScale;
	QPoint m_redoDis{0, 0};
	QList<Roi*>& m_lstRoi;
	int m_nDelta;
};

#endif
