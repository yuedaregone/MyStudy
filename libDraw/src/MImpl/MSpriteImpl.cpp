#include "MSpriteImpl.h"
#include "..\MDirector.h"

MSpriteImpl::MSpriteImpl()
	: m_g(NULL)
	, m_key(-1)
	, m_image(NULL)
	, m_size(0.0f, 0.0f)
{
}

MSpriteImpl::~MSpriteImpl()
{
	m_g = NULL;
}

void MSpriteImpl::init(int _imageId)
{
	m_g = g_mDirector->getGraphics();
	m_key = _imageId;
	m_image = g_imageMgr->getImageByKey(_imageId);
	m_size.w = (float)m_image->GetWidth();
	m_size.h = (float)m_image->GetHeight();
}

void MSpriteImpl::drawImage(const MPoint& _p)
{
	m_g->drawImage(m_image, _p, m_size);
}