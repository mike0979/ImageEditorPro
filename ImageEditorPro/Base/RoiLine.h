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

// ��ʶ���ֱ�ߵ�������
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

	// �ƶ�ROI
	void move(const QPoint& point);

	// ��ROI
	virtual void draw(QPainter& painter);

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
	Roi* clone();
	void drawVertex(QPainter& painter, QPen& pen);

private:
	LinePos m_linePos; // ���ֱ�ߵĵ�
};

#endif