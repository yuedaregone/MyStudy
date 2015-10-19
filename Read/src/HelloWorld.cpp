#include "HelloWorld.h"
#include "MDraw.h"
using namespace cFunction;
HelloWorld::~HelloWorld()
{
	delete m_pen;
}

MScene* HelloWorld::scene()
{
	MScene* sc = MScene::create();
	HelloWorld* hello = HelloWorld::create();
	sc->addChild(hello, 0);
	return sc;
}

void HelloWorld::init()
{	
	MNode::init();
	int w = g_mDirector->getWidth() >> 1;	
	m_maxH = g_mDirector->getHeight() >> 1;
	m_maxW = (int)g_mDirector->getWidth()*0.3f;
	m_pBottom[0].x = (float)(w);
	m_pBottom[0].y = m_maxH*0.3f;
	m_pBottom[1].x = (float)(w - (m_maxW >> 1));
	m_pBottom[1].y = (float)m_maxH + m_pBottom[0].y;
	m_pBottom[2].x = (float)(w + (m_maxW >> 1));
	m_pBottom[2].y = m_pBottom[1].y;
	m_pen = new Pen(Color(255, 0, 0));
	m_pen->SetWidth(0.1f);


	MLabel* label = MLabel::create("qwret", 16, MColor(255, 0, 0));
	this->addChild(label, 4);
	label->setPoint(MPoint(0,20));

	label = MLabel::create("qwret", 16, MColor(255, 0, 0));
	this->addChild(label, 4);
	label->setPoint(MPoint(1, 20));

	label = MLabel::create("qwret", 16, MColor(255, 0, 0));
	this->addChild(label, 4);
	label->setPoint(MPoint(2, 20));

	MSprite* sp = MSprite::createSprite(103);
	this->addChild(sp, 2);
	sp->setPoint(MPoint(50, 50));
}

void HelloWorld::draw()
{
	MNode::draw();
	return;
	Gdiplus::Graphics* gs = m_graphics->getGraphics();
	MPoint pMid;
	pMid.x = (m_pBottom[1].x + m_pBottom[2].x)*0.5f;
	pMid.y = (m_pBottom[1].y + m_pBottom[2].y)*0.5f;

	Rect rect;	
	rect.Width = 1;
	rect.Height = 1;

	int n = 50000;
	for (int i = 0; i < n; ++i)
	{
		BYTE r = 255 - 200.0 / (float)m_maxW*(pMid.x - m_pBottom[1].x);
		BYTE b = 200.0f / (float)m_maxW*(pMid.y - m_pBottom[0].y) + 50;
		BYTE g = 0;
		m_pen->SetColor(Color(r, g, b));
		rect.X = (INT)pMid.x;
		rect.Y = (INT)pMid.y;
		gs->DrawRectangles(m_pen, &rect, 1);
		int rd = rand() % 3;
		pMid.x = (pMid.x + m_pBottom[rd].x)*0.5f;
		pMid.y = (pMid.y + m_pBottom[rd].y)*0.5f;
	}	
	g_mDirector->pause();
}
