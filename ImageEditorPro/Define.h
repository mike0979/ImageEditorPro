/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: Define.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#ifndef DEFINE_H
#define DEFINE_H

#define MIN_DISTANCE 5 // 最小距离
#define SCALE 1.1
#define ELLIPSE 10

enum class OperateType
{
	TYPE_CHOOSE = 0,
	TYPE_LINE = 1, // 直线
	TYPE_RECT = 2, // 矩形
	TYPE_POLYGON = 3, // 多边形
	TYPE_POLYLINE = 4, // 曲线
	TYPE_MOVE = 5,
	TYPE_RESHAPE = 6,
	TYPE_TEXT = 7,
	TYPE_MEASURE_LENGTH = 8,
	TYPE_MEASURE_ANGLE = 9
};

enum RgbChannel
{
	CHANNEL_BLUE = 0,
	CHANNEL_GREEN = 1,
	CHANNEL_RED = 2
};

enum ChangeType
{
	TYPE_NULL = 0,
	TYPE_GAMMA = 1,
	TYPE_CONTRAST = 2,
	TYPE_BRIGHTNESS = 3,
	TYPE_BLUE = 4,
	TYPE_GREEN = 5,
	TYPE_RED = 6,
	TYPE_GRAY = 7,
	TYPE_NEAGTIVE = 8,
};

#endif