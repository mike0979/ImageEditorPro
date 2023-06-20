#include "DeleteCmd.h"
#include "Roi.h"

DeleteCmd::DeleteCmd(QList<Roi*>& lstRoi, Roi* pRoi) : m_lstRoi(lstRoi)
{
	m_pRoi = pRoi;
}

void DeleteCmd::redo()
{
	m_lstRoi.removeAll(m_pRoi);
}

void DeleteCmd::undo()
{
	m_pRoi->setProcColor(m_pRoi->getOrigColor());
	m_lstRoi.push_back(m_pRoi);
}
