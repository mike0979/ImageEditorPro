/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiRect.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-11
*  Description: brief
*  History: 
******************************************************************************/

#ifndef ROI_RECT_H
#define ROI_RECT_H

#include "Roi.h"
#include <QRectF>

// 矩形的四个角点位置
enum class RectPos
{
	POS_NULL,
	POS_TOP_LEFT,
	POS_TOP_RIGHT,
	POS_BOTTOM_LEFT,
	POS_BOTTOM_RIGHT
};

class RoiRect : public Roi, public QRectF
{
public:
	RoiRect(const QPointF& point1, const QPointF& point2);
	virtual ~RoiRect();

	// 移动ROI
	void move(const QPoint& point);

	// 画ROI
	void draw(QPainter& painter);

	// 判断点是否在ROI里或在直线上
	bool isInside(const QPoint& point);

	// 判断ROI的点在不在rect里
	bool isInRect(const QRectF& rect);

	// 判断点是否是ROI轮廓上的点
	bool isRoiPoint(const QPoint& point);

	// 设置ROI轮廓的点
	void setRoiPoint(const QPoint& point);

	const QSizeF getSize();
	void transform(int nDelta);
	void resetScale(double dScale);
	virtual Roi* clone();
	void drawVertex(QPainter& painter, QPen& pen);

protected:
	RectPos m_rectPos; // 角点位置
};

#endif