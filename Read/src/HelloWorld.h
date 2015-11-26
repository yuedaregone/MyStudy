#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include <windows.h>
#include "MDraw.h"
#include <vector>

class HelloWorld : public MNode
{
public:
	HelloWorld() {};
	~HelloWorld();
	CreateFunc(HelloWorld);
	virtual void init();
public:
	static MScene* scene();
	virtual void draw();
	void clickCakkback(MNode* _pSender);
public:
private:
	void setLabels(uint _labelNum, uint _labelSize);
private:
	std::vector<MLabel*> m_labels;
};

#endif