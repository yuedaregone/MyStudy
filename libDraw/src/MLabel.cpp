#include "MLabel.h"
#include "MDirector.h"

MLabel::MLabel()
{
	m_labelImpl = new MLabelImpl();
}

MLabel::~MLabel()
{
	delete m_labelImpl;
}

MLabel* MLabel::create(const char* _str, uint _size, MColor _color)
{
	MLabel* pRet = new MLabel();
	pRet->initLabel(_str, _size, _color);
	return pRet;
}

void MLabel::initLabel(const char* _str, uint _size, MColor _color)
{
	m_str = _str;
	m_fontSize = _size;
	m_color = _color;
	m_labelImpl->init(g_mDirector->getGraphics(), m_fontSize, m_color);
}

void MLabel::setPoint(const MPoint& _p)
{
	MNode::setPoint(_p);
	m_labelImpl->setPosition(m_worldPoint);
}

void MLabel::setString(const char* _str)
{
	m_str = _str;
}

void MLabel::setColor(const MColor& _color)
{
	m_color = _color;
	m_labelImpl->setColor(m_color);
}

void MLabel::draw()
{
	MNode::draw();
	m_labelImpl->drawStr(m_str.c_str());
}
