#ifndef __MBUTTON_H__
#define __MBUTTON_H__
#include "MNode.h"
#include "MTouchProtocol.h"
#define TOUCH_PRIORITY_DEFAULT -1
class MSprite;
class CC_DLL MButton : public MNode, public MTouchProtocol
{
public:
	MButton() : MTouchProtocol(TOUCH_PRIORITY_DEFAULT), m_spShow(NULL), m_target(NULL), m_callback(NULL), m_isTouched(false){}
	static MButton* createButton(int _key, MObject* _target = NULL,ClickCallback _callbak = NULL);
	void initButton(int _key);
	void setTarget(MObject* _target, ClickCallback _callbak);
public:
	virtual bool mTouchBegin(const MPoint& _p);
	virtual void mTouchMove(const MPoint& _p);
	virtual void mTouchEnd(const MPoint& _p);
protected:
	MSprite* m_spShow;
	MObject* m_target;
	ClickCallback m_callback;
	bool m_isTouched;
};

#endif