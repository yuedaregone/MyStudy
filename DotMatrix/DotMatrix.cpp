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
//#include "string_common.h"
#include <atlstr.h>

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
		//if ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || (i >= '0' && i <= '9'))
		{
		//	continue;
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

void findAllFile(std::vector<CString>& vStrFile, CString lpPath)
{
	CString szFind;
	CString szFile;

	WIN32_FIND_DATA FindFileData;
	szFind = lpPath;
	szFind = szFind + "\\*.*";

	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind) return;
	while (::FindNextFile(hFind, &FindFileData))
	{
		CString fileName = FindFileData.cFileName;
		if (fileName.Compare(L".") == 0 || fileName.Compare(L"..") == 0)
		{
			continue;
		}
		szFile = lpPath;
		szFile = szFile + "\\";
		szFile = szFile + fileName;

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			findAllFile(vStrFile, szFile);
		}
		else
		{
			int index = fileName.Find(L'.');
			CString houzhui = fileName.Right(fileName.GetLength() - index);
			if (houzhui.Compare(L".png") == 0)
			{
				vStrFile.push_back(szFile);
			}
		}
	}
	FindClose(hFind);
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::map<int, std::vector<char> > ascallGray;
	fun_calcGrayAscall(ascallGray);

	wchar_t* pathFile = argv[0];
	char buff[1024] = { 0 };
	wcstombs(buff, pathFile, 1024);
	std::string strPath = buff;
	strPath = strPath.substr(0, strPath.rfind("\\"));
	
	std::vector<CString> vFiles;
	findAllFile(vFiles, strPath.c_str());
	
	std::vector<CString>::iterator it = vFiles.begin();
	for (; it != vFiles.end(); ++it)
	{
		CString& file = *it;
		memset(buff, 0, 1024);
		wcstombs(buff, file.GetString(), 1024);
		std::string fileTxt = buff;		
		fileTxt = fileTxt.substr(0, fileTxt.find_last_of("."));
		fileTxt = fileTxt.substr(fileTxt.find_last_of("\\")+1, fileTxt.length());
		fileTxt += ".txt";

		MImage img;
		img.initWithFile(buff, MImage::typePNG);
		BYTE* _data = img.getData();
		size_t _size = img.getDataSize();
		unsigned short w = img.getWidth();
		int off = 3;
		if (img.isHasAlpha())
		{
			off = 4;
		}
		std::ofstream stream(fileTxt);
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

			int grayMax = ascallGray.rbegin()->first;
			float gray = (_data[i] * 30 + _data[i + 1] * 59 + _data[i + 2] * 11) / 100.0f;
			int index = (int)(gray / 255.0f*grayMax);
			index = index > grayMax ? grayMax : index;
			index = grayMax - index;

			std::map<int, std::vector<char> >::iterator it = ascallGray.find(index);
			if (it != ascallGray.end())
			{
				stream << it->second.back();
			}
			else
			{
				bool isFind = false;
				do
				{
					if ((it = ascallGray.find(--index)) != ascallGray.end())
					{
						isFind = true;
						stream << it->second.back();
					}
				} while (!isFind && index >= 0);
				if (!isFind)
				{
					stream << ascallGray.begin()->second.back();
				}
			}				
		}
		stream.close();
	}
	return 0;
}

