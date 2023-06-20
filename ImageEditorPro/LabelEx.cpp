/******************************************************************************
*  Copyright (C), 2017-2019,Advanced Technology Institute of Suzhou. 
*  THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY 
*   
*******************************************************************************
*  File Name: LabelEx.cpp
*  Author: cg.zhang@atisz.ac.cn
*  Version: 1.0.0
*  Date: 2020-3-10
*  Description: brief
*  History: 
******************************************************************************/

#include "LabelEx.h"
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <QFileInfo>
#include <QDateTime>
#include <QLineEdit>
#include <QMessageBox>
#include "RoiLine.h"
#include "RoiRect.h"
#include "RoiPolygon.h"
#include "RoiPolyline.h"
#include "RoiText.h"
#include "AddCmd.h"
#include "MoveCmd.h"
#include "ResizeCmd.h"
#include "DeleteCmd.h"
#include "ClearCmd.h"
#include "OperCmd.h"
#include "ImgMoveCmd.h"
#include "ImgResizeCmd.h"
#include "MeasureAngle.h"
#include "MeasureLine.h"
#include "Utils.h"

using namespace utilfunc;

#define MIN_SCALE 0.1
#define MAX_SCALE 10
#define MIN_POINT 3
#define MIN_SIZE 1
#define ANGLE_LEG 150
#define LINE_WIDTH 3
#define MAX_UNDO_SIZE 10
#define SCALE_LENGTH 4

LabelEx::LabelEx(QWidget *parent) : QWidget(parent)
{
	//m_pMenu = new QMenu();
	//m_pAction = new QAction(this);
	m_pTempPolylines = new RoiPolyline();
	m_pLineEdit = std::make_shared<QLineEdit>(this);
	m_pLineEdit->hide();
	grabKeyboard(); 
	m_undoStack = std::make_shared<QUndoStack>(this);
	m_undoStack->setUndoLimit(MAX_UNDO_SIZE);
}

