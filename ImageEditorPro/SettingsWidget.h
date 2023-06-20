/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: SetUpWidget.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-5-11
*  Description: brief
*  History: 
******************************************************************************/

#ifndef CONTRAST_WIDGET_H
#define CONTRAST_WIDGET_H

#include "ui_SettingsWidget.h"

class SettingsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsWidget(QWidget *parent = 0);
	void setValue(int nType, int nValue);
	const QMap<int, int>& getValue();

private:
	void contrastChanged(int nValue);
	void brightnessChanged(int nValue);
	void gammaChanged(int nValue);
	void redChanged(int nValue);
	void greenChanged(int nValue);
	void blueChanged(int nValue);

signals:
	void sigValueChanged(const QMap<int, int>& mapValue, int nType, int nOldValue, int nValue);

private slots: 
	// �����Աȶ�
	void onContrast(int nValue);
	void onContrast(double dValue);

	// ��������
	void onBrightness(int nValue);

	// ����Gammaֵ
	void onGamma(int nValue);
	void onGamma(double dValue);

	// ������ɫ����
	void onRed(int nValue);

	// ������ɫ����
	void onGreen(int nValue);

	// ������ɫ����
	void onBlue(int nValue);

	void onResetValue();

private:
	Ui::SettingsWidget ui;
	QMap<int, int> m_mapValue;
};

#endif