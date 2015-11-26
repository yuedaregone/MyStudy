#include "MButton.h"
#include "MSprite.h"

MButton* MButton::createButton(int _key, MObject* _target, ClickCallback _callbak)
{
	MButton* pRet = new MButton();
	pRet->m_target = _target;
	pRet->m_callback = _callbak;
	pRet->initButton(_key);
	return pRet;
}

void MButton::initButton(int _key)
{
	MNode::init();
	if (m_spShow)
	{
		m_spShow->remove();
	}
	m_spShow = MSprite::createSprite(_key);
	this->addChild(m_spShow, 0);
	m_spShow->setAnchorPoint(mp(0.5f, 0.5f));
	MSize size = m_spShow->getSize();
	this->setSize(size);
	m_spShow->setPoint(mp(size.w*0.5f, size.h*0.5f));	
}

void MButton::setTarget(MObject* _target, ClickCallback _callbak)
{
	m_target = _target;
	m_callback = _callbak;
}

bool MButton::mTouchBegin(const MPoint& _p)
{
	MRect rect = m_spShow->boundingBox();
	if (rect.isContainPoint(_p))
	{
		m_isTouched = true;
		m_spShow->setScale(ms(0.95f, 0.95f));
		return true;
	}
	return false;
}

void MButton::mTouchMove(const MPoint& _p)
{
}

void MButton::mTouchEnd(const MPoint& _p)
{
	if (m_isTouched)
	{
		MRect rect = m_spShow->boundingBox();
		if (rect.isContainPoint(_p))
		{			
			if (m_target && m_callback)
			{
				(m_target->*m_callback)(this);
			}
		}		
	}
	m_spShow->setScale(ms(1.0f, 1.0f));
}
