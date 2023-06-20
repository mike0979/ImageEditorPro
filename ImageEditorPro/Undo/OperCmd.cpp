#include "OperCmd.h"
#include "Utils.h"

using namespace utilfunc;

OperCmd::OperCmd(int nType, int nValue, int nOldValue, const cv::Mat& src, const cv::Mat& dst)
{
	if (!src.empty())
	{
		m_src = src.clone();
		m_dst = dst.clone();
	}

	m_nValue = nValue;
	m_nType = nType;
	m_nOldValue = nOldValue;
}

void OperCmd::redo()
{
	emit sigValueChanged(m_nType, m_nValue, m_dst);
}

void OperCmd::undo()
{
	if (!m_src.empty())
	{
		cv::Mat mat;
		cv::cvtColor(m_src, mat, CV_BGR2RGB);
		emit sigValueChanged(m_nType, m_nOldValue, mat);
	}
	else
	{
		emit sigValueChanged(m_nType, m_nOldValue, m_src);
	}
}
