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

// ���ε��ĸ��ǵ�λ��
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
	void setRoiPoint(const QPoint& point);

	const QSizeF getSize();
	void transform(int nDelta);
	void resetScale(double dScale);
	virtual Roi* clone();
	void drawVertex(QPainter& painter, QPen& pen);

protected:
	RectPos m_rectPos; // �ǵ�λ��
};

#endif