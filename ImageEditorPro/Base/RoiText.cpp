/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiText.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-15
*  Description: brief
*  History: 
******************************************************************************/

#include "RoiText.h"
#include "Utils.h"
#include "Define.h"

using namespace utilfunc;

RoiText::RoiText(const QPointF& point1, const QPointF& point2) : RoiRect(point1, point2)
{

}

//////////////////////////////////////////////////////////////////////////////// 
// Function: draw
// Description: 画ROI
// Parameters:QPainter & painter
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiText::draw(QPainter& painter)
{
	if (m_procColor == Qt::yellow || m_rectPos != RectPos::POS_NULL)
	{
		RoiRect::draw(painter);
	}

	QPen pen = painter.pen();
	pen.setColor(m_procColor);
	painter.setPen(pen);
	QFont font;
	font.setPixelSize(height());
	m_nFontSize = height();
	painter.setFont(font);

	QFontMetrics fm = painter.fontMetrics();
	int nWidth = fm.width(m_strText);
	if (nWidth > width())
	{
		auto cnt = m_strText.toLocal8Bit().length();
		font.setPixelSize(2 * width() / cnt);
		m_nFontSize = 2 * width() / cnt;
		painter.setFont(font);
	}

	painter.drawText(x(), y(), width(), height(), Qt::AlignCenter, m_strText);
}

Roi* RoiText::clone()
{
	return new RoiText(*this);
}

int RoiText::getFontSize()
{
	return m_nFontSize;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setText
// Description: 设置文字
// Parameters:QString & & strText
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiText::setText(QString&& strText)
{
	m_strText = std::move(strText);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: getText
// Description: 获取文字
// Return: const QT_NAMESPACE::QString&
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
const QString& RoiText::getText()
{
	return m_strText;
}
