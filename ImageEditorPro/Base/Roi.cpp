/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: Roi.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "Roi.h"

//////////////////////////////////////////////////////////////////////////////// 
// Function: setProcColor
// Description: ���ô������ɫ
// Parameters:const QColor & color
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void Roi::setProcColor(const QColor& color)
{
	m_procColor = color;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setOrigColor
// Description: ����ԭʼ��ɫ
// Parameters:const QColor & color
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void Roi::setOrigColor(const QColor& color)
{
	m_origColor = color;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: getProcColor
// Description: ��ȡ�������ɫ
// Return: const QColor&
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
const QColor& Roi::getProcColor()
{
	return m_procColor;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: getOrigColor
// Description: ��ȡԭʼ��ɫ
// Return: const QColor&
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
const QColor& Roi::getOrigColor()
{
	return m_origColor;
}

void Roi::setScale(double dScale)
{
	m_dScale = dScale;
}
