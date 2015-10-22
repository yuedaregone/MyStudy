#ifndef __MACTIONMANAGER_H__
#define __MACTIONMANAGER_H__
#include "MPlatform.h"
#include "MActions.h"
#include <vector>

class MActionManager
{
public:
	MActionManager();
	~MActionManager();
public:
	void addAction(MAction* _action);
	void update(float dt);	
private:
	std::vector<MAction*>* m_actions;
};

#endif