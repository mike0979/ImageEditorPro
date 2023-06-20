#ifndef OPER_COMMAND_H
#define OPER_COMMAND_H

#include <QUndoCommand>
#include <QImage>
#include <QObject>
#include "opencv.hpp"

class OperCmd : public QObject, public QUndoCommand
{
	Q_OBJECT
public:
	OperCmd(int nType, int nValue, int nOldValue, const cv::Mat& img = cv::Mat(), const cv::Mat& dst = cv::Mat());

private:
	void redo() override;
	void undo() override;

signals:
	void sigValueChanged(int nType, int nValue, const cv::Mat& mat);

private:
	cv::Mat m_src;
	cv::Mat m_dst;
	int m_nValue;
	int m_nType;
	int m_nOldValue{0};
};

#endif
