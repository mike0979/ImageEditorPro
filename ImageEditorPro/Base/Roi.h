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
	// �ƶ�ROI
	virtual void move(const QPoint& point) = 0;

	// ��ROI
	virtual void draw(QPainter& painter) = 0;

	// �жϵ��Ƿ���ROI�����ֱ����
	virtual bool isInside(const QPoint& point) = 0;

	// �ж�ROI�ĵ��ڲ���rect��
	virtual bool isInRect(const QRectF& rect) = 0;

	// �жϵ��Ƿ���ROI�����ϵĵ�
	virtual bool isRoiPoint(const QPoint& point) = 0;

	// ����ROI�����ĵ�
	virtual void setRoiPoint(const QPoint& point) = 0;

	virtual void transform(int nDelta) = 0;
	virtual void resetScale(double dScale) = 0;
	virtual const QSizeF getSize() = 0;
	virtual Roi* clone() = 0;

	// ���ô������ɫ
	virtual void setProcColor(const QColor& color);

	// ����ԭʼ��ɫ
	virtual void setOrigColor(const QColor& color);

	// ��ȡ�������ɫ
	virtual const QColor& getProcColor();

	// ��ȡԭʼ��ɫ
	virtual const QColor& getOrigColor();

	virtual void setScale(double dScale);
	virtual void drawVertex(QPainter& painter, QPen& pen) = 0;

protected:
	QColor m_procColor; // ʹ�õ���ɫ
	QColor m_origColor; // ԭʼ����ɫ
	QColor m_vertexColor; // �������ɫ
	double m_dScale;
};

#endif
