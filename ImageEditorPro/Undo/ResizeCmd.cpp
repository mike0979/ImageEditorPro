/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: ResizeCommand.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-15
*  Description: brief
*  History: 
******************************************************************************/

#include "ResizeCmd.h"
#include "Roi.h"

ResizeCmd::ResizeCmd(Roi* pRoi, const QPoint& point, const QPoint& redoPoint)
{
	m_pRoi = pRoi;
	m_resizePos = point;
	m_redoPos = redoPoint;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: redo
// Description: ÖØ×ö
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ResizeCmd::redo()
{
	if (QPoint(0, 0) != m_pos)
	{
		m_pRoi->isRoiPoint(m_pos);
		m_pRoi->setRoiPoint(m_redoPos);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: undo
// Description: ³·Ïú
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ResizeCmd::undo()
{
	m_pRoi->isRoiPoint(m_redoPos);
	m_pRoi->setRoiPoint(m_resizePos);
	m_pos = m_resizePos;
}

