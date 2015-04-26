#include "Applegate.h"
#include "HelloWorld.h"
#include "../classes/MDirector.h"

void Applegate::appBeforLaunch()
{
	m_isAccurite = true;
	m_timerGap = 16; //����timer
}

void  Applegate::appLaunchFinish()
{
	MScene* Hello = HelloWorld::scene();
	g_mDirector->runWithScene(Hello);
}