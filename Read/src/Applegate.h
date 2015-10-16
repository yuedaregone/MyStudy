#ifndef __APPLEGATE_H__
#define __APPLEGATE_H__
#include "..\classes\MApplication.h"

class Applegate : public MApplication
{
public:
	virtual void appBeforLaunch();
	virtual void appLaunchFinish();
};

#endif