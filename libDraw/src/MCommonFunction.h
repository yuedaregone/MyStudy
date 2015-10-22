#ifndef __MCOMMONFUNCTION_H__
#define __MCOMMONFUNCTION_H__
#include <time.h> 
#include <windows.h>
#include "MShap.h"
namespace cFunction
{
	CC_DLL struct tm getCurTime();
	CC_DLL bool isFloatEqual(float _a, float _b);
	CC_DLL wchar_t* utf8ToUnicode(const char* _str, int& _len);
	CC_DLL char* UnicodeToUtf8(const wchar_t* _str);
	CC_DLL float getDistancePower(const MPoint& _p1, const MPoint& _p2);
	CC_DLL void MLog(const char * pszFormat, ...);
};
#endif