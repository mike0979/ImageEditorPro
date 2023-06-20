/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: Utils.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <QImage>
#include "opencv.hpp"

namespace utilfunc
{
	// Matת����QImage
	void Mat2Image(const cv::Mat& mat, QImage &imgDst);

	// QImageת����Mat
	//void Image2Mat(const QImage &image, cv::Mat &mat);

	// �㵽��֮������ƽ��
	int Point2PointDis(const QPointF& point1, const QPointF& point2);

	// Gamma����
	void GammaCorrection(cv::Mat& mat, double dGamma);

	// �޸ĶԱȶȺͱ��Ͷ�
	void ImgProc(const cv::Mat& src, cv::Mat& dst, double dContrast, double dBrightness);

	// �ı�RGB
	void ChangeRgb(cv::Mat& src, cv::Mat& dst, int nChannel, int nValue);

	int GetNumlen(int nNum);
}

#endif 
