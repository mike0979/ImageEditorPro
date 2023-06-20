/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: LabelEx.h
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#ifndef LABELEX_H
#define LABELEX_H

//#include <QMenu>
//#include <QAction>
#include <QWidget>
#include "Define.h"
#include "opencv.hpp"
//#include "qcustomplot.h"

class QLineEdit;
class Roi;
class RoiPolyline;
class QUndoStack;

class LabelEx : public QWidget
{
	Q_OBJECT
public:
	explicit LabelEx(QWidget *parent = nullptr);
	~LabelEx();

	// 清除所绘制图形
	void clearShape();

	// 清空Label上的ROI
	void clearRoi();

	// 设置操作类型
	void setOperType(OperateType nRoiShape);

	// 设置处理的图片
	void setOrigImage(const cv::Mat& src, bool bNewImg = false, int nType = TYPE_NULL, int nOldValue = 0, int nValue = 0, bool bUndo = false);

	// 设置画框颜色
	void setFrameColor(const QColor& color);

	// 保存图片
	bool save(const QString& strFileName);

	void undo();
	void redo();

protected:
	void paintEvent(QPaintEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *ev);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);

private:
	// 画ROI
	void drawRoi(QImage& img, QList<Roi*>& lstRoi);

	// 点是否在画出的形状里
	bool isInRoi(const QPoint& point);

	// 点是否在画出的形状里
	bool isRoiPoint(const QPoint& point);

	// 鼠标按下时的绘图操作
	void pressDraw(const QPoint& pos, const QPoint& screenPos);

	// 鼠标移动时的绘图操作
	void moveDraw(const QPoint& pos);

	// 鼠标释放时的绘图操作
	void releaseDraw(const QPoint& pos);

	// 鼠标移动时的移动ROI操作
	void moveMoveRoi(const QPoint& pos);

	void editFinished();
	void clearSaveRoi();
	void draw();

signals:
	void sigScaleChanged(double dScale);

public slots:

private:
	double m_dScale{ 1 }; // 鼠标缩放值
	QPoint m_oldPos; // 旧的鼠标位置
	bool m_bIsPress{ false }; // 鼠标是否按下
	QPoint m_startPos; // 开始坐标
	Roi* m_pCurRoi{nullptr}; // 当前绘制的图形
	QList<Roi*> m_lstRoi; // 已经绘制的图形
	QList<Roi*> m_lstSaveRoi; // 需要保存的ROI
	bool m_bDrawCur{ false }; // 画当前ROI标志
	OperateType m_operType{ OperateType::TYPE_CHOOSE }; // 操作类型
	QImage m_procImg; // 处理的图片
	cv::Mat m_src; // 原始图片
	QImage m_saveImg; // 用于保存的图片
	Roi* m_pChooseRoi{nullptr}; // 选中的图形
	Roi* m_pChangeRoi{ nullptr }; // 改变的图形
	QPoint m_moveStartPos; // 移动开始坐标
	//QMenu* m_pMenu{ nullptr }; // 右键弹出菜单
	//QAction* m_pAction{ nullptr }; // 右键弹出菜单选项
	QLineF m_tempLine; // 绘制多边形时当前的线
	bool m_bIsInRegion{false}; // 是否在区域里
	QPoint m_picOffset{0, 0}; // 图片偏移
	QRect m_picRect; // 图片的矩形区域
	QColor m_frameColor{ Qt::red }; // 边框颜色
	bool m_bIsChange{false}; // 是否改变形状标志
	QVector<QPointF> m_vecLinePoints; // 多边形的点
	bool m_bMoveDraw{false}; // 鼠标是否移动了
	RoiPolyline* m_pTempPolylines; // 组成曲线的点
	std::shared_ptr<QLineEdit> m_pLineEdit;
	std::shared_ptr<QUndoStack> m_undoStack;
	QPoint m_movePressPos;
	QPoint m_resizePos;
	bool m_bEditFinish{ true };
	QPoint m_textPos;
	bool m_bReEdit{false};
	QPoint m_imgStartPos;
	bool m_bMeasureFinish{true};
	bool m_bChangeEdit{false};
	QPoint m_changeFinishPos{0, 0};
	QPoint m_moveFinishPos{0, 0};
};

#endif // LABELEX_H