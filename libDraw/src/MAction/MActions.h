#ifndef __MACTIONS_H__
#define __MACTIONS_H__
#include "MPlatform.h"
#include "MObject.h"
#include "MOpacityProtocol.h"
#include "MInterpolation.h"

class MActionManager;
class MActionTarget;
class CC_DLL MAction : public MObject
{
public:
	MAction()		
		: m_past(0.0f)
		, m_delay(0.0f)
		, m_actManager(NULL)
		, m_target(NULL)
		, m_isEnd(false)
		, m_num(1)
	{
	}
	MAction(float _delay)
		: m_past(0.0f)
		, m_delay(_delay)
		, m_actManager(NULL)
		, m_target(NULL)
		, m_isEnd(false)
		, m_num(1)
	{}
	virtual ~MAction() {}
public:
	virtual void update(float dt) = 0;	
	void setManager(MActionManager* _manager) { m_actManager = _manager; }
	virtual void setTarget(MActionTarget* _target) { m_target = _target; }
	bool isEnd() { return m_isEnd; }
	int getNumAction() { return m_num; }
	virtual void remove();	
protected:
	float m_past;
	float m_delay;
	MActionManager* m_actManager;
	MActionTarget* m_target;
	bool m_isEnd;
	int m_num;
};


class CC_DLL MFadeTo : public MAction
{
public:
	MFadeTo()
		:m_opacityDelegate(NULL)
	{}
	MFadeTo(float _delay, BYTE _toOpacity)
		: MAction(_delay)
		, m_toOpacity(_toOpacity)
		, m_opacityDelegate(NULL)
	{}
	static MFadeTo* createFadeTo(BYTE _toOpacity, float _delay);
	virtual void update(float dt);	
	virtual void setTarget(MActionTarget* _target);
protected:
	BYTE m_fromOpacity;
	BYTE m_toOpacity;
	MInterpolation m_calc;
	MOpacityProtocol* m_opacityDelegate;
};

#endif
