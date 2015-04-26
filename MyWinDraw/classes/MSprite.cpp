#include "MSprite.h"
#include "MDirector.h"
MSprite::MSprite()
{
	m_spImpl = new MSpriteImpl();
}

MSprite::~MSprite()
{
	delete m_spImpl;
}

MSprite* MSprite::createSprite(int _key)
{
	MSprite* pRet = new MSprite();
	pRet->initSprite(_key);
	return pRet;
}

bool MSprite::initSprite(int _key)
{
	MNode::init();
	m_key = _key;
	m_spImpl->init(m_key);
	m_size = m_spImpl->getContentSize();
	return true;
}

void MSprite::draw()
{
	MNode::draw();
	m_spImpl->drawImage(m_point);
}