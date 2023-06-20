/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: MoveCommand.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-15
*  Description: brief
*  History: 
******************************************************************************/

#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <QUndoCommand>
#include <QPoint>

class Roi;

class MoveCmd : public QUndoCommand
{
public:
	MoveCmd(Roi* pRoi, const QPoint& dis);

private:
	void redo() override;
	void undo() override;

private:
	Roi* m_pRoi;
	QPoint m_dis;
	QPoint m_redoDis;
};

#endif