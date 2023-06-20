/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: SetUpWidget.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-5-11
*  Description: brief
*  History: 
******************************************************************************/

#include "SettingsWidget.h"
#include "Define.h"

SettingsWidget::SettingsWidget(QWidget *parent /*= 0*/) : QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.doubleSpinBoxContrast, SIGNAL(valueChanged(double)), this, SLOT(onContrast(double)));
	connect(ui.horSliderContrast, SIGNAL(sliderMoved(int)), this, SLOT(onContrast(int)));
	connect(ui.horSliderRed, SIGNAL(sliderMoved(int)), this, SLOT(onRed(int)));
	connect(ui.spinBoxRed, SIGNAL(valueChanged(int)), this, SLOT(onRed(int)));
	connect(ui.spinBoxGreen, SIGNAL(valueChanged(int)), this, SLOT(onGreen(int)));
	connect(ui.horSliderGreen, SIGNAL(sliderMoved(int)), this, SLOT(onGreen(int)));
	connect(ui.spinBoxBlue, SIGNAL(valueChanged(int)), this, SLOT(onBlue(int)));
	connect(ui.horSliderBlue, SIGNAL(sliderMoved(int)), this, SLOT(onBlue(int)));
	connect(ui.horSliderGamma, SIGNAL(sliderMoved(int)), this, SLOT(onGamma(int)));
	connect(ui.doubleSpinBoxGamma, SIGNAL(valueChanged(double)), this, SLOT(onGamma(double)));
	connect(ui.spinBoxBrightness, SIGNAL(valueChanged(int)), this, SLOT(onBrightness(int)));
	connect(ui.horSliderBrightness, SIGNAL(sliderMoved(int)), this, SLOT(onBrightness(int)));

	m_mapValue[TYPE_GAMMA] = 10;
	m_mapValue[TYPE_CONTRAST] = 10;
	m_mapValue[TYPE_BRIGHTNESS] = 0;
	m_mapValue[TYPE_RED] = 0;
	m_mapValue[TYPE_GREEN] = 0;
	m_mapValue[TYPE_BLUE] = 0;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onContrast
