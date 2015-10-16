#ifndef __MAPPLICATIONPROTOCOL_H__
#define __MAPPLICATIONPROTOCOL_H__

class MApplicationProtocol
{
public:
	~MApplicationProtocol(){};
	virtual void appBeforLaunch() = 0;
	virtual void appLaunchFinish() = 0;
};

#endif