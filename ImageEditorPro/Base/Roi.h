/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: Roi.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-11
*  Description: brief
*  History: 
******************************************************************************/

#ifndef ROI_H
#define ROI_H

#include <QPainter>
#include <QPoint>

class Roi
{
public:
	// 移动ROI
	virtual void move(const QPoint& point) = 0;

	// 画ROI
	virtual void draw(QPainter& painter) = 0;

	// 判断点是否在ROI里或在直线上
	virtual bool isInside(const QPoint& point) = 0;

	// 判断ROI的点在不在rect里
	virtual bool isInRect(const QRectF& rect) = 0;

	// 判断点是否是ROI轮廓上的点
	virtual bool isRoiPoint(const QPoint& point) = 0;

	// 设置ROI轮廓的点
	virtual void setRoiPoint(const QPoint& point) = 0;

	virtual void transform(int nDelta) = 0;
	virtual void resetScale(double dScale) = 0;
	virtual const QSizeF getSize() = 0;
	virtual Roi* clone() = 0;

	// 设置处理的颜色
	virtual void setProcColor(const QColor& color);

	// 设置原始颜色
	virtual void setOrigColor(const QColor& color);

	// 获取处理的颜色
	virtual const QColor& getProcColor();

	// 获取原始颜色
	virtual const QColor& getOrigColor();

	virtual void setScale(double dScale);
	virtual void drawVertex(QPainter& painter, QPen& pen) = 0;

protected:
	QColor m_procColor; // 使用的颜色
	QColor m_origColor; // 原始的颜色
	QColor m_vertexColor; // 顶点的颜色
	double m_dScale;
};

#endif
