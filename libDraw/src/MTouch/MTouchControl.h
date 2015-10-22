#ifndef __MTOUCHCONTROL_H__
#define __MTOUCHCONTROL_H__
#include "MTouchProtocol.h"
#include "../MTool/MSingleton.h"
#include <vector>
class CC_DLL MTouchControl
{
public:

private:
	//std::vector<MTouchProtocol*>m_touches;
};
#define g_mTouchControl MSingleton<MTouchControl>::getInstance()
#endif