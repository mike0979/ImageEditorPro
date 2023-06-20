#include "ImgMoveCmd.h"

ImgMoveCmd::ImgMoveCmd(QPoint& picOffset, const QPoint& dis) : m_picOffset(picOffset)
{
	m_dis = std::move(dis);
}

void ImgMoveCmd::redo()
{
	m_picOffset += m_redoDis;
}

void ImgMoveCmd::undo()
{
	m_picOffset -= m_dis;
	m_redoDis = m_dis;
}

