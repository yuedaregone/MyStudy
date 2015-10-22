#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include <windows.h>
#include <gdiplus.h>
#include "MNode.h"
#include "MScene.h"
#include "MSprite.h"


class HelloWorld : public MNode
{
public:
	HelloWorld() {};
	~HelloWorld();
	CreateFunc(HelloWorld);
	virtual void init();
public:
	static MScene* scene();
	virtual void draw();	
private:	
};

#endif