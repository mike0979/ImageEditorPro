/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiPolyline.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "RoiPolyline.h"
#include "Define.h"

RoiPolyline::RoiPolyline(const QVector<QPointF>& vecPoints) : RoiPolygon(vecPoints)
{

}

RoiPolyline::RoiPolyline() : RoiPolygon()
{

}

//////////////////////////////////////////////////////////////////////////////// 
// Function: draw
// Description: »­ROI
// Parameters:QPainter & painter
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void RoiPolyline::draw(QPainter& painter)
{
	QPen pen = painter.pen();
	pen.setColor(m_procColor);
	painter.setPen(pen);
	painter.drawPolyline(*this);

	if (m_bDrawEllipse)
	{
		RoiPolygon::drawVertex(painter, pen);
	}
}

void RoiPolyline::setDrawEllipse(bool bDrawEllipse)
{
	m_bDrawEllipse = bDrawEllipse;
}

Roi* RoiPolyline::clone()
{
	return new RoiPolyline(*this);
}
