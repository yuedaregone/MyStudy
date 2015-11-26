#ifndef __MSPRITEIMPL_H_
#define __MSPRITEIMPL_H_
#include "MyGraphics.h"
#include "MShap.h"
#include <gdiplus.h>
class CC_DLL MSpriteImpl
{
public:
	MSpriteImpl();
	~MSpriteImpl();
	void init(int _imageId, MSize& _size);
	void drawImage(const MPoint& _p, const MSize& _size);
private:
	MyGraphics* m_g;
	int m_key;
	Gdiplus::Image* m_image;	
};
#endif