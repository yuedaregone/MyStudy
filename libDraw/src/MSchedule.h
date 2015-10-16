#ifndef __MSCHEDULE_H__
#define __MSCHEDULE_H__
#include <stdio.h>

class MNode;
typedef void (MNode::*SEL_Update)(float dt);

class MSchedule
{
public:
	MSchedule() :m_timeGap(0.0f), m_timeCur(0.0f), m_selUpdate(NULL), m_obj(NULL){};	
	~MSchedule(){};
	void setGap(float _gap) { m_timeGap = _gap; }
	void setTargetAndSelector(MNode* _node, SEL_Update _sel);
	void update(float _dt);
	bool isEqualSel(SEL_Update _sel);
private:
	float m_timeGap;
	float m_timeCur;
	SEL_Update m_selUpdate;
	MNode* m_obj;
};
#endif