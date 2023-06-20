/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: MeasureAngle.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-22
*  Description: brief
*  History: 
******************************************************************************/

#ifndef MEASURE_ANGLE_H
#define MEASURE_ANGLE_H

#include "RoiPolyline.h"

class MeasureAngle : public RoiPolyline
{
public:
	MeasureAngle(const QVector<QPointF>& vecPoints);
	void setRoiPoint(const QPoint& point);
	void draw(QPainter& painter);

private:
	const QPointF& getTextPos();

private:
	qreal m_angle{0};
	qreal m_angle1{ 0 };
	qreal m_angle2{ -90 * 16 };
	qreal m_curAngle{0};
	qreal m_curAngle1{ 0 };
	qreal m_curAngle2{ 0 };
	QPointF m_textPos;
};

#endif
