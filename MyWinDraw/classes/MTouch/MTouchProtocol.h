#ifndef __MTOUCHPROTOCOL__H__
#define __MTOUCHPROTOCOL__H__
#include "../MShap.h"
class MTouchProtocol
{
public:
	virtual ~MTouchProtocol() {}
	virtual void registerTouchDispatcher() = 0;
	virtual bool mTouchBegin(const MPoint& _p) = 0;
	virtual void mTouchMove(const MPoint& _p) = 0;
	virtual void mTouchEnd(const MPoint& _p) = 0;
};
#endif