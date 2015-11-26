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
	MSize tempSize;
	m_spImpl->init(m_key, tempSize);
	setSize(tempSize);
	return true;
}

void MSprite::draw()
{
	MNode::draw();
	m_spImpl->drawImage(m_realPoint, m_realSize);
}