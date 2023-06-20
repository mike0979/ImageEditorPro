/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiRect.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "RoiRect.h"
#include "Utils.h"
#include "Define.h"

using namespace utilfunc;

RoiRect::RoiRect(const QPointF& point1, const QPointF& point2) : QRectF(point1, point2)
{

}

RoiRect::~RoiRect()
{

}

//////////////////////////////////////////////////////////////////////////////// 
// Function: move
// Description: 移动ROI
// Parameters:const QPoint & point
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiRect::move(const QPoint& point)
{
	translate(point);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: draw
// Description: 画ROI
// Parameters:QPainter & painter
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiRect::draw(QPainter& painter)
{
	QPen pen = painter.pen();
	pen.setColor(m_procColor);
	painter.setPen(pen);
	painter.drawRect(*this);
	drawVertex(painter, pen);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isInside
// Description: 判断点是否在ROI里或在直线上
// Parameters:const QPoint & point
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiRect::isInside(const QPoint& point)
{
	return contains(point);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isInRect
// Description: 判断ROI的点在不在rect里
// Parameters:const QRect & rect
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiRect::isInRect(const QRectF& rect)
{
	return rect.contains(*this);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isRoiPoint
// Description: 判断点是否是ROI轮廓上的点
// Parameters:const QPoint & point
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool RoiRect::isRoiPoint(const QPoint& point)
{
	// 如果是矩形轮廓上的边角点就记下点的位置
	if (Point2PointDis(bottomLeft(), point) <= MIN_DISTANCE * MIN_DISTANCE)
	{
		m_rectPos = RectPos::POS_BOTTOM_LEFT;
		return true;
	}
	else if (Point2PointDis(bottomRight(), point) <= MIN_DISTANCE * MIN_DISTANCE)
	{
		m_rectPos = RectPos::POS_BOTTOM_RIGHT;
		return true;
	}
	else if (Point2PointDis(topLeft(), point) <= MIN_DISTANCE * MIN_DISTANCE)
	{
		m_rectPos = RectPos::POS_TOP_LEFT;
		return true;
	}
	else if (Point2PointDis(topRight(), point) <= MIN_DISTANCE * MIN_DISTANCE)
	{
		m_rectPos = RectPos::POS_TOP_RIGHT;
		return true;
	}
	else
	{
		m_rectPos = RectPos::POS_NULL;
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setRoiPoint
// Description: 设置ROI轮廓的点
// Parameters:const QPoint & point
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiRect::setRoiPoint(const QPoint& point)
{
	// 根据点的位置替换新点
	switch (m_rectPos)
	{
	case RectPos::POS_BOTTOM_LEFT:
	{
		setBottomLeft(point);
		break;
	}
	case RectPos::POS_BOTTOM_RIGHT:
	{
		setBottomRight(point);
		break;
	}
	case RectPos::POS_TOP_LEFT:
	{
		setTopLeft(point);
		break;
	}
	case RectPos::POS_TOP_RIGHT:
	{
		setTopRight(point);
		break;
	}
	default:
		break;
	}
}

const QSizeF RoiRect::getSize()
{
	return std::move(size());
}

void RoiRect::transform(int nDelta)
{
	if (nDelta > 0)
	{
		setTopLeft(topLeft() * SCALE);
		setBottomRight(bottomRight() * SCALE);
	}
	else
	{
		setTopLeft(topLeft() / SCALE);
		setBottomRight(bottomRight() / SCALE);
	}
}

void RoiRect::resetScale(double dScale)
{
	setTopLeft(topLeft() * dScale);
	setBottomRight(bottomRight() * dScale);
}

Roi* RoiRect::clone()
{
	return new RoiRect(*this);
}

void RoiRect::drawVertex(QPainter& painter, QPen& pen)
{
	painter.setBrush(m_procColor);

	switch (m_rectPos)
	{
	case RectPos::POS_BOTTOM_LEFT:
	{
		painter.drawEllipse(topLeft().x() - ELLIPSE * 0.5, topLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(topRight().x() - ELLIPSE * 0.5, topRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(bottomRight().x() - ELLIPSE * 0.5, bottomRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);

		pen.setColor(Qt::yellow);
		painter.setPen(pen);
		painter.setBrush(Qt::yellow);
		painter.drawEllipse(bottomLeft().x() - ELLIPSE * 0.5, bottomLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		break;
	}
	case RectPos::POS_BOTTOM_RIGHT:
	{
		painter.drawEllipse(topLeft().x() - ELLIPSE * 0.5, topLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(topRight().x() - ELLIPSE * 0.5, topRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(bottomLeft().x() - ELLIPSE * 0.5, bottomLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);

		pen.setColor(Qt::yellow);
		painter.setPen(pen);
		painter.setBrush(Qt::yellow);
		painter.drawEllipse(bottomRight().x() - ELLIPSE * 0.5, bottomRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		break;
	}
	case RectPos::POS_TOP_LEFT:
	{
		painter.drawEllipse(topRight().x() - ELLIPSE * 0.5, topRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(bottomLeft().x() - ELLIPSE * 0.5, bottomLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(bottomRight().x() - ELLIPSE * 0.5, bottomRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);

		pen.setColor(Qt::yellow);
		painter.setPen(pen);
		painter.setBrush(Qt::yellow);
		painter.drawEllipse(topLeft().x() - ELLIPSE * 0.5, topLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		break;
	}
	case RectPos::POS_TOP_RIGHT:
	{
		painter.drawEllipse(topLeft().x() - ELLIPSE * 0.5, topLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(bottomLeft().x() - ELLIPSE * 0.5, bottomLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(bottomRight().x() - ELLIPSE * 0.5, bottomRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		pen.setColor(Qt::yellow);
		painter.setPen(pen);
		painter.setBrush(Qt::yellow);
		painter.drawEllipse(topRight().x() - ELLIPSE * 0.5, topRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		break;
	}
	default:
	{
		painter.setBrush(m_procColor);
		painter.drawEllipse(topRight().x() - ELLIPSE * 0.5, topRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(topLeft().x() - ELLIPSE * 0.5, topLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(bottomLeft().x() - ELLIPSE * 0.5, bottomLeft().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		painter.drawEllipse(bottomRight().x() - ELLIPSE * 0.5, bottomRight().y() - ELLIPSE * 0.5, ELLIPSE, ELLIPSE);
		break;
	}
	}

	painter.setBrush(Qt::NoBrush);
}
