#include "MWindow.h"
#include <WindowsX.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (MWindow::mGetWindow() != NULL)
	{
		return MWindow::mGetWindow()->mOnWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

MWindow::MWindow() :
m_hinstance(NULL),
m_hwnd(NULL),
m_pClassName("MWindow"),
m_pTitleName(""),
m_isAccurite(false),
m_timerGap(100)
{
	m_rect.left = -1;
	m_rect.right = -1;
	m_rect.bottom = -1;
	m_rect.top = -1;
}

MWindow::~MWindow()
{
}

MWindow* MWindow::m_instance = NULL;

MWindow *MWindow::mGetWindow()
{
	return m_instance;
}

void MWindow::mSetTitle(std::string _pTitleName)
{
	m_pTitleName = _pTitleName;
}

void MWindow::mSetRect(RECT &_rect)
{
	m_rect = _rect;
}

void MWindow::mRun(HINSTANCE _hInstance, int _nCmdShow)
{
	m_hinstance = _hInstance;
	if (m_pTitleName.empty())
		m_pTitleName = "MWindow";
	if (m_rect.left == -1 && m_rect.right == -1 
		&& m_rect.bottom == -1 && m_rect.top == -1)
	{
		m_rect.left = 0;
		m_rect.right = 300;
		m_rect.bottom = 300;
		m_rect.top = 0;
	}	
	
	if (!mWindowInit())
	{
		MessageBox(NULL, TEXT("MWindow Init failed"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return;
	}
	ShowWindow(m_hwnd, _nCmdShow);
	UpdateWindow(m_hwnd);
	mOnInit();
	mWindowLoop();
	mWindowEnd();
}

void MWindow::mWndClass()
{
	memset(&m_wc, 0, sizeof(m_wc));
	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	m_wc.style = CS_HREDRAW | CS_VREDRAW;
	m_wc.lpfnWndProc = (WNDPROC)WindowProc;
	m_wc.cbClsExtra = 0;
	m_wc.cbWndExtra = 0;
	m_wc.hInstance = m_hinstance;
	m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	m_wc.lpszClassName = TEXT(m_pClassName.c_str());
}

bool MWindow::mCreateWindow()
{
	m_hwnd = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, 
		TEXT(m_pClassName.c_str()),
		TEXT(m_pTitleName.c_str()),
		WS_POPUP | WS_VISIBLE | WS_SYSMENU,
		m_rect.left, m_rect.top, m_rect.right, m_rect.bottom,
		NULL, NULL, m_hinstance, NULL);
	if (!m_hwnd){
		MessageBox(NULL, TEXT("CreateWindowEx - failed"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

bool MWindow::mWindowInit()
{
	m_instance = this;
	mWndClass();
	if (!mRegisterClass())
	{
		MessageBox(NULL, TEXT("MWindow Register failed"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}
	mCreateWindow();
	return true;
}

bool MWindow::mRegisterClass()
{
	if (!RegisterClassEx(&m_wc))
	{
		MessageBox(NULL, TEXT("RegisterClassEx - failed"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void MWindow::mWindowLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));

	if (m_isAccurite)
	{
		while (TRUE)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			mOnMainLoop();
		}
	}
	else
	{
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}	
}

void MWindow::mWindowEnd()
{
	m_instance = NULL;
	mOnEnd();
	UnregisterClassA(TEXT(m_pClassName.c_str()), m_hinstance);
}

LRESULT CALLBACK MWindow::mOnWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (uMsg)
	{
		HANDLE_MSG(hWnd, WM_COMMAND, MWindow::mOnButtonClick);
	}

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		::SendMessageA(m_hwnd, WM_SYSCOMMAND, 0xF012, 0);
		break;
	case WM_TIMER:
		mOnTimer();
		break;
	case WM_PAINT:
		hdc = BeginPaint(m_hwnd, &ps);
		mOnPaint(hdc);
		EndPaint(m_hwnd, &ps);
		return 0;
	case WM_SIZE:
		break;
	case WM_CLOSE:
		DestroyWindow(m_hwnd);		
		return true;
	case WM_DESTROY:
		PostQuitMessage(0);
		return true;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void MWindow::mOnInit()
{
	if (!m_isAccurite)
		::SetTimer(m_hwnd, ID_TIMER, (UINT)m_timerGap, NULL);
}

void MWindow::mOnMainLoop()
{
}

void MWindow::mOnEnd()
{
}

void MWindow::mOnDestroy()
{
}

void MWindow::mOnTimer()
{
}

void MWindow::mOnPaint(HDC _dc)
{
	SetTextColor(_dc, RGB(255, 0, 0));
	SetBkMode(_dc, TRANSPARENT);
	TextOut(_dc, 0, 0, TEXT("This is my window!"), strlen(TEXT("This is my window!")));
}

void MWindow::mOnButtonClick(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
}