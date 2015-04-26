#ifndef __MOBJECT_H__
#define __MOBJECT_H__
#include <stdio.h>
#include "MPlatform.h"

class MObject
{
public:	
	MObject();
	virtual ~MObject();	
	void remove() { delete this; }	
private:
	static int m_numOfObj;
	uint m_objId;
};

#endif