/*MNode.h
 *
 *其中m_worldPoint为屏幕上的坐标，以左下角为原点
 *m_point为相对于MNode的坐标
 *
 */

#ifndef __MNODE_H__
#define __MNODE_H__
#include <map>
#include <vector>
#include "MObject.h"
#include "MShap.h"
#include "MSchedule.h"

#define task_selector(SEL) ((SEL_Update)(&MNode::SEL))
class MyGraphics;
class CC_DLL MNode : public MObject
{
public:
	MNode();
	virtual ~MNode();
	CreateFunc(MNode);
	virtual void init();
public:
	void addChild(MNode* _node, int _z);
	bool removeChild(MNode* _node);
	void removeAllChilden();
	void setParent(MNode* _parent);
	MPoint getWorldPoint() { return m_worldPoint; }
	uint getTag() { return m_tag; }
	void setTag(uint _tag) { m_tag = _tag; }
	int getZOrder() { return m_zorder; }
public:
	const MPoint& getPoint() { return m_point; }
	virtual void setPoint(const MPoint& _p);
	const MSize& getSize() { return m_size; }
	void setSize(const MSize& _s) { m_size = _s; }
public:
	virtual void onEnter();
	virtual void onExit();	
	virtual void visit();
	void setGraphics(MyGraphics* _g) { m_graphics = _g; }
	MyGraphics* getGraphics() { return m_graphics; }
public:
	void scheduleTask(SEL_Update _sel, float dt);
	void unscheduleTask(SEL_Update _sel);
	void unscheduleAllTask();
	void update(float dt);
protected:
	virtual void draw();
	void setWorldPoint();
protected:
	std::multimap<int, MNode*>* m_childen;
	uint m_tag;
	int m_zorder;
	MNode* m_parent;
	MPoint m_worldPoint;
	MPoint m_point;
	MSize m_size;
	std::vector<MSchedule*>* m_vSchedule;
	MyGraphics* m_graphics;
};



#endif