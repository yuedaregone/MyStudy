#include "Applegate.h"
#include "HelloWorld.h"
#include "MDraw.h"

void Applegate::appBeforLaunch()
{
	
}

void  Applegate::appLaunchFinish()
{
	g_mDirector->isShowFPS(true);	

	MScene* Hello = HelloWorld::scene();
	g_mDirector->runWithScene(Hello);

	//g_mDirector->getGraphics()->setOpacity(0);
	//MAction* act = MFadeTo::createFadeTo(255, 2.0f);
	//g_mDirector->getGraphics()->runAction(act);
}