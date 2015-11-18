#ifndef __MDIRECTOR_H__
#define __MDIRECTOR_H__
#include "MScene.h"
#include <windows.h>

class MActionManager;
class MApplicationProtocol;
class CC_DLL MDirector
{
public:
	MDirector();
	~MDirector();
	static MDirector* getInstance();
	void init();
	void destoy();
	void setWH(int _w, int _h);
	void setWPos(int _x, int _y) { m_wPosX = _x; m_wPosY = _y; }
	void setWnd(HWND _wnd) { m_wnd = _wnd; }
	int getScreenWidth();
	int getScreenHeight();
	int getPosX() { return m_wPosX; }
	int getPosY() { return m_wPosY; }
public:
	void onMainLoop();
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }	
	void setDelay(float _delay);
	void drawScene(LONGLONG _gap);
	void pause() { m_isPause = true; }
	void resume() { m_isPause = false; }
	void runWithScene(MScene* _scene);
	void replaceScene(MScene* _scene);
	MyGraphics* getGraphics() { return m_graphics; }
	MPoint& getMidPoint() { return m_midPoint; }
	void convertPointToGLPoint(MPoint& _point);
	void isShowFPS(bool _isShow) { m_fpsShow = _isShow; }
	MActionManager* getActionManager();
	void registerApplication(MApplicationProtocol* _app) { m_app = _app; }
	void setApplicationAccurite(bool _isAccurite);
	bool isApplicationAccurite();
	void end();
	void registerDragFileCallback(MObject* _taget, DragFileCallBack _callback);
	void unregiterDragFileCallback();
	void invokeDraFileCallback(const std::vector<std::string>& files);
private:
	static MDirector* m_director;
	MScene* m_curScene;
	MScene* m_nextScene;
	int m_width;
	int m_height;
	int m_wPosX;
	int m_wPosY;
	LARGE_INTEGER nFeq;
	LARGE_INTEGER nCountFirst;
	LARGE_INTEGER nCountLast;
	LONGLONG m_delayCount;	
	HWND m_wnd;
	bool m_isPause;
	MyGraphics* m_graphics;
	MPoint m_midPoint;
	float m_fDelayTime;
	int m_uFrames;
	bool m_fpsShow;
	MActionManager* m_gActManager;
	MApplicationProtocol* m_app;
	DragFileCallBack m_dragFileCallback;
	MObject* m_dragFileTarget;
private: 
	void showFPS(float _dt);
};

#define g_mDirector MDirector::getInstance()
#endif