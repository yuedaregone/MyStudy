// DotMatrix.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <map>
#include <vector>
#include "MImage.h"
#include <fstream>

void fun_turnWordToDot()
{
	HDC dc = GetDC(NULL);

	LOGFONT font;
	font.lfHeight = 16;
	font.lfWidth = 16;
	font.lfEscapement = 0;
	font.lfOrientation = 0;
	font.lfWeight = FW_THIN;
	font.lfItalic = false;
	font.lfUnderline = false;
	font.lfStrikeOut = false;
	font.lfCharSet = CHINESEBIG5_CHARSET;
	font.lfOutPrecision = OUT_CHARACTER_PRECIS;
	font.lfClipPrecision = CLIP_CHARACTER_PRECIS;
	font.lfQuality = DEFAULT_QUALITY;
	font.lfPitchAndFamily = FF_MODERN;
	wmemcpy(font.lfFaceName, L"宋体", sizeof(L"宋体") / sizeof(wchar_t));

	setlocale(LC_ALL, "chs");
	wprintf(L"字体大小:\n");
	int fontSize = 16;
	std::cin >> fontSize;
	getchar();
	font.lfHeight = font.lfWidth = fontSize;
	wchar_t ch = L'蔡';

	while (1)
	{
		wscanf(L"%c", &ch);
		if (ch == 0)
		{
			break;
		}
		wchar_t ch1 = 0;
		while ((ch1 = getchar()) != '\n')
			continue;
		HFONT hFont = CreateFontIndirect(&font);
		HFONT oldFont = (HFONT)SelectObject(dc, hFont);		
		MAT2 mat2 = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };

		GLYPHMETRICS gm = { 0 };
		DWORD retByte = GetGlyphOutline(dc, ch, GGO_BITMAP, &gm, 0, NULL, &mat2);
		if (retByte == GDI_ERROR)
		{
			printf("error");
			return;
		}
		unsigned char* buffStr = new unsigned char[retByte];
		memset(buffStr, 0, retByte);
		GetGlyphOutline(dc, ch, GGO_BITMAP, &gm, retByte, buffStr, &mat2);

		int nByteCount = ((gm.gmBlackBoxX + 31) >> 5) << 2;
		for (int i = 0; i < gm.gmBlackBoxY; ++i)
		{
			for (int j = 0; j < nByteCount; ++j)
			{
				BYTE w = *((BYTE*)buffStr + i * nByteCount + j);
				for (int k = 8; k > 0; --k)
				{
					BYTE index = 1 << (k - 1);
					BYTE temp = w & index;
					if (temp > 0)
					{
						printf("*");
					}
					else
					{
						printf(".");
					}
				}
			}
			printf("\n");
		}

		SelectObject(dc, oldFont);
		DeleteObject(hFont);
	}
	ReleaseDC(NULL, dc);
}

void fun_calcGrayAscall(std::map<int, std::vector<char> >& ascallGray)
{
	ascallGray.clear();
	std::vector<char> v0;
	v0.push_back(32);
	ascallGray.insert(std::map<int, std::vector<char> >::value_type(0, v0));

	HDC dc = GetDC(NULL);
	LOGFONT font;
	font.lfHeight = 16;
	font.lfWidth = 16;
	font.lfEscapement = 0;
	font.lfOrientation = 0;
	font.lfWeight = FW_THIN;
	font.lfItalic = false;
	font.lfUnderline = false;
	font.lfStrikeOut = false;
	font.lfCharSet = CHINESEBIG5_CHARSET;
	font.lfOutPrecision = OUT_CHARACTER_PRECIS;
	font.lfClipPrecision = CLIP_CHARACTER_PRECIS;
	font.lfQuality = DEFAULT_QUALITY;
	font.lfPitchAndFamily = FF_MODERN;
	wmemcpy(font.lfFaceName, L"宋体", sizeof(L"宋体") / sizeof(wchar_t));
	setlocale(LC_ALL, "chs");
	HFONT hFont = CreateFontIndirect(&font);
	HFONT oldFont = (HFONT)SelectObject(dc, hFont);

	for (int i = 33; i < 127; ++i)
	{
		if ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || (i >= '0' && i <= '9'))
		{
			continue;
		}
		char ch = i;
		MAT2 mat2 = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };

		GLYPHMETRICS gm = { 0 };
		DWORD retByte = GetGlyphOutline(dc, ch, GGO_BITMAP, &gm, 0, NULL, &mat2);
		if (retByte == GDI_ERROR)
		{
			printf("error");
			return;
		}
		unsigned char* buffStr = new unsigned char[retByte];
		memset(buffStr, 0, retByte);
		GetGlyphOutline(dc, ch, GGO_BITMAP, &gm, retByte, buffStr, &mat2);

		int dotNum = 0;		
		int nByteCount = ((gm.gmBlackBoxX + 31) >> 5) << 2;
		for (int i = 0; i < gm.gmBlackBoxY; ++i)
		{
			for (int j = 0; j < nByteCount; ++j)
			{
				BYTE w = *((BYTE*)buffStr + i * nByteCount + j);
				for (int k = 8; k > 0; --k)
				{
					BYTE index = 1 << (k - 1);
					BYTE temp = w & index;
					if (temp > 0)
						++dotNum;
				}
			}			
		}	
		ascallGray[dotNum].push_back(ch);		
	}

	SelectObject(dc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, dc);	
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::map<int, std::vector<char> > ascallGray;
	fun_calcGrayAscall(ascallGray);

	MImage img;
	img.initWithFile("as.png", MImage::typePNG);
	BYTE* _data = img.getData();
	size_t _size = img.getDataSize();
	unsigned short w = img.getWidth();
	int off = 3;
	if (img.isHasAlpha())
	{
		off = 4;
	}	
	std::ofstream stream("a.txt");
	int k = 0;
	int h = w*off;
	for (int i = 0; i < _size; i += off)
	{
		if (i != 0 && i % h == 0)
		{
			k++;
			stream << "\n";
			if (k == 1)
			{
				i += h;
				if (i > _size || (_size - i < h))
				{
					break;
				}
				k = 0;
			}
			
		}

		float gray = (_data[i] * 30 + _data[i + 1] * 59 + _data[i + 2] * 11) / 100.0f;		
		int index = (int)(gray / 255.0f*ascallGray.size());
		index = index > ascallGray.size() ? ascallGray.size() : index;
		index = ascallGray.size() - index;

		int j = 0;
		std::map<int, std::vector<char> >::iterator it = ascallGray.begin();
		for (; it != ascallGray.end(); ++it, ++j)
		{
			if (j == index)
			{							
				stream << it->second.back();
				break;
			}
		}		
	}
	stream.close();
	return 0;
}

