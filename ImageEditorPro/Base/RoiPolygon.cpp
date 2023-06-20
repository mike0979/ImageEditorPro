/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiPolygon.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "RoiPolygon.h"
#include "Utils.h"
#include "Define.h"

using namespace utilfunc;

RoiPolygon::RoiPolygon(const QVector<QPointF>& vecPoints) : QPolygonF(vecPoints)
{

}

RoiPolygon::RoiPolygon() : QPolygonF()
{

}

RoiPolygon::~RoiPolygon()
{

}

//////////////////////////////////////////////////////////////////////////////// 
// Function: move
// Description: �ƶ�ROI
// Parameters:const QPoint & point
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiPolygon::move(const QPoint& point)
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
void RoiPolygon::draw(QPainter& painter)
{
	QPen pen = painter.pen();
	pen.setColor(m_procColor);
	painter.setPen(pen);
	painter.drawPolygon(*this);
	drawVertex(painter, pen);
}


//////////////////////////////////////////////////////////////////////////////// 
// Function: isInside
// Description: �жϵ��Ƿ���ROI�����ֱ����
// Parameters:const QPoint & point
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiPolygon::isInside(const QPoint& point)
{
	return containsPoint(point, Qt::WindingFill);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isInRect
// Description: �ж�ROI�ĵ��ڲ���rect��
// Parameters:const QRect & rect
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiPolygon::isInRect(const QRectF& rect)
{
	return rect.contains(boundingRect());
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isRoiPoint
// Description: �жϵ��Ƿ���ROI�����ϵĵ�
// Parameters:const QPoint & point
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiPolygon::isRoiPoint(const QPoint& point)
{
	// ������¶���������ĵ㣬�ͼ��µ�����
	for (size_t i = 0; i < size(); i++)
	{
		if (Point2PointDis((*this)[i], point) <= MIN_DISTANCE * MIN_DISTANCE)
		{
			m_nIndex = i;
			return true;
		}
	}

	m_nIndex = -1;
	return false;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setRoiPoint
// Description: ����ROI�����ĵ�
// Parameters:const QPoint & point
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiPolygon::setRoiPoint(const QPoint& point)
{
	(*this)[m_nIndex] = point;
}

const QSizeF RoiPolygon::getSize()
{
	return std::move(boundingRect().size());
}

void RoiPolygon::transform(int nDelta)
{
	for (size_t i = 0; i < size(); i++)
	{
		if (nDelta > 0)
		{
			(*this)[i] *= SCALE;
		}
		else
		{
			(*this)[i] /= SCALE;
		}
	}
}

void RoiPolygon::resetScale(double dScale)
{
	for (size_t i = 0; i < size(); i++)
	{
		(*this)[i] *= dScale;
	}
}

Roi* RoiPolygon::clone()
{
	return new RoiPolygon(*this);
}

void RoiPolygon::drawVertex(QPainter& painter, QPen& pen)
{
	painter.setBrush(m_procColor);

	for (size_t i = 0; i < size(); i++)
	{
		if (i == m_nIndex)
		{
			painter.setBrush(Qt::yellow);
			pen.setColor(Qt::yellow);
			painter.setPen(pen);
			painter.drawEllipse((*this)[i].x() - ELLIPSE * 0.5, (*this)[i].y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
			painter.setBrush(m_procColor);
			pen.setColor(m_procColor);
			painter.setPen(pen);
		}
		else
		{
			painter.drawEllipse((*this)[i].x() - ELLIPSE * 0.5, (*this)[i].y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		}
	}

	painter.setBrush(Qt::NoBrush);
}
