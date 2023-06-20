/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: ResizeCommand.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-15
*  Description: brief
*  History: 
******************************************************************************/

#ifndef RESIZE_COMMAND_H
#define RESIZE_COMMAND_H

#include <QUndoCommand>
#include <QPoint>

class Roi;

class ResizeCmd : public QUndoCommand
{
public:
	ResizeCmd(Roi* pRoi, const QPoint& point, const QPoint& redoPoint);

private:
	void redo() override;
	void undo() override;

private:
	Roi* m_pRoi;
	QPoint m_resizePos;
	QPoint m_redoPos;
	QPoint m_pos{0,0};
};

#endif