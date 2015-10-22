#include "ImageMgr.h"
#include <assert.h>
#include <windows.h>
using namespace Gdiplus;

ImageMgr::ImageMgr(void)
{
	m_images = new std::map<int, Gdiplus::Image*>();
}


ImageMgr::~ImageMgr(void)
{
	delete m_images;
}

void ImageMgr::LoadMyImage(int _begin, int _end, const char* _type)
{	
	for (int i = _begin; i <= _end; ++i)
	{
		m_images->insert(std::map<int, Gdiplus::Image*>::value_type(i, LoadResImage(LPCTSTR(i), TEXT(_type))));
	}
}

void ImageMgr::LoadMyImage(std::vector<int>& _vKeys, const char* _type)
{
	for (std::vector<int>::iterator it = _vKeys.begin(); it != _vKeys.end(); ++it)
	{
		int key = *it;
		m_images->insert(std::map<int, Gdiplus::Image*>::value_type(key, LoadResImage(LPCTSTR(key), TEXT(_type))));
	}
}

Image* ImageMgr::getImageByKey(int index)
{
	if (m_images->find(index) == m_images->end())
		return NULL;
	return (*m_images)[index];
}

Image* ImageMgr::LoadResImage(LPCTSTR lpName,LPCTSTR lpType)
{
	HINSTANCE hIns=::GetModuleHandle(NULL);
	HRSRC hRsrc = ::FindResource (hIns,lpName,lpType); // type 
	if (!hRsrc) 
		return NULL; 
	// load resource into memory 
	DWORD len = SizeofResource(hIns, hRsrc); 
	BYTE* lpRsrc = (BYTE*)LoadResource(hIns, hRsrc); 
	if (!lpRsrc) 
		return NULL; 
	// Allocate global memory on which to create stream 
	HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, len); 
	BYTE* pmem = (BYTE*)GlobalLock(hMem); 
	memcpy(pmem,lpRsrc,len); 
	IStream* pstm; 
	CreateStreamOnHGlobal(hMem,FALSE,&pstm); 
	// load from stream 
	Gdiplus::Image* pImage=Gdiplus::Image::FromStream(pstm); 
	// free/release stuff 
	GlobalUnlock(hMem); 
	pstm->Release(); 
	FreeResource(lpRsrc);
	return pImage;
}