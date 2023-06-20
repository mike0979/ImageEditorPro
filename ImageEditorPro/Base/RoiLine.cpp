/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiLine.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "RoiLine.h"
#include "Utils.h"
#include "Define.h"

using namespace utilfunc;

#define OFFSET 1 // ѡ��ֱ��ʱ��������ƫ����

RoiLine::RoiLine(const QPointF& point1, const QPointF& point2) : QLineF(point1, point2)
{

}

RoiLine::~RoiLine()
{

}

//////////////////////////////////////////////////////////////////////////////// 
// Function: move
// Description: �ƶ�ROI
// Parameters:const QPoint & point
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiLine::move(const QPoint& point)
{
	translate(point);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: draw
// Description: ��ROI
// Parameters:QPainter & painter
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiLine::draw(QPainter& painter)
{
	QPen pen = painter.pen();
	pen.setColor(m_procColor);
	painter.setPen(pen);
	painter.drawLine(*this);
	drawVertex(painter, pen);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isInside
// Description: �жϵ��Ƿ���ROI�����ֱ����
// Parameters:const QPoint & point
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiLine::isInside(const QPoint& point)
{
	// �ж�Ч�ʲ��ߣ����Ż�
	QLineF temp1 = QLineF(point, p1());
	QLineF temp2 = QLineF(point, p2());
	QLineF temp3 = QLineF(p1(), p2());
	return temp1.length() + temp2.length() <= temp3.length() + OFFSET ? true : false;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isInRect
// Description: �ж�ROI�ĵ��ڲ���rect��
// Parameters:const QRect & rect
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiLine::isInRect(const QRectF& rect)
{
	return rect.contains(p1()) || rect.contains(p2());
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isRoiPoint
// Description: �жϵ��Ƿ���ROI�����ϵĵ�
// Parameters:const QPoint & point
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiLine::isRoiPoint(const QPoint& point)
{
	// �������ֱ�����������յ㣬�ͼ��µ��λ��
	if (Point2PointDis(p1(), point) <= MIN_DISTANCE * MIN_DISTANCE)
	{
		m_linePos = LinePos::POS_P1;
		return true;
	}
	else if (Point2PointDis(p2(), point) <= MIN_DISTANCE * MIN_DISTANCE)
	{
		m_linePos = LinePos::POS_P2;
		return true;
	}
	else
	{
		m_linePos = LinePos::POS_NULL;
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setRoiPoint
// Description: ����ROI�����ĵ�
// Parameters:const QPoint & point
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiLine::setRoiPoint(const QPoint& point)
{
	// ���ݵ��λ���滻�µ�
	switch (m_linePos)
	{
	case LinePos::POS_P1:
	{
		setP1(point);
		break;
	}
	case LinePos::POS_P2:
	{
		setP2(point);
		break;
	}
	default:
		break;
	}
}

const QSizeF RoiLine::getSize()
{
	return std::move(QSize());
}

void RoiLine::transform(int nDelta)
{
	if (nDelta > 0)
	{
		setP1(p1() * SCALE);
		setP2(p2() * SCALE);
	}
	else
	{
		setP1(p1() / SCALE);
		setP2(p2() / SCALE);
	}
}

void RoiLine::resetScale(double dScale)
{
	setP1(p1() * dScale);
	setP2(p2() * dScale);
}

Roi* RoiLine::clone()
{
	return new RoiLine(*this);
}

void RoiLine::drawVertex(QPainter& painter, QPen& pen)
{
	painter.setBrush(m_procColor);

	switch (m_linePos)
	{
	case LinePos::POS_P1:
	{
		painter.drawEllipse(p2().x() - ELLIPSE * 0.5, p2().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.setBrush(Qt::yellow);
		pen.setColor(Qt::yellow);
		painter.setPen(pen);
		painter.drawEllipse(p1().x() - ELLIPSE * 0.5, p1().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		break;
	}
	case LinePos::POS_P2:
	{
		painter.drawEllipse(p1().x() - ELLIPSE * 0.5, p1().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.setBrush(Qt::yellow);
		pen.setColor(Qt::yellow);
		painter.setPen(pen);
		painter.drawEllipse(p2().x() - ELLIPSE * 0.5, p2().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		break;
	}
	default:
	{
		painter.drawEllipse(p1().x() - ELLIPSE * 0.5, p1().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(p2().x() - ELLIPSE * 0.5, p2().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		break;
	}
	}

	painter.setBrush(Qt::NoBrush);
}
