#include "ImgResizeCmd.h"
#include "Roi.h"

ImgResizeCmd::ImgResizeCmd(QPoint& picOffset, const QPoint& dis, double& dScale, 
	double dOldScale, QList<Roi*>& lstRoi, int nDelta) : m_picOffset(picOffset), m_dScale(dScale), m_lstRoi(lstRoi)
{
	m_dis = std::move(dis);
	m_dOldScale = dOldScale;
	m_dChangedScale = dScale;
	m_nDelta = nDelta;
}

void ImgResizeCmd::redo()
{
	m_picOffset -= m_redoDis;
	m_dScale = m_dChangedScale;
	if (m_redoDis != QPoint(0, 0))
	{
		resize(m_nDelta);
	}
}

void ImgResizeCmd::undo()
{
	m_picOffset += m_dis;
	m_dScale = m_dOldScale;
	m_redoDis = m_dis;
	resize(-m_nDelta);
}

void ImgResizeCmd::resize(int nDelta)
{
	for (auto roi : m_lstRoi)
	{
		if (nullptr != roi)
		{
			roi->transform(nDelta);
		}
	}
}

