#include "AppDelegate.h"
#include "HelloWorld.h"
#include "MDraw.h"

void AppDelegate::appBeforLaunch()
{
	
}

void  AppDelegate::appLaunchFinish()
{
	g_mDirector->isShowFPS(true);	

	MScene* Hello = HelloWorld::scene();
	g_mDirector->runWithScene(Hello);

	g_mDirector->getGraphics()->setOpacity(0);
	MAction* act = MFadeTo::createFadeTo(255, 0.5f);
	g_mDirector->getGraphics()->runAction(act);
}