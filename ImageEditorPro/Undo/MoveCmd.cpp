/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: MoveCommand.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-15
*  Description: brief
*  History: 
******************************************************************************/

#include "MoveCmd.h"
#include "Roi.h"

MoveCmd::MoveCmd(Roi* pRoi, const QPoint& dis)
{
	m_pRoi = pRoi;
	m_dis = dis;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: redo
// Description: ÖØ×ö
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void MoveCmd::redo()
{
	m_pRoi->move(m_redoDis);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: undo
// Description: ³·Ïú
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void MoveCmd::undo()
{
	m_pRoi->move(-m_dis);
	m_redoDis = m_dis;
}

