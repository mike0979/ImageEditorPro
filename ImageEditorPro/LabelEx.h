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

	// ���������ͼ��
	void clearShape();

	// ���Label�ϵ�ROI
	void clearRoi();

	// ���ò�������
	void setOperType(OperateType nRoiShape);

	// ���ô����ͼƬ
	void setOrigImage(const cv::Mat& src, bool bNewImg = false, int nType = TYPE_NULL, int nOldValue = 0, int nValue = 0, bool bUndo = false);

	// ���û�����ɫ
	void setFrameColor(const QColor& color);

	// ����ͼƬ
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
	// ��ROI
	void drawRoi(QImage& img, QList<Roi*>& lstRoi);

	// ���Ƿ��ڻ�������״��
	bool isInRoi(const QPoint& point);

	// ���Ƿ��ڻ�������״��
	bool isRoiPoint(const QPoint& point);

	// ��갴��ʱ�Ļ�ͼ����
	void pressDraw(const QPoint& pos, const QPoint& screenPos);

	// ����ƶ�ʱ�Ļ�ͼ����
	void moveDraw(const QPoint& pos);

	// ����ͷ�ʱ�Ļ�ͼ����
	void releaseDraw(const QPoint& pos);

	// ����ƶ�ʱ���ƶ�ROI����
	void moveMoveRoi(const QPoint& pos);

	void editFinished();
	void clearSaveRoi();
	void draw();

signals:
	void sigScaleChanged(double dScale);

public slots:

private:
	double m_dScale{ 1 }; // �������ֵ
	QPoint m_oldPos; // �ɵ����λ��
	bool m_bIsPress{ false }; // ����Ƿ���
	QPoint m_startPos; // ��ʼ����
	Roi* m_pCurRoi{nullptr}; // ��ǰ���Ƶ�ͼ��
	QList<Roi*> m_lstRoi; // �Ѿ����Ƶ�ͼ��
	QList<Roi*> m_lstSaveRoi; // ��Ҫ�����ROI
	bool m_bDrawCur{ false }; // ����ǰROI��־
	OperateType m_operType{ OperateType::TYPE_CHOOSE }; // ��������
	QImage m_procImg; // �����ͼƬ
	cv::Mat m_src; // ԭʼͼƬ
	QImage m_saveImg; // ���ڱ����ͼƬ
	Roi* m_pChooseRoi{nullptr}; // ѡ�е�ͼ��
	Roi* m_pChangeRoi{ nullptr }; // �ı��ͼ��
	QPoint m_moveStartPos; // �ƶ���ʼ����
	//QMenu* m_pMenu{ nullptr }; // �Ҽ������˵�
	//QAction* m_pAction{ nullptr }; // �Ҽ������˵�ѡ��
	QLineF m_tempLine; // ���ƶ����ʱ��ǰ����
	bool m_bIsInRegion{false}; // �Ƿ���������
	QPoint m_picOffset{0, 0}; // ͼƬƫ��
	QRect m_picRect; // ͼƬ�ľ�������
	QColor m_frameColor{ Qt::red }; // �߿���ɫ
	bool m_bIsChange{false}; // �Ƿ�ı���״��־
	QVector<QPointF> m_vecLinePoints; // ����εĵ�
	bool m_bMoveDraw{false}; // ����Ƿ��ƶ���
	RoiPolyline* m_pTempPolylines; // ������ߵĵ�
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