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

	// �ƶ�ROI
	void move(const QPoint& point);

	// ��ROI
	void draw(QPainter& painter);

	// �жϵ��Ƿ���ROI�����ֱ����
	bool isInside(const QPoint& point);

	// �ж�ROI�ĵ��ڲ���rect��
	bool isInRect(const QRectF& rect);

	// �жϵ��Ƿ���ROI�����ϵĵ�
	bool isRoiPoint(const QPoint& point);

	// ����ROI�����ĵ�
	virtual void setRoiPoint(const QPoint& point);

	const QSizeF getSize();
	void transform(int nDelta);
	void resetScale(double dScale);
	virtual Roi* clone();
	void drawVertex(QPainter& painter, QPen& pen);

protected:
	int m_nIndex{-1}; // ����ε�����
};

#endif