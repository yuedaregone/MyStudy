#include "MActions.h"
#include "MInterpolation.h"
#include "MActionManager.h"
#include "MCommonFunction.h"
#include "MActionTarget.h"
#include "MDirector.h"

int MAction::m_actSum = 0;

void MAction::addAction()
{
	++m_actSum;
	g_mDirector->setApplicationAccurite(true);
}

void MAction::reduceAction()
{
	--m_actSum;
	if (m_actSum<=0)
	{
		g_mDirector->setApplicationAccurite(false);
	}
}

void MAction::remove()
{
	m_target->removeAction(this);
	MObject::remove();
}

MFadeTo* MFadeTo::createFadeTo(BYTE _toOpacity, float _delay)
{
	MFadeTo* ret = new MFadeTo(_delay, _toOpacity);
	return ret;
}

void MFadeTo::update(float dt)
{
	if (m_opacityDelegate)
	{
		m_past += dt;
		if (m_past > m_delay)
		{
			m_opacityDelegate->setOpacity(m_toOpacity);
			m_isEnd = true;
			return;
		}

		BYTE targetOpacity = m_calc.getSineInterpolation<int>(m_fromOpacity, m_toOpacity, m_past, m_delay);
		m_opacityDelegate->setOpacity(targetOpacity);
	}	
}

void MFadeTo::setTarget(MActionTarget* _target)
{	
	MAction::setTarget(_target);	
	m_opacityDelegate = dynamic_cast<MOpacityProtocol*>(_target);
	if (m_opacityDelegate)
	{
		m_fromOpacity = m_opacityDelegate->getOpacity();
	}	
}

