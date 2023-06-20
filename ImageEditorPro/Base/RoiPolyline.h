/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiPolyline.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-11
*  Description: brief
*  History: 
******************************************************************************/

#ifndef ROI_POLYLINE_H
#define ROI_POLYLINE_H

#include "RoiPolygon.h"

class RoiPolyline : public RoiPolygon
{
public:
	RoiPolyline();
	RoiPolyline(const QVector<QPointF>& vecPoints);

	// »­ROI
	virtual void draw(QPainter& painter);
	void setDrawEllipse(bool bDrawEllipse);
	Roi* clone();

private:
	bool m_bDrawEllipse{false};
};

#endif