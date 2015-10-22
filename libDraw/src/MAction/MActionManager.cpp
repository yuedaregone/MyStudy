#include "MActionManager.h"

MActionManager::MActionManager()
{
	m_actions = new std::vector<MAction*>();
}

MActionManager::~MActionManager()
{
	delete m_actions;
}

void MActionManager::addAction(MAction* _action)
{
	_action->setManager(this);
	m_actions->push_back(_action);
}

void MActionManager::update(float dt)
{
	if (m_actions->empty())
	{
		return;
	}
	std::vector<MAction*>::iterator it = m_actions->begin();
	for (; it != m_actions->end();)
	{
		(*it)->update(dt);
		if ((*it)->isEnd())
		{
			(*it)->remove();
			it = m_actions->erase(it);
		}
		else
		{
			++it;
		}
	}
}
