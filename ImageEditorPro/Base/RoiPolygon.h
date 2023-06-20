/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiPolygon.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-11
*  Description: brief
*  History: 
******************************************************************************/

#ifndef ROI_POLYGON_H
#define ROI_POLYGON_H

#include "Roi.h"
#include <QPolygonF>

class RoiPolygon : public Roi, public QPolygonF
{
public:
	RoiPolygon();
	RoiPolygon(const QVector<QPointF>& vecPoints);
	virtual ~RoiPolygon();

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
	virtual void setRoiPoint(const QPoint& point);

	const QSizeF getSize();
	void transform(int nDelta);
	void resetScale(double dScale);
	virtual Roi* clone();
	void drawVertex(QPainter& painter, QPen& pen);

protected:
	int m_nIndex{-1}; // 多边形点的序号
};

#endif