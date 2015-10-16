#ifndef __MWINDOW_H__
#define __MWINDOW_H__
#include <windows.h>
#include <string>
#define ID_TIMER 1

class MWindow
{
public:
	MWindow();
	virtual ~MWindow();
public:
	static MWindow *mGetWindow();
	void mSetTitle(std::string _pTitleName);
	void mSetRect(RECT &_rect);
	void mSetTimeGap(unsigned int _gap) { m_timerGap = _gap; }
	void mRun(HINSTANCE _hInstance, int _nCmdShow);
	virtual void mWndClass();
	virtual bool mCreateWindow();
	virtual LRESULT CALLBACK mOnWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	virtual void mOnInit();
	virtual void mOnMainLoop();
	virtual void mOnEnd();
	virtual void mOnDestroy();
	virtual void mOnTimer();
	virtual void mOnPaint(HDC _dc);
	virtual void mOnButtonClick(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
private:
	bool mRegisterClass();
	bool mWindowInit();
	void mWindowLoop();
	void mWindowEnd();
protected:
	HINSTANCE		m_hinstance;
	HWND			m_hwnd;
	WNDCLASSEX		m_wc;
	std::string		m_pClassName;
	std::string		m_pTitleName;
	static MWindow*	m_instance;
	RECT			m_rect;
	bool			m_isAccurite;
	unsigned int	m_timerGap;
};


#endif