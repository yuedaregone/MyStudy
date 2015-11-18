#ifndef __MTOUCHPROTOCOL__H__
#define __MTOUCHPROTOCOL__H__
#include "../MShap.h"
#include "MTouchControl.h"
class CC_DLL MTouchProtocol
{
public:
	MTouchProtocol(int _priority)
	{
		m_id = m_touchIndex++;
		g_mTouchControl->registerTouchCallback(_priority, this);
	}
	virtual ~MTouchProtocol() 
	{
		g_mTouchControl->unregisterTouch(this);
	}	
	virtual bool mTouchBegin(const MPoint& _p) = 0;
	virtual void mTouchMove(const MPoint& _p) = 0;
	virtual void mTouchEnd(const MPoint& _p) = 0;	
	int getId() { return m_id; }
private:
	static int m_touchIndex;
	int m_id;
};

int MTouchProtocol::m_touchIndex = 0;
#endif