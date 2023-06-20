/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: AddCommand.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-15
*  Description: brief
*  History: 
******************************************************************************/

#include "AddCmd.h"

AddCmd::AddCmd(QList<Roi*>& lstRoi) : m_lstRoi(lstRoi)
{

}

//////////////////////////////////////////////////////////////////////////////// 
// Function: redo
// Description: ÖØ×ö
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void AddCmd::redo()
{
	if (m_lstRedoRoi.size() > 0)
	{
		auto roi = m_lstRedoRoi.takeFirst();
		m_lstRoi.push_back(roi);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: undo
// Description: ³·Ïú
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void AddCmd::undo()
{
	auto roi = m_lstRoi.back();
	m_lstRedoRoi.push_back(roi);

	if (m_lstRoi.size() > 0)
	{
		m_lstRoi.pop_back();
	}
}

