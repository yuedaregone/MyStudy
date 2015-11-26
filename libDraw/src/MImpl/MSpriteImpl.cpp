#include "MSpriteImpl.h"
#include "..\MDirector.h"

MSpriteImpl::MSpriteImpl()
	: m_g(NULL)
	, m_key(-1)
	, m_image(NULL)	
{
}

MSpriteImpl::~MSpriteImpl()
{
	m_g = NULL;
}

void MSpriteImpl::init(int _imageId, MSize& _size)
{
	m_g = g_mDirector->getGraphics();
	m_key = _imageId;
	m_image = g_imageMgr->getImageByKey(_imageId);
	_size.w = (float)m_image->GetWidth();
	_size.h = (float)m_image->GetHeight();
}

void MSpriteImpl::drawImage(const MPoint& _p,const MSize& _size)
{
	m_g->drawImage(m_image, _p, _size);
}