/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiLine.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-11
*  Description: brief
*  History: 
******************************************************************************/

#ifndef ROI_LINT_H
#define ROI_LINT_H

#include "Roi.h"
#include <QLineF>

// 标识组成直线的两个点
enum class LinePos
{
	POS_NULL,
	POS_P1,
	POS_P2
};

class RoiLine : public Roi, public QLineF
{
public:
	RoiLine(const QPointF& point1, const QPointF& point2);
	virtual ~RoiLine();

	// 移动ROI
	void move(const QPoint& point);

	// 画ROI
	virtual void draw(QPainter& painter);

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
	Roi* clone();
	void drawVertex(QPainter& painter, QPen& pen);

private:
	LinePos m_linePos; // 组成直线的点
};

#endif