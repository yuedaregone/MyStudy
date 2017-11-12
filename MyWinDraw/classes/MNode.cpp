#include "MNode.h"

MNode::MNode()
	: m_tag(0)
	, m_zorder(0)
	, m_parent(NULL)
	, m_worldPoint(0.0f, 0.0f)
	, m_point(0.0f, 0.0f)
	, m_size(0.0f, 0.0f)
	, m_graphics(NULL)
	, m_vSchedule(NULL)
{
	m_childen = new std::multimap<int, MNode*>();
}

MNode::~MNode()
{
	if (m_vSchedule)
	{
		delete m_vSchedule;
	}
	if (m_childen)
	{
		delete m_childen;
	}
}

void MNode::init()
{
}

void MNode::addChild(MNode* _node, int _z)
{
	m_zorder = _z;
	_node->onEnter();
	_node->setParent(this);
	_node->setGraphics(m_graphics);
	m_childen->insert(std::make_pair(m_zorder, _node));
}

bool MNode::removeChild(MNode* _node)
{
	_node->onExit();
	_node->removeAllChilden();
	_node->setParent(NULL);
	bool isFind = false;

	int z = _node->getZOrder();
	for (std::multimap<int, MNode*>::iterator it = m_childen->begin();
		it != m_childen->end(); ++it)
	{
		if (z == it->first)
		{
			if (_node == it->second)
			{
				isFind = true;
				m_childen->erase(it);
				break;
			}
		}
		else if (z > it->first)
		{
			break;
		}
	}
	if (isFind)
	{
		_node->remove();
	}
	return isFind;
}

void MNode::removeAllChilden()
{
	for (std::multimap<int, MNode*>::iterator it = m_childen->begin();
		it != m_childen->end(); ++it)
	{
		it->second->onExit();
		it->second->removeAllChilden();
		it->second->remove();
	}
	m_childen->clear();
}

void MNode::setParent(MNode* _parent)
{	
	m_parent = _parent;
}

void MNode::setPoint(const MPoint& _p)
{ 
	MAssert(m_parent != NULL);
	m_point = _p;
	setWorldPoint();
	std::multimap<int, MNode*>::iterator it = m_childen->begin();
	for (; it != m_childen->end(); ++it)
	{
		it->second->setWorldPoint();
	}
}

void MNode::setWorldPoint()
{
	if (m_parent)
		m_worldPoint = m_point + m_parent->getWorldPoint();
}

void MNode::onEnter()
{
}

void MNode::onExit()
{
	unscheduleAllTask();
}

void MNode::draw()
{
	if (!m_graphics)
	{
		m_graphics = m_parent->getGraphics();
	}
}

void MNode::visit()
{
	std::multimap<int, MNode*>::iterator it = m_childen->begin();
	for (; it != m_childen->end(); ++it)
	{
		if (it->first < 0)
		{
			it->second->visit();
		}
		else
		{
			break;
		}
	}
	this->draw();
	for (; it != m_childen->end(); ++it)
	{
		it->second->visit();
	}
}

void MNode::scheduleTask(SEL_Update _sel, float dt)
{
	if (!m_vSchedule)
	{
		m_vSchedule = new std::vector<MSchedule*>();
	}

	MSchedule* sd = new MSchedule();
	sd->setGap(dt);
	sd->setTargetAndSelector(this, _sel);
	m_vSchedule->push_back(sd);
}

void MNode::unscheduleTask(SEL_Update _sel)
{
	if (!m_vSchedule) return;
	for (std::vector<MSchedule*>::iterator it = m_vSchedule->begin();
		it != m_vSchedule->end(); ++it)
	{
		if ((*it)->isEqualSel(_sel))
		{
			delete (*it);
			m_vSchedule->erase(it);
			break;
		}		 
	}
}

void MNode::unscheduleAllTask()
{
	if (!m_vSchedule) return;
	for (std::vector<MSchedule*>::iterator it = m_vSchedule->begin();
		it != m_vSchedule->end(); ++it)
	{
		delete (*it);		
	}
	m_vSchedule->clear();
}

void MNode::update(float dt)
{
	if (m_vSchedule != NULL)
	{
		for (std::vector<MSchedule*>::iterator it = m_vSchedule->begin();
			it != m_vSchedule->end(); ++it)
		{
			(*it)->update(dt);
		}
	}	

	std::multimap<int, MNode*>::iterator it = m_childen->begin();
	for (; it != m_childen->end(); ++it)
	{
		it->second->update(dt);
	}
}