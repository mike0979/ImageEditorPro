/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: MeasureLine.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-22
*  Description: brief
*  History: 
******************************************************************************/

#include "MeasureLine.h"

#define ARROW_LENGTH 20

MeasureLine::MeasureLine(const QPoint& point1, const QPoint& point2) : RoiLine(point1, point2)
{

}

//////////////////////////////////////////////////////////////////////////////// 
// Function: draw
// Description: 画ROI
// Parameters:QPainter & painter
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void MeasureLine::draw(QPainter& painter)
{
	QPen pen = painter.pen();
	pen.setColor(m_procColor);
	painter.setPen(pen);
	painter.drawLine(*this);
	painter.setFont(QFont());

	if (m_bShowAll)
	{
		auto vec1 = unitVector();
		auto vec2 = vec1;

		vec1.setLength(ARROW_LENGTH);
		auto line1 = vec1.normalVector();
		auto line2 = line1.normalVector().normalVector();
		m_line1 = QLineF(line1.p2(), line2.p2());
		m_line2 = QLineF(m_line1.p1() + QPoint(dx(), dy()), m_line1.p2() + QPoint(dx(), dy()));
		m_lenPos = QPoint(center().x() + line1.dx(), center().y() + line1.dy());

		vec2.translate(dx() * ARROW_LENGTH / length(), dy() * ARROW_LENGTH / length());
		vec1.translate(dx() * (length() - ARROW_LENGTH) / length(), dy() * (length() - ARROW_LENGTH) / length());

		auto vec12 = vec1.normalVector();
		auto vec13 = vec12.normalVector().normalVector();
		auto vec21 = vec2.normalVector();
		vec21.setLength(ARROW_LENGTH);
		auto vec22 = vec21.normalVector();
		auto vec23 = vec22.normalVector();
		m_arrow1 = std::move(QPolygonF(QVector<QPointF> { vec21.p2(), vec22.p2(), vec23.p2() }));
		m_arrow2 = std::move(QPolygonF(QVector<QPointF> { vec12.p2(), vec1.p2(), vec13.p2() }));

		painter.drawPolyline(m_arrow1);
		painter.drawPolyline(m_arrow2);
		painter.drawLine(m_line1);
		painter.drawLine(m_line2);
		painter.drawText(m_lenPos, QString::number(length() / m_dScale));
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setShowFlag
// Description: 设置显示标志
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void MeasureLine::setShowFlag()
{
	m_bShowAll = true;
}
