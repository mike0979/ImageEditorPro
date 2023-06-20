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

	// ��ʼ��
	bool init();

private:
	// �����ź�
	bool connectSignals();

	// ��������������
	void process(const QMap<int, int>& mapValue);

signals:
	void sigResetValue();

private slots:
	// ����ͼƬ
	void onLoadin();

	// �Ҷȴ���
	void onBtnGray();

	// ���ROI
	void onBtnClear();

	// �ָ�ԭͼ
	void onBtnRestore();

	// ��ͼ��
	void onBtnNeagtive();

	// �����Աȶ�
	void onSetUp();
	void onValueChanged(const QMap<int, int>& mapValue, int nType, int nOldValue, int nValue);

	// ���û�����ɫ
	void onFrameColor();

	// ����ͼƬ
	void onSave();

	// ��������
	void onRoiPolyline();

	// ����ֱ��
	void onRoiLine();

	// ���ƾ���
	void onRoiRect();

	// ���ƶ����
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
	Ui::ImageEditorPro ui; // ����
	cv::Mat m_origMat; // ԭʼͼ��
	cv::Mat m_cacheMat; // �����ͼ��
	cv::Mat m_cvMat; // �����ͼ��
	std::shared_ptr<SettingsWidget> m_setUpWidget;
};

#endif