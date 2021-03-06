#ifndef __MOBJECT_H__
#define __MOBJECT_H__
#include <stdio.h>
#include <vector>
#include <string>
#include "MPlatform.h"
class MNode;
class CC_DLL MObject
{
public:	
	MObject();
	virtual ~MObject();	
	virtual void remove() { delete this; }	
private:
	static int m_numOfObj;
	uint m_objId;
};

typedef void (MObject::*DragFileCallBack)(const std::vector<std::string>& files);
typedef void (MObject::*ClickCallback)(MNode* _node);

#define drag_selector(SEL) ((DragFileCallBack)(&SEL))
#define click_selector(SEL) ((ClickCallback)(&SEL))
#endif