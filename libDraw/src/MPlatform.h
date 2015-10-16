#ifndef __MPLATFORM_H__
#define __MPLATFORM_H__
#include <assert.h>
#include <windows.h>

typedef unsigned int				uint;
typedef unsigned char				BYTE;
typedef unsigned short				ushort;

#ifdef _DEBUG
#define MAssert(conf) assert(conf);
#else
#define MAssert(conf) do{}while(0);
#endif // _DEBUG

#define CreateFunc(CName)	static CName* create() \
{ \
	CName* pRet = new CName(); \
	pRet->init(); \
	return pRet; \
}
#define RemoveObj(obj)		do {if (obj){ delete obj; obj = NULL;}} while (0);

#endif