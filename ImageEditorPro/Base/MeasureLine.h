/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: MeasureLine.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-22
*  Description: brief
*  History: 
******************************************************************************/

#ifndef MEASURE_LINE_H
#define MEASURE_LINE_H

#include "RoiLine.h"

class MeasureLine : public RoiLine
{
public:
	MeasureLine(const QPoint& point1, const QPoint& point2);
	void draw(QPainter& painter);
	void setShowFlag();

private:
	QPolygonF m_arrow1;
	QPolygonF m_arrow2;
	QLineF m_line1;
	QLineF m_line2;
	QPoint m_lenPos;
	bool m_bShowAll{false};
};

#endif
