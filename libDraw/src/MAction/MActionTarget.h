#ifndef __MACTIONTARGET_H__
#define __MACTIONTARGET_H__
#include "MPlatform.h"
#include "MActions.h"

class MAction;
class CC_DLL MActionTarget : public MObject
{
public:
	MActionTarget()
		: m_numActions(0)
	{}
	virtual ~MActionTarget() {}
	virtual void runAction(MAction* _action) { m_numActions += _action->getNumAction(); }
	void removeAction(MAction* _action) { m_numActions -= _action->getNumAction(); }
	bool isActing() { return m_numActions != 0; }
protected:
	int m_numActions;	
};


#endif