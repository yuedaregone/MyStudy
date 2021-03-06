#include "MDirector.h"
#include <stdio.h>
#include "MyGraphics.h"
#include "MCommonFunction.h"
#include "MActionManager.h"
#include "MApplicationProtocol.h"

MDirector* MDirector::m_director = NULL;

MDirector::MDirector()
	:m_curScene(NULL)
	,m_nextScene(NULL)
	,m_isPause(false)
	,m_graphics(NULL)
	,m_fDelayTime(0.0f)
	,m_uFrames(0)
	,m_fpsShow(true)
	,m_wPosX(0)
	,m_wPosY(0)
	,m_gActManager(NULL)
	,m_app(NULL)
	,m_dragFileCallback(NULL)
	,m_dragFileTarget(NULL)
{}

MDirector::~MDirector()
{}

MDirector* MDirector::getInstance()
{
	if (!m_director)
	{
		m_director = new MDirector();
	}
	return m_director;
}

void MDirector::init()
{
	QueryPerformanceFrequency(&nFeq);
	QueryPerformanceCounter(&nCountFirst);
	m_delayCount = static_cast<LONGLONG>(1.0 / 60.0 * nFeq.QuadPart);
	m_graphics = new MyGraphics();
	m_graphics->init(m_wnd);
	m_midPoint.x = (float)(m_width >> 1);
	m_midPoint.y = (float)(m_height >> 1);
}

void MDirector::destoy()
{
	m_graphics->destroy();
}

void MDirector::setWH(int _w, int _h)
{
	m_width = _w;
	m_height = _h;
}

int MDirector::getScreenWidth()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int MDirector::getScreenHeight()
{
	return GetSystemMetrics(SM_CYSCREEN);
}

void MDirector::onMainLoop()
{
	QueryPerformanceCounter(&nCountLast);
	if (nCountLast.QuadPart - nCountFirst.QuadPart >= m_delayCount)
	{
		if (!m_isPause)
		{
			drawScene(nCountLast.QuadPart - nCountFirst.QuadPart);
		}		
		nCountFirst.QuadPart = nCountLast.QuadPart;
	}
}

void MDirector::setDelay(float _delay)
{
	LARGE_INTEGER feq;
	QueryPerformanceFrequency(&feq);
	m_delayCount = static_cast<LONGLONG>(_delay*feq.QuadPart);
}

void MDirector::drawScene(LONGLONG _gap)
{	
	float dt = _gap / static_cast<float>(nFeq.QuadPart);
	m_curScene->update(dt);
	if (m_gActManager)
		m_gActManager->update(dt);
	m_graphics->clear();
	m_curScene->visit();	
	if (m_fpsShow)
		showFPS(dt);
	m_graphics->update(dt);
}

void MDirector::runWithScene(MScene* _scene)
{
	MAssert(m_curScene == NULL && "this is must be run once!");
	m_curScene = _scene;
	m_curScene->setGraphics(m_graphics);
}

void MDirector::replaceScene(MScene* _scene)
{
}

void MDirector::convertPointToGLPoint(MPoint& _point)
{
	_point.y = m_height - _point.y;
}

void MDirector::showFPS(float _dt)
{
	m_uFrames++;
	m_fDelayTime += _dt;
	if (m_fDelayTime > 0.5f)
	{
		cFunction::MLog("FPS:%.3f", m_uFrames / m_fDelayTime);
		m_uFrames = 0;
		m_fDelayTime = 0.0f;
	}
}

MActionManager* MDirector::getActionManager()
{
	if (!m_gActManager)
	{
		m_gActManager = new MActionManager();
	}
	return m_gActManager;
}

void MDirector::setApplicationAccurite(bool _isAccurite)
{
	if (m_app)
	{
		m_app->mSetIsAccurite(_isAccurite);
	}
}

bool MDirector::isApplicationAccurite()
{
	if (m_app)
	{
		return m_app->mIsAccurite();
	}
	return false;
}

void MDirector::end()
{
	if (m_app)
	{
		m_app->mSetEnd(true);
	}
}

void MDirector::registerDragFileCallback(MObject* _taget, DragFileCallBack _callback)
{
	m_dragFileTarget = _taget;
	m_dragFileCallback = _callback;
}

void MDirector::unregiterDragFileCallback()
{
	m_dragFileTarget = NULL;
	m_dragFileCallback = NULL;
}

void MDirector::invokeDraFileCallback(const std::vector<std::string>& files)
{
	if (m_dragFileTarget && m_dragFileCallback)
	{
		(m_dragFileTarget->*m_dragFileCallback)(files);
	}
}