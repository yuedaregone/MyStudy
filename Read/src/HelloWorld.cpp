#include "HelloWorld.h"
#include "MDraw.h"
#include "MActions.h"
using namespace cFunction;
HelloWorld::~HelloWorld()
{	
}

MScene* HelloWorld::scene()
{
	MScene* sc = MScene::create();
	HelloWorld* hello = HelloWorld::create();
	sc->addChild(hello, 0);
	return sc;
}

void HelloWorld::init()
{	
	MNode::init();		

	//g_mDirector->getGraphics()->setClearColor(MColor(255,255,255,255));

	MLabel* label = MLabel::create("qwretdfhgf", 16, MColor(255, 0, 0));
	this->addChild(label, 4);
	label->setPoint(MPoint(0,300));	

	MSprite* sp = MSprite::createSprite(103);
	this->addChild(sp, 2);
	sp->setPoint(MPoint(-10, 10));
}

void HelloWorld::draw()
{
	MNode::draw();
}
