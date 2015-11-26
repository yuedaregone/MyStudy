/*MNode.h
 *
 *����m_worldPointΪ��Ļ�ϵ����꣬�����½�Ϊԭ��
 *m_pointΪ�����MNode������
 *
 */

#ifndef __MNODE_H__
#define __MNODE_H__
#include <map>
#include <vector>
#include "MObject.h"
#include "MShap.h"
#include "MSchedule.h"
#include "MActionTarget.h"
#define task_selector(SEL) ((SEL_Update)(&MNode::SEL))
class MyGraphics;
class CC_DLL MNode : public MActionTarget
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
	virtual void setSize(const MSize& _s);
	const MPoint& getAnchorPoint() { return m_anchorPoint; }
	virtual void setAnchorPoint(const MPoint& _ap);
	virtual void setScale(const MSize& _scale);	
	const MSize& getRealSize() { return m_realSize; }
	const MSize& getScale() { return m_scale; }
	MRect boundingBox();
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
	void resetRealPoint();
	void resetRealSize();
protected:
	std::multimap<int, MNode*>* m_childen;
	uint m_tag;
	int m_zorder;
	MNode* m_parent;
	MPoint m_worldPoint;
	MPoint m_point;
	MPoint m_anchorPoint;
	MPoint m_realPoint;
	MSize m_size;
	MSize m_realSize;
	MSize m_scale;
	std::vector<MSchedule*>* m_vSchedule;
	MyGraphics* m_graphics;
};



#endif