LabelEx::~LabelEx()
{
	clearRoi();
	clearSaveRoi();

	//// 清理菜单和选项内存
	//if (nullptr != m_pAction)
	//{
	//	delete m_pAction;
	//	m_pAction = nullptr;
	//}

	//if (nullptr != m_pMenu)
	//{
	//	delete m_pMenu;
	//	m_pMenu = nullptr;
	//}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: mousePressEvent
// Description: 鼠标按下事件
// Parameters:QMouseEvent * ev
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::mousePressEvent(QMouseEvent *ev)
{
	// 鼠标点不在图片上直接返回
	if (!m_picRect.contains(ev->pos()))
	{
		return;
	}

	m_bIsPress = true;
	const QPoint& pos = ev->pos() - m_picOffset;

	// 鼠标按下时区分左键和右键，左键用来拖拽或绘图，右键用来完成多边形绘制
	if (ev->button() == Qt::LeftButton)
	{
		// 按住Ctrl记录移动起始点
		if (QApplication::keyboardModifiers() == Qt::ControlModifier)
		{
			m_oldPos = ev->pos();
			m_imgStartPos = ev->pos();
			return;
		}
		else
		{
			if (isRoiPoint(pos))
			{
				m_resizePos = pos;

				// 没有选中任何图形的情况下把画框颜色还原，并把选中的ROI置空
				if (nullptr != m_pChooseRoi)
				{
					m_pChooseRoi->setProcColor(m_pChooseRoi->getOrigColor());
					m_pChooseRoi = nullptr;
					draw();
					update();
				}

				return;
			}

			if (m_bChangeEdit)
			{
				m_bChangeEdit = false;
				editFinished();
			}

			pressDraw(pos, ev->pos());
		}
	} 
	else if (ev->button() == Qt::RightButton)
	{
		if (m_operType == OperateType::TYPE_POLYGON && m_pTempPolylines->size() >= MIN_POINT)
		{
			m_pCurRoi = new RoiPolygon(*m_pTempPolylines);
			m_pCurRoi->setOrigColor(m_frameColor);
			m_pCurRoi->setProcColor(m_frameColor);
			m_lstRoi.push_back(m_pCurRoi);
			m_undoStack->push(new AddCmd(m_lstRoi));
			m_pTempPolylines->clear();
			draw();
			update();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: mouseMoveEvent
// Description: 鼠标移动事件
// Parameters:QMouseEvent * ev
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::mouseMoveEvent(QMouseEvent *ev)
{	
	// 鼠标点不在图片上直接返回
	if (!m_picRect.contains(ev->pos()))
	{
		return;
	}

	if (ev->buttons() & Qt::RightButton)
	{
		return;
	}

	if (!m_bIsPress)
	{
		return;
	}

	// 按住Ctrl就移动图片
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		setCursor(Qt::SizeAllCursor);
		QPoint moveDis = ev->pos() - m_oldPos;
		m_picOffset += moveDis;
		m_oldPos = ev->pos();
		draw();
		update();
		return;
	}
	else
	{
		setCursor(Qt::ArrowCursor);
		const QPoint& pos = ev->pos() - m_picOffset;

		// 如果是改变图形的形状
		if (m_bIsChange)
		{
			m_pChangeRoi->setRoiPoint(pos);
			m_changeFinishPos = pos;
			draw();
			update();
			return;
		}

		if (m_operType == OperateType::TYPE_TEXT)
		{
			return;
		}

		// 如果在形状区域，则拖动形状
		if (m_bIsInRegion)
		{
			moveMoveRoi(pos);
			m_moveFinishPos = pos;
			return;
		}

		if (m_operType == OperateType::TYPE_CHOOSE)
		{
			return;
		}

		moveDraw(pos);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: mouseReleaseEvent
// Description: 鼠标释放事件
// Parameters:QMouseEvent * ev
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::mouseReleaseEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::RightButton)
	{
		return;
	}

	// 如果按住Ctrl记录移动起始点将鼠标箭头还原，其他情况还原各标志位
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		m_undoStack->push(new ImgMoveCmd(m_picOffset, ev->pos() - m_imgStartPos));
		setCursor(Qt::ArrowCursor);
		return;
	}
	else
	{
		if (m_bIsChange)
		{
			if (m_resizePos != m_changeFinishPos && m_changeFinishPos != std::move(QPoint(0, 0)))
			{
				m_undoStack->push(new ResizeCmd(m_pChangeRoi, m_resizePos, m_changeFinishPos));
				m_resizePos = std::move(QPoint(0, 0));
				m_changeFinishPos = std::move(QPoint(0, 0));
			}

			m_bIsChange = false;
			return;
		}

		if (m_bIsInRegion)
		{
			if (m_moveFinishPos != std::move(QPoint(0, 0)))
			{
				m_undoStack->push(new MoveCmd(m_pChooseRoi, m_moveFinishPos - m_movePressPos));
				m_moveFinishPos = std::move(QPoint(0, 0));
			}

			m_bIsInRegion = false;
			return;
		}

		const QPoint& pos = ev->pos() - m_picOffset;
		releaseDraw(pos);
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: clearShape
// Description: 清除所绘制图形
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::clearShape()
{
	clearRoi();
	draw();
	update();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setRoiShape
// Description: 设置操作类型
// Parameters:RoiShape roiShape
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::setOperType(OperateType roiShape)
{
	m_operType = roiShape;
	m_pTempPolylines->clear();
	m_pLineEdit->clear();
	m_pLineEdit->hide();
	draw();
	update();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setProcImage
// Description: 设置处理的图片
// Parameters:const QImage & img
// Parameters:bool bNewImg
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::setOrigImage(const cv::Mat& src, bool bNewImg, int nType, int nOldValue, int nValue, bool bUndo)
{
	if (src.empty())
	{
		return;
	}

	if (nType != TYPE_NULL && !bUndo)
	{
		OperCmd* pOperCmd = nullptr;
		if (nType == TYPE_GRAY || nType == TYPE_NEAGTIVE)
		{
			pOperCmd = new OperCmd(nType, nValue, nOldValue, m_src, src);
		}
		else
		{
			pOperCmd = new OperCmd(nType, nValue, nOldValue);
		}

		m_undoStack->push(pOperCmd);
		bool a = connect(pOperCmd, SIGNAL(sigValueChanged(int, int, const cv::Mat&)), parent()->parent(), SLOT(onSetValue(int, int, const cv::Mat&)));
		int b = 2;
	}

	m_src = src.clone();
	cv::cvtColor(src, m_src, CV_BGR2RGB);
	Mat2Image(m_src, m_saveImg);

	if (bNewImg)
	{
		if (src.cols <= width() && src.rows <= height())
		{
			m_picOffset = std::move(QPoint(width() * 0.5 - src.cols * 0.5, height() * 0.5 - src.rows * 0.5));
		}
		else
		{
			m_picOffset = QPoint(0, 0);
		}

		m_dScale = 1;
		emit sigScaleChanged(m_dScale);
		clearShape();
	}
	else
	{
		draw();
		update();
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: setFrameColor
// Description: 设置画框颜色
// Parameters:const QColor & color
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::setFrameColor(const QColor& color)
{
	m_frameColor = color;

	if (nullptr != m_pChooseRoi)
	{
		m_pChooseRoi->setOrigColor(color);
		m_pChooseRoi->setProcColor(color);
	}

	m_pTempPolylines->clear();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: save
// Description: 保存图片
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool LabelEx::save(const QString& strFileName)
{
	for (auto roi : m_lstRoi)
	{
		// 测量的线不需要保存
		if (nullptr != dynamic_cast<MeasureLine*>(roi) || nullptr != dynamic_cast<MeasureAngle*>(roi))
		{
			continue;
		}

		m_lstSaveRoi.push_back(roi->clone());
	}

	for (auto roi : m_lstSaveRoi)
	{
		roi->resetScale(1 / m_dScale);
		
		// 保存时将高亮还原
		if (roi->getProcColor() == Qt::yellow)
		{
			roi->setProcColor(roi->getOrigColor());
		}
	}

	drawRoi(m_saveImg, m_lstSaveRoi);
	clearSaveRoi();
	QFileInfo fileInfo(strFileName);
	QString strSuffix = fileInfo.suffix();
	bool bRet = m_saveImg.save(strFileName, strSuffix.toStdString().c_str(), 100);
	Mat2Image(m_src, m_saveImg);
	return bRet;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: undo
// Description: 撤销
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::undo()
{
	m_undoStack->undo();
	draw();
	update();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: redo
// Description: 重做
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::redo()
{
	m_undoStack->redo();
	draw();
	update();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: drawRoi
// Description:  画ROI
// Parameters:QPainter & painter
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::drawRoi(QImage& img, QList<Roi*>& lstRoi)
{
	QPainter painter;
	painter.begin(&img);

	// 抗锯齿和平滑
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	QPen pen;
	pen.setWidth(LINE_WIDTH);
	pen.setCapStyle(Qt::RoundCap);
	painter.setPen(pen);

	// 显示已经画出的图形
	for (auto& roi : lstRoi)
	{
		if (nullptr != roi)
		{
			roi->setScale(m_dScale);
			roi->draw(painter);
		}
	}

	pen.setColor(m_frameColor);
	painter.setPen(pen);

	// 画多边形的第一笔
	if (m_tempLine != std::move(QLine(QPoint(0, 0), QPoint(0, 0))))
	{
		painter.drawLine(m_tempLine);
	}

	// 画当前正在画的ROI
	if (m_bDrawCur && nullptr != m_pCurRoi)
	{
		m_bDrawCur = false;
		m_pCurRoi->setOrigColor(m_frameColor);
		m_pCurRoi->setProcColor(m_frameColor);
		m_pCurRoi->draw(painter);
	}

	painter.end();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isInRoi
// Description: 点是否在画出的形状里
// Parameters:const QPoint & point
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool LabelEx::isInRoi(const QPoint& point)
{
	QVector<Roi*> vecRois;

	// 判断点是否在画的图形内
	for (const auto& roi : m_lstRoi)
	{
		if (roi->isInside(point))
		{
			vecRois.push_back(roi);
		}
	}

	if (vecRois.size() < 1)
	{
		return false;
	}
	else if (vecRois.size() > 1)
	{
		std::sort(vecRois.begin(), vecRois.end(), [](Roi* roi1, Roi* roi2)
		{
			return roi1->getSize().width() <= roi2->getSize().width() && roi1->getSize().height() <= roi2->getSize().height();
		});
	}

	if (nullptr != m_pChooseRoi)
	{
		// 取消高亮，还原以前的颜色
		m_pChooseRoi->setProcColor(m_pChooseRoi->getOrigColor());
	}

	m_pChooseRoi = vecRois[0];

	// 设置选中高亮
	m_pChooseRoi->setProcColor(Qt::yellow);

	m_bIsInRegion = true;
	m_vecLinePoints.clear();
	draw();
	update();
	return true;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: isRoiPoint
// Description: 点是否在ROI里
// Parameters:const QPoint & point
// Return: bool
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
bool LabelEx::isRoiPoint(const QPoint& point)
{
	// 判断点是否是图形的点
	for (const auto& roi : m_lstRoi)
	{
		if (nullptr != roi && roi->isRoiPoint(point))
		{
			//if (nullptr != m_pChooseRoi)
			//{
			//	m_pChooseRoi->setProcColor(m_pChooseRoi->getOrigColor());
			//}

			m_pChangeRoi = roi;
			//m_pChooseRoi->setProcColor(Qt::yellow);
			draw();
			update();
			m_bIsChange = true;
			return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: clearRoi
// Description: 清空Label上的ROI
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::clearRoi()
{
	//// 将画出的直线和矩形所占的内存清理掉
	//for (auto& roi : m_lstRoi)
	//{
	//	if (nullptr != roi)
	//	{
	//		delete roi;
	//		roi = nullptr;
	//	}
	//}

	m_undoStack->push(new ClearCmd(m_lstRoi, m_lstRoi));
	m_lstRoi.clear();
	m_vecLinePoints.clear();
	m_pTempPolylines->clear();

	// 所有内存被清空，指向对应内存的指针也要清空
	m_pChooseRoi = nullptr;
	m_pCurRoi = nullptr;
	m_pChangeRoi = nullptr;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: pressDraw
// Description: 鼠标按下时的绘图操作
// Parameters:const QPoint & pos
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::pressDraw(const QPoint& pos, const QPoint& screenPos)
{
	switch (m_operType)
	{
	case OperateType::TYPE_LINE:
	case OperateType::TYPE_RECT:
	case OperateType::TYPE_MEASURE_LENGTH:
	{
		// 记录图形的开始点
		m_startPos = pos;
		break;
	}
	case OperateType::TYPE_POLYGON:
	{
		m_pTempPolylines->push_back(pos);
		m_pCurRoi = m_pTempPolylines;
		auto curRoi = dynamic_cast<RoiPolyline*> (m_pCurRoi);
		curRoi->setDrawEllipse(true);
		m_bDrawCur = true;
		draw();
		update();
		break;
	}
	case OperateType::TYPE_POLYLINE:
	{
		if (m_vecLinePoints.size() == 0)
		{
			m_vecLinePoints.push_back(pos);
		}
		else
		{
			m_vecLinePoints.clear();
		}

		break;
	}
	case OperateType::TYPE_MEASURE_ANGLE:
	{
		if (m_bMeasureFinish)
		{
			m_bMeasureFinish = false;
			QRect rect = m_picRect;
			rect.translate(-m_picOffset);
			if (rect.contains(QPoint(pos.x(), pos.y() + ANGLE_LEG * m_dScale)) 
				&& rect.contains(QPoint(pos.x() + ANGLE_LEG * m_dScale, pos.y())))
			{
				auto roi = new MeasureAngle(QVector<QPointF> {QPointF(pos.x(), pos.y() + ANGLE_LEG * m_dScale), pos,
					QPointF(pos.x() + ANGLE_LEG * m_dScale, pos.y())});
				roi->setOrigColor(m_frameColor);
				roi->setProcColor(m_frameColor);
				m_lstRoi.push_back(roi);
				m_undoStack->push(new AddCmd(m_lstRoi));
				draw();
				update();
			}
			else
			{
				QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("量角器的边将超出边界, 请更换位置"));
			}
		} 
		else
		{
			m_bMeasureFinish = true;
		}

		break;
	}
	case OperateType::TYPE_TEXT:
	{
		if (m_bEditFinish)
		{
			m_bEditFinish = false;

			if (!m_picRect.contains(screenPos.x(), screenPos.y() + QPainter().fontMetrics().height()))
			{
				QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("文字长度将超出边界, 请更换位置或缩短输入长度"));
				break;
			}

			releaseKeyboard();
			m_pLineEdit->move(screenPos);
			m_pLineEdit->clear();
			m_pLineEdit->show();
			m_pLineEdit->setFocus();
			m_textPos = pos;
		}
		else
		{
			editFinished();
			draw();
			update();
		}

		break;
	}
	case OperateType::TYPE_CHOOSE:
	{
		if (isInRoi(pos))
		{
			m_moveStartPos = pos;
			m_movePressPos = pos;
			return;
		}

		// 没有选中任何图形的情况下把画框颜色还原，并把选中的ROI置空
		if (nullptr != m_pChooseRoi)
		{
			m_pChooseRoi->setProcColor(m_pChooseRoi->getOrigColor());
			m_pChooseRoi = nullptr;
			draw();
			update();
		}

		break;
	}
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: moveDraw
// Description: 鼠标移动时的绘图操作
// Parameters:const QPoint & pos
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::moveDraw(const QPoint& pos)
{
	m_bMoveDraw = true;

	switch (m_operType)
	{
	case OperateType::TYPE_LINE:
	{
		m_pCurRoi = new RoiLine(m_startPos, pos);
		break;
	}
	case OperateType::TYPE_RECT:
	{
		m_pCurRoi = new RoiRect(m_startPos, pos);
		break;
	}
	case OperateType::TYPE_POLYGON:
	{
		if (m_pTempPolylines->size() <= 1)
		{
			m_tempLine = QLineF((*m_pTempPolylines)[0], pos);
		}

		break;
	}
	case OperateType::TYPE_POLYLINE:
	{
		m_vecLinePoints.push_back(pos);
		m_pCurRoi = new RoiPolyline(m_vecLinePoints);
		break;
	}
	case OperateType::TYPE_MEASURE_LENGTH:
	{
		m_pCurRoi = new MeasureLine(m_startPos, pos);
		break;
	}
	default:
		break;
	}

	m_bDrawCur = true;
	draw();
	update();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: releaseDraw
// Description: 鼠标释放时的绘图操作
// Parameters:const QPoint & pos
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::releaseDraw(const QPoint& pos)
{
	if (!m_bMoveDraw)
	{
		m_bIsPress = false;
		return;
	}

	m_bMoveDraw = false;
	m_bIsPress = false;

	switch (m_operType)
	{
	case OperateType::TYPE_LINE:
	case OperateType::TYPE_RECT:
	{
		if (nullptr != m_pCurRoi)
		{
			m_lstRoi.push_back(m_pCurRoi);
			m_undoStack->push(new AddCmd(m_lstRoi));
		}

		break;
	}
	case OperateType::TYPE_POLYGON:
	{
		if (m_pTempPolylines->size() <= MIN_SIZE)
		{
			m_pTempPolylines->push_back(m_tempLine.p2());
			m_tempLine = QLine();
			m_pCurRoi = m_pTempPolylines;
			m_bDrawCur = true;
			draw();
			update();
		}

		break;
	}
	case OperateType::TYPE_POLYLINE:
	{
		if (nullptr != m_pCurRoi)
		{
			m_lstRoi.push_back(m_pCurRoi);
			m_undoStack->push(new AddCmd(m_lstRoi));
		}

		m_vecLinePoints.clear();
		break;
	}
	case OperateType::TYPE_MEASURE_LENGTH:
	{
		if (nullptr != m_pCurRoi)
		{
			auto measureLine = dynamic_cast<MeasureLine*>(m_pCurRoi);
			measureLine->setShowFlag();
			m_lstRoi.push_back(measureLine);
			m_undoStack->push(new AddCmd(m_lstRoi));
		}

		draw();
		update();
		break;
	}
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: moveMoveRoi
// Description: 鼠标移动时的移动ROI操作
// Parameters:const QPoint & pos
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::moveMoveRoi(const QPoint& pos)
{
	QPoint distance = pos - m_moveStartPos;
	m_moveStartPos = pos;
	m_pChooseRoi->move(distance);

	// 移动画框不能超出图片
	QRect rect = m_picRect;
	rect.translate(-m_picOffset);

	// 超出图片后要把超出部分平移回来
	if (!m_pChooseRoi->isInRect(rect))
	{
		m_pChooseRoi->move(-distance);
	}
	
	draw();
	update();
	return;
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: editFinished
// Description: 文字编辑结束的处理
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::editFinished()
{
	auto inputText = m_pLineEdit->text();
	QFontMetrics fm = QPainter().fontMetrics();
	int nWidth = fm.width(inputText);
	int nHeight = fm.height();
	QRect rect = m_picRect;
	rect.translate(-m_picOffset);
	m_bEditFinish = true;

	if (!inputText.isEmpty())
	{
		if (!m_bReEdit)
		{
			if (!rect.contains(m_textPos + QPoint(nWidth, nHeight)))
			{
				m_pLineEdit->hide();
				QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("文字长度将超出边界, 请更换位置或缩短输入长度"));
				return;
			}

			m_pCurRoi = new RoiText(m_textPos, m_textPos + std::move(QPoint(nWidth, nHeight)));
			m_pCurRoi->setOrigColor(m_frameColor);
			m_pCurRoi->setProcColor(m_frameColor);
			m_lstRoi.push_back(m_pCurRoi);
		}
		else
		{
			auto fontSize = dynamic_cast<RoiText*>(m_pCurRoi)->getFontSize();
			if (!rect.contains(dynamic_cast<RoiText*>(m_pCurRoi)->topLeft().toPoint() + std::move(QPoint(inputText.toLocal8Bit().length() * fontSize * 0.5, 0))))
			{
				m_pLineEdit->hide();
				QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("文字长度将超出边界, 请更换位置或缩短输入长度"));
				return;
			}

			m_bReEdit = false;
			dynamic_cast<RoiText*>(m_pCurRoi)->setWidth(inputText.toLocal8Bit().length() * fontSize * 0.5);
		}

		m_undoStack->push(new AddCmd(m_lstRoi));
		dynamic_cast<RoiText*>(m_pCurRoi)->setText(std::move(m_pLineEdit->text()));
	}

	m_pLineEdit->hide();
	grabKeyboard();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: clearSaveRoi
// Description:  清理保存图片时的ROI
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::clearSaveRoi()
{
	for (auto roi : m_lstSaveRoi)
	{
		if (nullptr != roi)
		{
			delete roi;
			roi = nullptr;
		}
	}

	m_lstSaveRoi.clear();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: draw
// Description: 绘制
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::draw()
{
	if (m_src.empty())
	{
		return;
	}

	// 缩放
	cv::Mat dst;
	cv::resize(m_src, dst, cv::Size(m_src.cols * m_dScale, m_src.rows * m_dScale), 0, 0, cv::INTER_NEAREST);
	Mat2Image(dst, m_procImg);

	// 绘制图形
	drawRoi(m_procImg, m_lstRoi);
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: paintEvent
// Description: 绘图事件
// Parameters:QPaintEvent * ev
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::paintEvent(QPaintEvent *ev)
{
	//QCustomPlot::paintEvent(ev);

	QPainter painter;
	painter.begin(this);

	// 绘制图像
	m_picRect = QRect(m_picOffset.x(), m_picOffset.y(), m_procImg.width(), m_procImg.height());
	painter.drawImage(m_picRect, m_procImg);
	painter.end();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: wheelEvent
// Description: 鼠标滚轮事件
// Parameters:QWheelEvent * event
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::wheelEvent(QWheelEvent *event)
{
	if (QApplication::keyboardModifiers() != Qt::ControlModifier)
	{
		return;
	}

	auto oldScale = m_dScale;

	int nDelta = event->delta();
	if (nDelta > 0)
	{
		m_dScale *= SCALE;

		if (m_dScale >= MAX_SCALE)
		{
			m_dScale = oldScale;
			return;
		}
	}
	else
	{
		m_dScale /= SCALE;

		if (m_dScale <= MIN_SCALE)
		{
			m_dScale = oldScale;
			return;
		}
	}

	if (!m_src.empty())
	{
		emit sigScaleChanged(m_dScale);
	}

	// 显示已经画出的图形
	for (auto roi : m_lstRoi)
	{
		if (nullptr != roi)
		{
			roi->transform(nDelta);
		}
	}

	// 图片尺寸小于画布时在中心显示
	if (m_procImg.width() <= width() && m_procImg.height() <= height())
	{
		QPoint oldPicOffset = m_picOffset;

		if (nDelta > 0)
		{
			m_picOffset = std::move(QPoint(width() * 0.5 - m_procImg.width() * SCALE * 0.5, height() * 0.5 - m_procImg.height() * SCALE * 0.5));
		} 
		else
		{
			m_picOffset = std::move(QPoint(width() * 0.5 - m_procImg.width() / SCALE * 0.5, height() * 0.5 - m_procImg.height() / SCALE * 0.5));
		}

		m_undoStack->push(new ImgResizeCmd(m_picOffset, oldPicOffset - m_picOffset, m_dScale, oldScale, m_lstRoi, nDelta));
		draw();
		update();
		return;
	}

	// 为了以鼠标为中心对图片进行缩放，计算缩放之后图片的位置
	const QPoint& oldPoint = event->pos() - m_picOffset;

	if (nDelta > 0)
	{
		m_picOffset -= oldPoint * SCALE - oldPoint;
		m_undoStack->push(new ImgResizeCmd(m_picOffset, oldPoint * SCALE - oldPoint, m_dScale, oldScale, m_lstRoi, nDelta));
	}
	else
	{
		m_picOffset -= oldPoint / SCALE - oldPoint;
		m_undoStack->push(new ImgResizeCmd(m_picOffset, oldPoint / SCALE - oldPoint, m_dScale, oldScale, m_lstRoi, nDelta));
	}

	draw();
	update();
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: keyPressEvent
// Description: 键盘按下事件
// Parameters:QKeyEvent * ev
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::keyPressEvent(QKeyEvent *ev)
{
	// 如果按下删除键且删除的ROI存在则进行删除操作
	if (ev->key() == Qt::Key_Delete && nullptr != m_pChooseRoi)
	{
		// 如果m_pChooseRoi和m_pCurRoi指向同一地址，则m_pCurRoi也要置空
		if (m_pChooseRoi == m_pCurRoi)
		{
			m_pCurRoi = nullptr;
		}

		// 删除对应内存并将指针置空
		m_lstRoi.removeAll(m_pChooseRoi);
		m_undoStack->push(new DeleteCmd(m_lstRoi, m_pChooseRoi));
		//delete m_pChooseRoi;
		//m_pChooseRoi = nullptr;
		draw();
		update();
	}
}

//////////////////////////////////////////////////////////////////////////////// 
// Function: mouseDoubleClickEvent
// Description: 双击编辑标注文字
// Parameters:QMouseEvent * event
// Return: void
// Remarks: 
////////////////////////////////////////////////////////////////////////////////
void LabelEx::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (m_operType != OperateType::TYPE_CHOOSE || nullptr == dynamic_cast<RoiText*>(m_pChooseRoi))
	{
		return;
	}

	releaseKeyboard();
	m_pLineEdit->setText(dynamic_cast<RoiText*>(m_pChooseRoi)->getText());
	m_pLineEdit->move(event->pos());
	m_pLineEdit->show();
	m_pCurRoi = m_pChooseRoi;
	m_bEditFinish = false;
	m_bReEdit = true;
	m_bChangeEdit = true;
}

void LabelEx::resizeEvent(QResizeEvent *event)
{
	if (m_procImg.width() <= width() && m_procImg.height() <= height())
	{
		m_picOffset = std::move(QPoint(width() * 0.5 - m_procImg.width() * 0.5, height() * 0.5 - m_procImg.height() * 0.5));
	}
}
