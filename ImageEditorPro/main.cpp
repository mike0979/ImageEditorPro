/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: main.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "ImageEditorPro.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>

#define ERROR_CODE -1

#define WINDOW_COLOR QColor(37, 37, 38)
#define WINDOW_TEXT_COLOR QColor(241, 241, 241)
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    QPalette palette;
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    palette.setBrush(QPalette::Window, QBrush(WINDOW_COLOR));//vs灰
    palette.setBrush(QPalette::Text, QBrush(WINDOW_TEXT_COLOR));//vs文字色
    palette.setBrush(QPalette::ToolTipText, QBrush(WINDOW_TEXT_COLOR));//vs文字色
    palette.setBrush(QPalette::HighlightedText, QBrush(WINDOW_TEXT_COLOR));//vs文字色
    palette.setBrush(QPalette::WindowText, QBrush(WINDOW_TEXT_COLOR));//vs文字色
    palette.setBrush(QPalette::ButtonText, QBrush(WINDOW_TEXT_COLOR));//vs文字色
    palette.setBrush(QPalette::Button, QBrush(WINDOW_COLOR));//vs灰
    palette.setBrush(QPalette::Base, QBrush(QColor(80, 80, 80)));
    palette.setBrush(QPalette::AlternateBase, QBrush(QColor(40, 40, 40)));
    palette.setBrush(QPalette::Disabled, QPalette::Button, QBrush(QColor(60, 60, 60)));
    palette.setBrush(QPalette::Active, QPalette::Button, QBrush(QColor(40, 40, 40)));
    palette.setBrush(QPalette::Inactive, QPalette::Highlight, QBrush(QColor(40, 40, 40)));

    QApplication::setPalette(palette);

	ImageEditorPro w;
	bool bRet = w.init();
	if (!bRet)
	{
		return ERROR_CODE;
	}

	w.show();
	return a.exec();
}
