#ifndef __MOPACITYPROTOCOL_H__
#define __MOPACITYPROTOCOL_H__
#include "MPlatform.h"
class CC_DLL MOpacityProtocol
{
public:
	virtual ~MOpacityProtocol() {}
	virtual void setOpacity(BYTE _alpha) = 0;
	virtual BYTE getOpacity() = 0;
};

#endif