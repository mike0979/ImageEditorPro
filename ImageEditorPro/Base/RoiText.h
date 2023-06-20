/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: RoiText.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-13
*  Description: brief
*  History: 
******************************************************************************/

#ifndef ROI_TEXT_H
#define ROI_TEXT_H

#include "RoiRect.h"

class RoiText : public RoiRect
{
public:
	RoiText(const QPointF& point1, const QPointF& point2);
	void setText(QString&& strText);
	const QString& getText();
	void draw(QPainter& painter);
	Roi* clone();
	int getFontSize();

private:
	QString m_strText;
	int m_nFontSize;
	int m_nMaxFontSize;
};

#endif