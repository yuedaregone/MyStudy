#include "HelloWorld.h"
#include "MButton.h"
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

MLabel* label = NULL;

void HelloWorld::init()
{	
	MNode::init();		

	g_mDirector->getGraphics()->setClearColor(MColor(255,128,128,128));

	label = MLabel::create("qwretdfhgf", 16, MColor(255, 0, 0));
	this->addChild(label, 4);
	label->setPoint(MPoint(0.0f,0.0f));	
	label->setAnchorPoint(MPoint(0.5f,0.3f));

	//MSprite* sp = MSprite::createSprite(103);
	//this->addChild(sp, 2);
	//sp->setAnchorPoint(MPoint(0.3,0.3));
	//sp->setPoint(MPoint(150, 150));
	//sp->setScale(ms(0.5, 0.5));
	 
	MButton* btn = MButton::createButton(103, this, click_selector(HelloWorld::clickCakkback));
	this->addChild(btn, 2);	
	btn->setPoint(MPoint(150, 150));	 
} 

void HelloWorld::draw()
{
	MNode::draw();
}

void HelloWorld::setLabels(uint _labelNum, uint _labelSize)
{
	uint num = m_labels.size();	
	if (_labelNum < num)
	{
		for (uint i = 0; i < num; ++i)
		{
			if (i >= _labelNum)
			{

			}
		}
	}
	if (_labelNum > num)
	{
		
	}
	
}

void HelloWorld::clickCakkback(MNode* _pSender)
{
	
}
