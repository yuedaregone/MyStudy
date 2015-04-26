#include "HelloWorld.h"
#include "../classes/MyGraphics.h"
#include "../classes/MDirector.h"
#include "../classes/MLabel.h"
#include "../classes/MSprite.h"
#include "../classes/MCommonFunction.h"
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


	/*MLabel* label = MLabel::create("qwret", 16, MColor(255, 0, 0));
	this->addChild(label, 4);
	label->setPoint(g_mDirector->getMidPoint());

	MSprite* sp = MSprite::createSprite(102);
	this->addChild(sp, 2);
	sp->setPoint(MPoint(50, 50));*/
	srand(time(NULL));
	for (int i = 0; i < BALL_MAX_NUM; ++i)
	{
		m_ball[i] = Ball::createBall(112);
		this->addChild(m_ball[i], 2);
		m_ball[i]->resetBallPosition(m_ball, i);
	}	
	this->scheduleTask((SEL_Update(&HelloWorld::updateBallPos)), 0.0f);
}

void HelloWorld::updateBallPos(float dt)
{
	for (int i = 0; i < BALL_MAX_NUM; ++i)
	{
		m_ball[i]->updatePosition(m_ball, i);
	}	
	for (int i = 1; i < BALL_MAX_NUM; ++i)
	{
		m_ball[i]->updateCrash(m_ball, i);
	}
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

Ball* Ball::createBall(int _key)
{
	Ball* pRet = new Ball();
	pRet->initBall(_key);
	return pRet;
}

void Ball::initBall(int _key)
{
	MSprite::initSprite(_key);
	m_speedX = rand() % 3 + 2;
	m_speedY = rand() % 3 + 2;
	m_speedX = rand() % 10 > 5 ? m_speedX : -m_speedX;
	m_speedY = rand() % 10 > 5 ? m_speedY : -m_speedY;
	m_r = m_size.w * 0.5f;
}

void Ball::resetBallPosition(Ball* _ball[], int n)
{
	bool isCrash = false;
	do 
	{
		isCrash = false;
		m_point.x = rand() % (g_mDirector->getWidth() - (int)m_size.w);
		m_point.y = rand() % (g_mDirector->getHeight() - (int)m_size.h);
		MPoint mMidPoint = getMidPoint();
		for (int i = 0; i < n; ++i)
		{
			MPoint oMidPoint = _ball[i]->getMidPoint();
			if (getDistancePower(mMidPoint, oMidPoint) <
				(m_r + _ball[i]->m_r)*(m_r + _ball[i]->m_r))
			{
				isCrash = true;
				break;
			}
		}
	} while (isCrash);
}

void Ball::updatePosition(Ball* _ball[], int n)
{
	m_speedY += 0.0005f;
	m_point.x += m_speedX;
	m_point.y += m_speedY;
	for (int i = e_type_up; i < e_type_unkown; ++i)
	{
		checkIsCrashWall((WallType)i);
	}	
}

void Ball::updateCrash(Ball* _ball[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (isCrashOtherBall(_ball[i]))
		{
			crashBall(_ball[i]);
		}
	}
}

MPoint Ball::getMidPoint()
{
	return m_point + MPoint(m_size.w * 0.5f, m_size.h * 0.5f);
}

void Ball::checkIsCrashWall(WallType _t)
{
	switch (_t)
	{
	case e_type_up:
		if (m_point.y <= 0 && m_speedY < 0)			
			m_speedY = -m_speedY;
		break;
	case e_type_down:
		if (m_point.y + m_size.h >= g_mDirector->getHeight() && m_speedY > 0)			
			m_speedY = -m_speedY;
		break;
	case e_type_left:
		if (m_point.x <= 0 && m_speedX < 0)			
			m_speedX = -m_speedX;
		break;
	case e_type_right:
		if (m_point.x + m_size.w >= g_mDirector->getWidth() && m_speedX > 0)			
			m_speedX = -m_speedX;
		break;
	default:
		break;
	}
}

bool Ball::isCrashOtherBall(Ball* _otherBall)
{	
	MPoint mMidPoint = getMidPoint();
	MPoint oMidPoint = _otherBall->getMidPoint();
	if (getDistancePower(mMidPoint, oMidPoint) < 
		(m_r + _otherBall->m_r)*(m_r + _otherBall->m_r) &&
		getDistancePower(mMidPoint, oMidPoint) > 
		getDistancePower(MPoint(mMidPoint.x + m_speedX, mMidPoint.y + m_speedY), 
		MPoint(oMidPoint.x + _otherBall->m_speedX, oMidPoint.y + _otherBall->m_speedY)))
	{
		return true;
	}
	return false;
}

void Ball::crashBall(Ball* _otherBall)
{
	float ma = m_r * m_r, mb = _otherBall->m_r * _otherBall->m_r;

	float sx = m_point.x - _otherBall->getPoint().x;
	float sy = m_point.y - _otherBall->getPoint().y;
	float s1x = sx / sqrt(sx*sx + sy*sy);
	float s1y = sy / sqrt(sx*sx + sy*sy);
	float t1x = -s1y;
	float t1y = s1x;

	float vas = m_speedX * s1x + m_speedY * s1y;
	float vat = m_speedX * t1x + m_speedY * t1y;
	float vbs = _otherBall->m_speedX * s1x + _otherBall->m_speedY * s1y;
	float vbt = _otherBall->m_speedX * t1x + _otherBall->m_speedY * t1y;

	float vasf = (2 * mb * vbs + vas * (ma - mb)) / (ma + mb);
	float vbsf = (2 * ma * vas - vbs * (ma - mb)) / (ma + mb);

	float nsx = vasf * s1x;
	float nsy = vasf * s1y;
	float ntx = vat * t1x;
	float nty = vat * t1y;

	m_speedX = nsx + ntx;
	m_speedX = nsy + nty;

	nsx = vbsf * s1x;
	nsy = vbsf * s1y;
	ntx = vbt * t1x;
	nty = vbt * t1y;

	_otherBall->m_speedX = nsx + ntx;
	_otherBall->m_speedY = nsy + nty;
}