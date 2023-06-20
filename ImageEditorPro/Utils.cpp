/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: Util.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "Utils.h"
#include <QMap>
#include "Define.h"

#define CLIP_RANGE(value, min, max)  ((value) > (max) ? (max) : (((value) < (min)) ? (min) : (value)))
#define COLOR_RANGE(value)  CLIP_RANGE(value, 0, 255)

void utilfunc::Mat2Image(const cv::Mat& src, QImage& dst)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (src.type() == CV_8UC1)
	{
		QImage img(src.cols, src.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		img.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			img.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = src.data;
		for (int row = 0; row < src.rows; row++)
		{
			uchar *pDest = img.scanLine(row);
			memcpy(pDest, pSrc, src.cols);
			pSrc += src.step;
		}
		dst.swap(img);
	}
	else if (src.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)src.data;
		// Create QImage with same dimensions as input Mat
		dst = QImage(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888).copy();
	}
	else if (src.type() == CV_8UC4)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)src.data;
		// Create QImage with same dimensions as input Mat
		dst = QImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32).copy();
	}
	else
	{
		dst = QImage();
	}
}

//void utilfunc::Image2Mat(const QImage &src, cv::Mat &dst)
//{
//	switch (src.format())
//	{
//	case QImage::Format_ARGB32:
//	case QImage::Format_RGB32:
//	case QImage::Format_ARGB32_Premultiplied:
//		dst = cv::Mat(src.height(), src.width(), CV_8UC4, (void*)src.constBits(), src.bytesPerLine());
//		break;
//	case QImage::Format_RGB888:
//		dst = cv::Mat(src.height(), src.width(), CV_8UC3, (void*)src.constBits(), src.bytesPerLine());
//		break;
//	case QImage::Format_Indexed8:
//		dst = cv::Mat(src.height(), src.width(), CV_8UC1, (void*)src.constBits(), src.bytesPerLine());
//		break;
//	default:
//		break;
//	}
//}

//////////////////////////////////////////////////////////////////////////////// 
// Function: point2PointDis
// Description: 点到点之间距离的平方
// Parameters:const QPoint & point1
// Parameters:const QPoint & point2
// Return: int
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
int utilfunc::Point2PointDis(const QPointF& point1, const QPointF& point2)
{
	return (point1.x() - point2.x()) * (point1.x() - point2.x()) + (point1.y() - point2.y()) * (point1.y() - point2.y());
}

// Gamma矫正
//////////////////////////////////////////////////////////////////////////////// 
// Function: gammaCorrection
// Description: Gamma矫正
// Parameters:const cv::Mat & origImg
// Parameters:double dGamma
// Return: cv::Mat
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void utilfunc::GammaCorrection(cv::Mat& mat, double dGamma)
{
	if (mat.empty())
	{
		mat = std::move(cv::Mat());
		return;
	}

	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();

	for (size_t i = 0; i < 256; i++)
	{
		p[i] = cv::saturate_cast <uchar>(pow(i / 255.0, dGamma) * 255.0);
	}

	LUT(mat, lookUpTable, mat);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: imgProc
// Description: 修改对比度和饱和度
// Parameters:const cv::Mat & srcMat
// Parameters:double dContrast
// Parameters:double dBrightness
// Return: cv::Mat
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void utilfunc::ImgProc(const cv::Mat& src, cv::Mat& dst, double dContrast, double dBrightness)
{
	src.convertTo(dst, -1, dContrast, dBrightness);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: changeRgb
// Description: 改变RGB分量
// Parameters:cv::Mat & input
// Parameters:cv::Mat & output
// Parameters:const QMap<int, double> & mapRgbInfo
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void utilfunc::ChangeRgb(cv::Mat& src, cv::Mat& dst, int nChannel, int nValue)
{
	//OperRgbThread thread1(src, dst, CHANNEL_BLUE, mapRgbInfo[CHANNEL_BLUE]);
	//OperRgbThread thread2(src, dst, CHANNEL_GREEN, mapRgbInfo[CHANNEL_GREEN]);
	//OperRgbThread thread3(src, dst, CHANNEL_RED, mapRgbInfo[CHANNEL_RED]);

	//thread1.start();
	//thread2.start();
	//thread3.start();

	//thread1.wait();
	//thread2.wait();
	//thread3.wait();

	for (size_t i = 0; i < src.rows; i++)
	{
		for (size_t j = 0; j < src.cols; j++)
		{
			dst.at<cv::Vec3b>(i, j)[nChannel] = COLOR_RANGE(src.at<cv::Vec3b>(i, j)[nChannel] + nValue);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: GetNumlen
// Description: 获取数字位数
// Parameters:int nNum
// Return: int
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
int utilfunc::GetNumlen(int nNum)
{
	int nLen = 0;
	while (nNum)
	{
		nNum /= 10;
		nLen++;
	}

	return nLen;
}
