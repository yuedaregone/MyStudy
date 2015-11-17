#ifndef __MAPPLICATIONPROTOCOL_H__
#define __MAPPLICATIONPROTOCOL_H__
#include "MPlatform.h"
class CC_DLL MApplicationProtocol
{
public:
	MApplicationProtocol() : m_isAccurite(false) {}
	virtual ~MApplicationProtocol(){};	
public:
	virtual void mOnInit(int x, int y, int w, int h) = 0;
	virtual void mOnDestroy() = 0;
	virtual void mOnTimer() = 0;
	virtual void mOnMainLoop() = 0;
	virtual void mSetHWND(void* _hwnd) = 0;	
	bool mIsAccurite() { return m_isAccurite; }
	void mSetIsAccurite(bool _isAccurite) { m_isAccurite = _isAccurite; }
	virtual bool mIsEnd() { return m_isEnd; }
	virtual void mSetEnd(bool _isEnd) { m_isEnd = _isEnd; }
protected:
	bool m_isAccurite;
	bool m_isEnd;
};

#endif