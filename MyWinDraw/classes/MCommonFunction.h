#ifndef __MCOMMONFUNCTION_H__
#define __MCOMMONFUNCTION_H__
#include <time.h> 
#include <windows.h>
#include "MShap.h"
namespace cFunction
{
	struct tm getCurTime();
	bool isFloatEqual(float _a, float _b);
	wchar_t* utf8ToUnicode(const char* _str);
	char* UnicodeToUtf8(const wchar_t* _str);
	float getDistancePower(const MPoint& _p1, const MPoint& _p2);
	void MLog(const char * pszFormat, ...);
};
#endif