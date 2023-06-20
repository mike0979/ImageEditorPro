#include "ClearCmd.h"
#include "Roi.h"

ClearCmd::ClearCmd(QList<Roi*>& lstRoi, const QList<Roi*>& lstOrigRoi) : m_lstRoi(lstRoi)
{
	m_lstOrigRoi = lstOrigRoi;
}

void ClearCmd::redo()
{
	m_lstRoi.clear();
}

void ClearCmd::undo()
{
	for (const auto& roi : m_lstOrigRoi)
	{
		if (roi->getProcColor() == Qt::yellow)
		{
			roi->setProcColor(roi->getOrigColor());
		}
	}

	m_lstRoi = m_lstOrigRoi;
}

