#include "MLabel.h"
#include "MDirector.h"

MLabel::MLabel()
{
	m_labelImpl = new MLabelImpl();
	m_str = new std::string();
}

MLabel::~MLabel()
{
	delete m_labelImpl;
	delete m_str;
}

MLabel* MLabel::create(const char* _str, uint _size, MColor _color)
{
	MLabel* pRet = new MLabel();
	pRet->initLabel(_str, _size, _color);
	return pRet;
}

void MLabel::initLabel(const char* _str, uint _size, MColor _color)
{
	m_str->assign(_str);
	m_fontSize = _size;
	m_color = _color;
	m_labelImpl->init(g_mDirector->getGraphics(), m_fontSize, m_color);
}

void MLabel::setString(const char* _str)
{
	m_str->assign(_str);
}

void MLabel::setColor(const MColor& _color)
{
	m_color = _color;
	m_labelImpl->setColor(m_color);
}

void MLabel::draw()
{
	MNode::draw();
	m_labelImpl->drawStr(m_str->c_str(), m_realPoint);
}

void MLabel::setFontSize(uint _size)
{
	m_labelImpl->setSize(_size);
}
