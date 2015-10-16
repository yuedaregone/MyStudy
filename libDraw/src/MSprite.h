#ifndef __MSPRITE_H__
#define __MSPRITE_H__
#include "MNode.h"
#include "MImpl/MSpriteImpl.h"
class MSprite : public MNode
{
public:
	MSprite();
	~MSprite();
	CreateFunc(MSprite);
	static MSprite* createSprite(int _key);
	bool initSprite(int _key);	
private:
	virtual void draw();
private:
	int m_key;
	MSpriteImpl* m_spImpl;
};


#endif