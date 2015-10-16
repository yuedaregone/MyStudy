#ifndef __MSPRITEIMPL_H_
#define __MSPRITEIMPL_H_
#include "MyGraphics.h"
#include "MShap.h"
#include <gdiplus.h>
class MSpriteImpl
{
public:
	MSpriteImpl();
	~MSpriteImpl();
	void init(int _imageId);	
	void drawImage(const MPoint& _p);
	MSize getContentSize() { return m_size; }
private:
	MyGraphics* m_g;
	int m_key;
	Gdiplus::Image* m_image;
	MSize m_size;
};
#endif