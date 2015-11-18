#ifndef __MTOUCHCONTROL_H__
#define __MTOUCHCONTROL_H__
#include "../MTool/MSingleton.h"
#include "MShap.h"
#include <map>
#include <vector>
class MTouchProtocol;
class CC_DLL MTouchControl : public MSingleton<MTouchControl>
{
public:
	MTouchControl();
	~MTouchControl();
public:
	void registerTouchCallback(int priority, MTouchProtocol* _touch);
	void unregisterTouch(MTouchProtocol* _touch);

	void mTouchBegin(const MPoint& _p);
	void mTouchMove(const MPoint& _p);
	void mTouchEnd(const MPoint& _p);
private:
	std::map<int, std::vector<MTouchProtocol*> >* m_touches;
	MTouchProtocol* m_curTouch;
};
#define g_mTouchControl MTouchControl::getInstance()
#endif