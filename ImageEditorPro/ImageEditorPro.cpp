/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: ImageProcess.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "ImageEditorPro.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QTextEdit>
#include "SettingsWidget.h"
#include "Utils.h"

using namespace utilfunc;

ImageEditorPro::ImageEditorPro(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.customplot->xAxis->setVisible(false);
	ui.customplot->xAxis2->setVisible(true);
	ui.customplot->yAxis->setRangeReversed(true);
	ui.customplot->yAxis->setTickLabelSide(QCPAxis::LabelSide::lsOutside);
	ui.customplot->xAxis2->setTickLabelSide(QCPAxis::LabelSide::lsOutside);
	ui.customplot->xAxis2->grid()->setVisible(false);
	ui.customplot->yAxis->grid()->setVisible(false);

	ui.customplot->xAxis2->setTickLengthIn(-ui.customplot->xAxis2->tickLengthIn());
	ui.customplot->xAxis2->setSubTickLengthIn(-ui.customplot->xAxis2->subTickLengthIn());
	ui.customplot->yAxis->setTickLengthIn(-ui.customplot->yAxis->tickLengthIn());
	ui.customplot->yAxis->setSubTickLengthIn(-ui.customplot->yAxis->subTickLengthIn());
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: init
// Description: 初始化
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool ImageEditorPro::init()
{
	m_setUpWidget = std::make_shared<SettingsWidget>();
	bool bRet = connectSignals();

	if (!bRet)
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: connectSignals
// Description: 链接信号
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool ImageEditorPro::connectSignals()
{
	bool bRet = true;
	bRet &= (bool)connect(ui.pBtnGray, SIGNAL(clicked()), this, SLOT(onBtnGray()));
    bRet &= (bool)connect(ui.pBtnClear, SIGNAL(clicked()), this, SLOT(onBtnClear()));
    bRet &= (bool)connect(ui.pBtnOpen, SIGNAL(clicked()), this, SLOT(onLoadin()));
    bRet &= (bool)connect(ui.pBtnRestore, SIGNAL(clicked()), this, SLOT(onBtnRestore()));
    bRet &= (bool)connect(ui.pBtnNegative, SIGNAL(clicked()), this, SLOT(onBtnNeagtive()));
    bRet &= (bool)connect(ui.pBtnColor, SIGNAL(clicked()), this, SLOT(onFrameColor()));
    bRet &= (bool)connect(ui.pBtnSave, SIGNAL(clicked()), this, SLOT(onSave()));
    bRet &= (bool)connect(ui.pBtnPolyline, SIGNAL(clicked()), this, SLOT(onRoiPolyline()));
    bRet &= (bool)connect(ui.pBtnLine, SIGNAL(clicked()), this, SLOT(onRoiLine()));
    bRet &= (bool)connect(ui.pBtnChoose, SIGNAL(clicked()), this, SLOT(onChoose()));
    bRet &= (bool)connect(ui.pBtnRect, SIGNAL(clicked()), this, SLOT(onRoiRect()));
    bRet &= (bool)connect(ui.pBtnPolygon, SIGNAL(clicked()), this, SLOT(onRoiPolygon()));
    bRet &= (bool)connect(ui.pBtnUndo, SIGNAL(clicked()), this, SLOT(onUndo()));
    bRet &= (bool)connect(ui.pBtnRedo, SIGNAL(clicked()), this, SLOT(onRedo()));
    bRet &= (bool)connect(ui.pBtnMeasureLine, SIGNAL(clicked()), this, SLOT(onMeasureLen()));
    bRet &= (bool)connect(ui.pBtnMeasureAngle, SIGNAL(clicked()), this, SLOT(onMeasureAngle()));
	bRet &= (bool)connect(ui.pBtnSmooth, SIGNAL(clicked()), this, SLOT(onSmooth()));
	bRet &= (bool)connect(ui.pBtnSharpen, SIGNAL(clicked()), this, SLOT(onSharpen()));
	bRet &= (bool)connect(ui.pBtnEdgeExtract, SIGNAL(clicked()), this, SLOT(onEdgeExtract()));
    bRet &= (bool)connect(ui.pBtnSetUp, SIGNAL(clicked()), this, SLOT(onSetUp()));
	bRet &= (bool)connect(ui.pBtnText, SIGNAL(clicked()), this, SLOT(onText()));
	bRet &= (bool)connect(m_setUpWidget.get(), SIGNAL(sigValueChanged(const QMap<int, int>&, int, int, int)), 
		this, SLOT(onValueChanged(const QMap<int, int>&, int, int, int)));
	bRet &= (bool)connect(this, SIGNAL(sigResetValue()), m_setUpWidget.get(), SLOT(onResetValue()));
	bRet &= (bool)connect(ui.labelDisplay, SIGNAL(sigScaleChanged(double)), this, SLOT(onScaleChanged(double)));
	return bRet;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: process
// Description: 参数调整处理函数
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::process(const QMap<int, int>& mapValue)
{
	ImgProc(m_cacheMat, m_cvMat, mapValue[TYPE_CONTRAST] * 0.1, mapValue[TYPE_BRIGHTNESS] * 1.0);
	ChangeRgb(m_cvMat, m_cvMat, CHANNEL_RED, mapValue[TYPE_RED]);
	ChangeRgb(m_cvMat, m_cvMat, CHANNEL_GREEN, mapValue[TYPE_GREEN]);
	ChangeRgb(m_cvMat, m_cvMat, CHANNEL_BLUE, mapValue[TYPE_BLUE]);
	GammaCorrection(m_cvMat, mapValue[TYPE_GAMMA] * 0.1);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onLoadinClicked
// Description: 加载图片
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onLoadin()
{
	QString strFileName;
	strFileName = QFileDialog::getOpenFileName(this, QStringLiteral("选择图像"), "", "Images (*.png *.bmp *.jpg *.tif *.GIF )");

	// 如果文件名是空的就返回，否则加载图片
	if (strFileName.isEmpty())
	{
		return;
	}
	else
	{
		cv::Mat mat = cv::imread(strFileName.toLocal8Bit().data());
		if (mat.empty())
		{
			QMessageBox::information(this, QStringLiteral("打开图像"), QStringLiteral("打开图像失败!"));
			return;
		}

		m_cvMat = mat.clone();
		m_origMat = mat.clone();
		m_cacheMat = mat.clone();
		emit sigResetValue();
		ui.labelDisplay->setOrigImage(mat, true, TYPE_NULL);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onBtnGrayClicked
// Description: 灰度处理
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onBtnGray()
{
	if (m_cvMat.empty())
	{
		return;
	}

	cv::Mat imgGray;
	cv::cvtColor(m_cvMat, imgGray, cv::COLOR_BGR2GRAY);
	cv::cvtColor(imgGray, m_cacheMat, cv::COLOR_GRAY2BGR);
	m_cvMat = m_cacheMat.clone();
	ui.labelDisplay->setOrigImage(m_cacheMat, false, TYPE_GRAY);
	emit sigResetValue();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onBtnClearClicked
// Description: 清除ROI
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onBtnClear()
{
	ui.labelDisplay->clearShape();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onBtnRestoreClicked
// Description: 恢复原图
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onBtnRestore()
{
	emit sigResetValue();
	m_cvMat = m_origMat.clone();
	m_cacheMat = m_origMat.clone();
	ui.labelDisplay->clearRoi();
	ui.labelDisplay->setOrigImage(m_origMat);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onBtnNeagtiveClicked
// Description:负图像 
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onBtnNeagtive()
{
	if (m_cvMat.empty())
	{
		return;
	}

	m_cacheMat = ~m_cvMat;
	m_cvMat = m_cacheMat.clone();
	ui.labelDisplay->setOrigImage(m_cacheMat, false, TYPE_NEAGTIVE);
	emit sigResetValue();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onSetUp
// Description: 点击设置
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onSetUp()
{
	m_setUpWidget->show();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onValueChanged
// Description: 当有数值变化时
// Parameters:const QMap<int, int> & mapValue
// Parameters:int nType
// Parameters:int nOldValue
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onValueChanged(const QMap<int, int>& mapValue, int nType, int nOldValue, int nValue)
{
	process(mapValue);
	ui.labelDisplay->setOrigImage(m_cvMat, false, nType, nOldValue, nValue);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onFrameColorClicked
// Description: 设置画框颜色
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onFrameColor()
{
	QColor color = QColorDialog::getColor(Qt::red, this, QStringLiteral("画框颜色"));
	ui.labelDisplay->setFrameColor(color);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onRoiPen
// Description: 绘制曲线
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onRoiPolyline()
{
	this->ui.labelDisplay->setOperType(OperateType::TYPE_POLYLINE);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onRoiLine
// Description: 绘制直线
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onRoiLine()
{
	this->ui.labelDisplay->setOperType(OperateType::TYPE_LINE);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onRoiRect
// Description: 绘制矩形
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onRoiRect()
{
	this->ui.labelDisplay->setOperType(OperateType::TYPE_RECT);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onRoiPolygon
// Description: 绘制多边形
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onRoiPolygon()
{
	this->ui.labelDisplay->setOperType(OperateType::TYPE_POLYGON);
}

void ImageEditorPro::onChoose()
{
	this->ui.labelDisplay->setOperType(OperateType::TYPE_CHOOSE);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: OnCancel
// Description: 撤销
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onUndo()
{
	this->ui.labelDisplay->undo();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: OnRedo
// Description: 重做
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onRedo()
{
	this->ui.labelDisplay->redo();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onSmooth
// Description: 平滑
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onSmooth()
{
	blur(m_cvMat, m_cacheMat, cv::Size(3, 3));
	m_cvMat = m_cacheMat.clone();
	ui.labelDisplay->setOrigImage(m_cacheMat);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onSharpen
// Description: 锐化
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onSharpen()
{
	cv::Mat blur;
	GaussianBlur(m_cvMat, blur, cv::Size(0, 0), 25);
	addWeighted(m_cvMat, 1.5, blur, -0.5, 0, m_cacheMat);
	m_cvMat = m_cacheMat.clone();
	ui.labelDisplay->setOrigImage(m_cacheMat);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onEdgeExtract
// Description: 边缘提取
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onEdgeExtract()
{
	if (m_cvMat.empty())
	{
		return;
	}

	// 将原始图转化为灰度图
	cv::Mat imgGray;
	cv::cvtColor(m_cvMat, imgGray, cv::COLOR_BGR2GRAY);

	// 先使用3*3内核来降噪
	blur(imgGray, imgGray, cv::Size(3, 3));

	// 运行canny算子
	Canny(imgGray, m_cacheMat, 3, 9, 3);

	cv::cvtColor(m_cacheMat, m_cacheMat, cv::COLOR_GRAY2BGR);
	m_cvMat = m_cacheMat.clone();
	ui.labelDisplay->setOrigImage(m_cacheMat);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onMeasureLen
// Description: 测量长度
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onMeasureLen()
{
	ui.labelDisplay->setOperType(OperateType::TYPE_MEASURE_LENGTH);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onMeasureAngle
// Description: 测量角度
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onMeasureAngle()
{
	ui.labelDisplay->setOperType(OperateType::TYPE_MEASURE_ANGLE);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onText
// Description: 标注文字
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onText()
{
	ui.labelDisplay->setOperType(OperateType::TYPE_TEXT);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onSetValue
// Description: 设置数值
// Parameters:int nType
// Parameters:int nValue
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onSetValue(int nType, int nValue, const cv::Mat& mat)
{
	switch (nType)
	{
		case TYPE_GRAY:
		case TYPE_NEAGTIVE:
		{
			m_cvMat = mat.clone();
			m_cacheMat = mat.clone();
			emit sigResetValue();
			break;
		}
		default:
		{
			m_setUpWidget->setValue(nType, nValue);
			const auto& mapValue = m_setUpWidget->getValue();
			process(mapValue);
			break;
		}
	}

	ui.labelDisplay->setOrigImage(m_cvMat, false, nType, nValue, nValue, true);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onScaleChanged
// Description: 比例尺变化
// Parameters:double dScale
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onScaleChanged(double dScale)
{
	int nNumLen = GetNumlen(m_cvMat.cols * dScale);
	ui.widget->setMinimumSize(QSize(2 + (nNumLen - 1) * 6, 5));

	ui.customplot->xAxis2->setRange(0, m_cvMat.rows * dScale);
	ui.customplot->yAxis->setRange(0, m_cvMat.cols * dScale);
	ui.customplot->replot();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: onSave
// Description: 保存图片
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void ImageEditorPro::onSave()
{
	QString strFilename = QFileDialog::getSaveFileName(this, QStringLiteral("保存图像"), "", "*.bmp");
	if (strFilename.isEmpty())
	{
		return;
	}
	else
	{
		if (!ui.labelDisplay->save(strFilename))
		{
			QMessageBox::information(this, QStringLiteral("保存图像"), QStringLiteral("保存图像失败!"));
			return;
		}
	}
}