/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: ImageProcess.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <QtWidgets/QWidget>
#include "ui_ImageEditorPro.h"
#include "opencv.hpp"

class SettingsWidget;

class ImageEditorPro : public QWidget
{
	Q_OBJECT

public:
	ImageEditorPro(QWidget *parent = Q_NULLPTR);

	// 初始化
	bool init();

private:
	// 链接信号
	bool connectSignals();

	// 参数调整处理函数
	void process(const QMap<int, int>& mapValue);

signals:
	void sigResetValue();

private slots:
	// 加载图片
	void onLoadin();

	// 灰度处理
	void onBtnGray();

	// 清除ROI
	void onBtnClear();

	// 恢复原图
	void onBtnRestore();

	// 负图像
	void onBtnNeagtive();

	// 调整对比度
	void onSetUp();
	void onValueChanged(const QMap<int, int>& mapValue, int nType, int nOldValue, int nValue);

	// 设置画框颜色
	void onFrameColor();

	// 保存图片
	void onSave();

	// 绘制曲线
	void onRoiPolyline();

	// 绘制直线
	void onRoiLine();

	// 绘制矩形
	void onRoiRect();

	// 绘制多边形
	void onRoiPolygon();

	void onChoose();
	void onUndo();
	void onRedo();
	void onSmooth();
	void onSharpen();
	void onEdgeExtract();
	void onMeasureLen();
	void onMeasureAngle();
	void onText();
	void onSetValue(int nType, int nValue, const cv::Mat& mat);
	void onScaleChanged(double dScale);

private:
	Ui::ImageEditorPro ui; // 界面
	cv::Mat m_origMat; // 原始图像
	cv::Mat m_cacheMat; // 缓存的图像
	cv::Mat m_cvMat; // 处理的图像
	std::shared_ptr<SettingsWidget> m_setUpWidget;
};

#endif