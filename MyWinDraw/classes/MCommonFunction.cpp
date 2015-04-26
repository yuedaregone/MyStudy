#include "MCommonFunction.h"
#include <stdio.h>
#define MAX_LEN 16384
namespace cFunction
{
	struct tm getCurTime()
	{
		struct tm timeNow;
		time_t long_time;
		time(&long_time);
		localtime_s(&timeNow, &long_time);
		return timeNow;
	}

	bool isFloatEqual(float _a, float _b)
	{
		float c = _a - _b;
		c = c > 0.0f ? c : -c;
		if (c < 0.0001f)
			return true;
		return false;
	}

	wchar_t* utf8ToUnicode(const char* _str)
	{
		int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, _str, -1, NULL, 0);
		if (nLen == 0)
		{
			return NULL;
		}
		wchar_t* pResult = new wchar_t[nLen];
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, _str, -1, pResult, nLen);
		return pResult;
	}

	char* UnicodeToUtf8(const wchar_t* _str)
	{
		int nLen = WideCharToMultiByte(CP_ACP, 0, _str, -1, NULL, 0, NULL, NULL);
		if (nLen == 0)
		{
			return NULL;
		}
		char* pResult = new char[nLen];
		WideCharToMultiByte(CP_ACP, 0, _str, -1, pResult, nLen, NULL, NULL);
		return pResult;
	}

	float getDistancePower(const MPoint& _p1, const MPoint& _p2)
	{
		return (_p1.x - _p2.x)*(_p1.x - _p2.x) + (_p1.y - _p2.y)*(_p1.y - _p2.y);
	}
	void MLog(const char * pszFormat, ...)
	{
		char szBuf[MAX_LEN];

		va_list ap;
		va_start(ap, pszFormat);
		vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
		va_end(ap);

		WCHAR wszBuf[MAX_LEN] = { 0 };
		MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
		OutputDebugStringW(wszBuf);
		OutputDebugStringA("\n");

		WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
		printf("%s\n", szBuf);
	}
};
