#pragma once
#include <windows.h>
#include <gdiplus.h>
#include "MTool/MSingleton.h"
#include <map>
#include <vector>
class Gdiplus::Image;
class CC_DLL ImageMgr : public MSingleton<ImageMgr>
{
public:
	ImageMgr(void);
	~ImageMgr(void);
public:	
	Gdiplus::Image* getImageByKey(int index);
	void LoadMyImage(int _begin, int _end, const char* _type = "PNG");
	void LoadMyImage(std::vector<int>& _vKeys, const char* _type = "PNG");
private:	
	Gdiplus::Image* LoadResImage(LPCTSTR lpName, LPCTSTR lpType);	
private:
	std::map<int, Gdiplus::Image*>* m_images;
};

#define g_imageMgr ImageMgr::getInstance()
