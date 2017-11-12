#ifndef __APPDELEGATE_H__
#define __APPDELEGATE_H__
#include "MApplication.h"

class AppDelegate : public MApplication
{
public:
	virtual void appBeforLaunch();
	virtual void appLaunchFinish();
};

#endif