// Description: 调整对比度
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onContrast(int nValue)
{
	if (m_mapValue[TYPE_CONTRAST] != nValue)
	{
		int nOldContrast = m_mapValue[TYPE_CONTRAST];
		contrastChanged(nValue);
		emit sigValueChanged(m_mapValue, TYPE_CONTRAST, nOldContrast, m_mapValue[TYPE_CONTRAST]);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onContrast
// Description: 调整对比度
// Parameters:double dValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onContrast(double dValue)
{
	if (m_mapValue[TYPE_CONTRAST] != static_cast<int>(dValue * 10))
	{
		int nOldContrast = m_mapValue[TYPE_CONTRAST];
		m_mapValue[TYPE_CONTRAST] = dValue * 10;
		ui.doubleSpinBoxContrast->setValue(dValue);
		ui.horSliderContrast->setValue(static_cast<int>(m_mapValue[TYPE_CONTRAST]));
		m_mapValue[TYPE_CONTRAST] = m_mapValue[TYPE_CONTRAST];
		emit sigValueChanged(m_mapValue, TYPE_CONTRAST, nOldContrast, m_mapValue[TYPE_CONTRAST]);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: contrastChanged
// Description: 对比度变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::contrastChanged(int nValue)
{
	m_mapValue[TYPE_CONTRAST] = nValue;
	ui.doubleSpinBoxContrast->setValue(nValue * 0.1);
	ui.horSliderContrast->setValue(nValue);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onBrightness
// Description: 亮度发生变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onBrightness(int nValue)
{
	if (m_mapValue[TYPE_BRIGHTNESS] != nValue)
	{
		int nOldBrightness = m_mapValue[TYPE_BRIGHTNESS];
		brightnessChanged(nValue);
		emit sigValueChanged(m_mapValue, TYPE_BRIGHTNESS, nOldBrightness, m_mapValue[TYPE_BRIGHTNESS]);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: brightnessChanged
// Description: 亮度发生变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::brightnessChanged(int nValue)
{
	m_mapValue[TYPE_BRIGHTNESS] = nValue;
	ui.spinBoxBrightness->setValue(nValue);
	ui.horSliderBrightness->setValue(nValue);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onGammaChanged
// Description: 调整Gamma值
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onGamma(int nValue)
{
	if (m_mapValue[TYPE_GAMMA] != nValue)
	{
		int nOldGamma = m_mapValue[TYPE_GAMMA];
		gammaChanged(nValue);
		emit sigValueChanged(m_mapValue, TYPE_GAMMA, nOldGamma, m_mapValue[TYPE_GAMMA]);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onGammaChanged
// Description: 调整Gamma值
// Parameters:double dValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onGamma(double dValue)
{
	if (m_mapValue[TYPE_GAMMA] != static_cast<int>(dValue * 10))
	{
		int nOldGamma = m_mapValue[TYPE_GAMMA];
		m_mapValue[TYPE_GAMMA] = dValue * 10;
		ui.doubleSpinBoxGamma->setValue(dValue);
		ui.horSliderGamma->setValue(static_cast<int>(dValue * 10));
		m_mapValue[TYPE_GAMMA] = m_mapValue[TYPE_GAMMA];
		emit sigValueChanged(m_mapValue, TYPE_GAMMA, nOldGamma, m_mapValue[TYPE_GAMMA]);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: gammaChanged
// Description: Gamma值发生变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::gammaChanged(int nValue)
{
	m_mapValue[TYPE_GAMMA] = nValue;
	ui.doubleSpinBoxGamma->setValue(nValue * 0.1);
	ui.horSliderGamma->setValue(nValue);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: redChanged
// Description: 红色分量变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::redChanged(int nValue)
{
	m_mapValue[TYPE_RED] = nValue;
	ui.spinBoxRed->setValue(nValue);
	ui.horSliderRed->setValue(nValue);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onRed
// Description: 红色分量变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onRed(int nValue)
{
	if (m_mapValue[TYPE_RED] != nValue)
	{
		int nOldRed = m_mapValue[TYPE_RED];
		redChanged(nValue);
		emit sigValueChanged(m_mapValue, TYPE_RED, nOldRed, m_mapValue[TYPE_RED]);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onGreen
// Description: 绿色分量变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onGreen(int nValue)
{
	if (m_mapValue[TYPE_GREEN] != nValue)
	{
		int nOldGreen = m_mapValue[TYPE_GREEN];
		greenChanged(nValue);
		emit sigValueChanged(m_mapValue, TYPE_GREEN, nOldGreen, m_mapValue[TYPE_GREEN]);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: greenChanged
// Description: 绿色分量变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::greenChanged(int nValue)
{
	m_mapValue[TYPE_GREEN] = nValue;
	ui.spinBoxGreen->setValue(nValue);
	ui.horSliderGreen->setValue(nValue);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onBlue
// Description: 蓝色分量变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onBlue(int nValue)
{
	if (m_mapValue[TYPE_BLUE] != nValue)
	{
		int nOldBlue = m_mapValue[TYPE_BLUE];
		blueChanged(nValue);
		emit sigValueChanged(m_mapValue, TYPE_BLUE, nOldBlue, m_mapValue[TYPE_BLUE]);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: blueChanged
// Description: 蓝色分量发生变化
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::blueChanged(int nValue)
{
	m_mapValue[TYPE_BLUE] = nValue;
	ui.spinBoxBlue->setValue(nValue);
	ui.horSliderBlue->setValue(nValue);
}

void SettingsWidget::setValue(int nType, int nValue)
{
	switch (nType)
	{
	case TYPE_GAMMA:
	{
		gammaChanged(nValue);
		break;
	}
	case TYPE_CONTRAST:
	{
		contrastChanged(nValue);
		break;
	}
	case TYPE_BRIGHTNESS:
	{
		brightnessChanged(nValue);
		break;
	}
	case TYPE_BLUE:
	{
		blueChanged(nValue);
		break;
	}
	case TYPE_GREEN:
	{
		greenChanged(nValue);
		break;
	}
	case TYPE_RED:
	{
		redChanged(nValue);
		break;
	}
	default:
		break;
	}
}

const QMap<int, int>& SettingsWidget::getValue()
{
	return m_mapValue;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: resetValue
// Description: 重置
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void SettingsWidget::onResetValue()
{
	contrastChanged(10);
	gammaChanged(10);
	brightnessChanged(0);
	redChanged(0);
	greenChanged(0);
	blueChanged(0);
}