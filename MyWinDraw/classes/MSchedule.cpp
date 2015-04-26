#include "MSchedule.h"
#include "MPlatform.h"
#include "MCommonFunction.h"

using namespace cFunction;


void MSchedule::setTargetAndSelector(MNode* _node, SEL_Update _sel)
{
	m_obj = _node;
	m_selUpdate = _sel;
}

void MSchedule::update(float _dt)
{	
	if (isFloatEqual(m_timeGap, 0.0f))
	{
		(m_obj->*m_selUpdate)(_dt);
		return;
	}

	MAssert(m_timeGap > 0.0f);

	m_timeCur += _dt;
	if (m_timeCur >= m_timeGap)
	{
		(m_obj->*m_selUpdate)(m_timeCur);
		m_timeCur = 0.0f;
	}
}

bool MSchedule::isEqualSel(SEL_Update _sel)
{
	return m_selUpdate == _sel;
}