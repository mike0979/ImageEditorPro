/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: MeasureAngle.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-22
*  Description: brief
*  History: 
******************************************************************************/

#include "MeasureAngle.h"

#define  ANGLE_SIDE 100

MeasureAngle::MeasureAngle(const QVector<QPointF>& vecPoints) : RoiPolyline(vecPoints)
{

}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setRoiPoint
// Description: 设置点的位置
// Parameters:const QPoint & point
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void MeasureAngle::setRoiPoint(const QPoint& point)
{
	if (1 == m_nIndex || -1 == m_nIndex)
	{
		return;
	}

	RoiPolygon::setRoiPoint(point);
	QLineF line1 = std::move(QLineF((*this)[1], (*this)[0]));
	QLineF line2 = std::move(QLineF((*this)[1], (*this)[2]));
	m_angle = line1.angleTo(line2);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: draw
// Description: 画ROI
// Parameters:QPainter & painter
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void MeasureAngle::draw(QPainter& painter)
{
	RoiPolyline::setDrawEllipse(true);
	RoiPolyline::draw(painter);
	painter.setFont(QFont());

	if (2 == m_nIndex)
	{
		if (m_angle <= 180)
		{
			painter.drawArc((*this)[1].x() - ANGLE_SIDE * m_dScale * 0.5, (*this)[1].y() - ANGLE_SIDE * m_dScale * 0.5, ANGLE_SIDE * m_dScale, ANGLE_SIDE * m_dScale, m_angle2, m_angle * 16);
			m_angle1 = m_angle2 + m_angle * 16;
			painter.drawText(getTextPos(), QString::number(m_angle));
			m_curAngle = m_angle;
			m_curAngle1 = m_angle2;
			m_curAngle2 = m_angle * 16;
		}
		else
		{
			painter.drawArc((*this)[1].x() - ANGLE_SIDE * m_dScale * 0.5, (*this)[1].y() - ANGLE_SIDE * m_dScale * 0.5, ANGLE_SIDE * m_dScale, ANGLE_SIDE * m_dScale, m_angle2, -(360 - m_angle) * 16);
			m_angle1 = m_angle2 - (360 - m_angle) * 16;
			painter.drawText(getTextPos(), QString::number(360 - m_angle));
			m_curAngle = 360 - m_angle;
			m_curAngle1 = m_angle2;
			m_curAngle2 = -(360 - m_angle) * 16;
		}
	}
	else if (m_nIndex >= 0)
	{
		if (m_angle <= 180)
		{
			painter.drawArc((*this)[1].x() - ANGLE_SIDE * m_dScale * 0.5, (*this)[1].y() - ANGLE_SIDE * m_dScale * 0.5, ANGLE_SIDE * m_dScale, ANGLE_SIDE * m_dScale, m_angle1, -m_angle * 16);
			m_angle2 = m_angle1 - m_angle * 16;
			painter.drawText(getTextPos(), QString::number(m_angle));
			m_curAngle = m_angle;
			m_curAngle1 = m_angle1;
			m_curAngle2 = -m_angle * 16;
		}
		else
		{
			painter.drawArc((*this)[1].x() - ANGLE_SIDE * m_dScale * 0.5, (*this)[1].y() - ANGLE_SIDE * m_dScale * 0.5, ANGLE_SIDE * m_dScale, ANGLE_SIDE * m_dScale, m_angle1, (360 - m_angle) * 16);
			m_angle2 = m_angle1 + (360 - m_angle) * 16;
			painter.drawText(getTextPos(), QString::number(360 - m_angle));
			m_curAngle = 360 - m_angle;
			m_curAngle1 = m_angle1;
			m_curAngle2 = (360 - m_angle) * 16;
		}
	}
	else
	{
		painter.drawArc((*this)[1].x() - ANGLE_SIDE * m_dScale * 0.5, (*this)[1].y() - ANGLE_SIDE * m_dScale * 0.5, ANGLE_SIDE * m_dScale, ANGLE_SIDE * m_dScale, m_curAngle1, m_curAngle2);
		painter.drawText(getTextPos(), QString::number(m_curAngle));
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: getTextPos
// Description: 获取文字的位置
// Return: const QT_NAMESPACE::QPointF&
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
const QPointF& MeasureAngle::getTextPos()
{
	QLineF line1 = std::move(QLineF((*this)[1], (*this)[0]));
	QLineF line2 = std::move(QLineF((*this)[1], (*this)[2]));
	auto vec1 = line1.unitVector();
	auto vec2 = line2.unitVector();
	vec1.setLength(ANGLE_SIDE * m_dScale);
	vec2.setLength(ANGLE_SIDE * m_dScale);
	return m_textPos = (vec1.p2() + vec2.p2()) * 0.5;
}

