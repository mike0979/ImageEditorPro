/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: AddCommand.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-4-15
*  Description: brief
*  History: 
******************************************************************************/

#ifndef ADD_COMMAND_H
#define ADD_COMMAND_H

#include <QUndoCommand>

class Roi;

class AddCmd : public QUndoCommand
{
public:
	AddCmd(QList<Roi*>& lstRoi);

private:
	void redo() override;
	void undo() override;

private:
	QList<Roi*>& m_lstRoi;
	QList<Roi*> m_lstRedoRoi;
};

#endif