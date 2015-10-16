#ifndef __MSCENE_H__
#define __MSCENE_H__
#include "MNode.h"

class MScene : public MNode
{
public:
	MScene();
	virtual ~MScene();
	virtual void init();
	CreateFunc(MScene);
private:
	virtual void draw() {};
};

#endif