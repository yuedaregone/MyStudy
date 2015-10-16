#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>
using namespace std;

void CodeInfo(int *start,int *CodeSize)
{
	DWORD s,e;
	_asm
	{
		push eax
		mov eax,begin1
		mov s,eax
		mov eax,end1
		mov e,eax
		jmp end1
		begin1:
		//这里放你需要的汇编代码
		mov eax,42969AH
		jmp eax
		end1:
		pop eax
	}
	*start=s;
	*CodeSize=e-s;
}

BOOL IsPeFile(LPVOID  ImageBase)   //判断是否是PE文件结构
{
	PIMAGE_DOS_HEADER  pDosHeader = NULL;
	PIMAGE_NT_HEADERS  pNtHeader = NULL;

	if (!ImageBase)
		return FALSE;
	pDosHeader = (PIMAGE_DOS_HEADER)ImageBase;

	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return FALSE;
	pNtHeader = (PIMAGE_NT_HEADERS32)((DWORD)pDosHeader + pDosHeader->e_lfanew);
	if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
		return FALSE;
	return TRUE;
}


PIMAGE_NT_HEADERS  GetNtHeader(LPVOID  ImageBase) //获取NT结构指针
{
	PIMAGE_DOS_HEADER  pDosHeader = NULL;
	PIMAGE_NT_HEADERS  pNtHeader = NULL;

	if (!IsPeFile(ImageBase))
		return  NULL;
	pDosHeader = (PIMAGE_DOS_HEADER)ImageBase;
	pNtHeader = (PIMAGE_NT_HEADERS32)((DWORD)pDosHeader + pDosHeader->e_lfanew);
	return pNtHeader;
}


PIMAGE_FILE_HEADER  WINAPI  GetFileHeader(LPVOID  Imagebase)
{
	PIMAGE_FILE_HEADER  pFileHeader;
	PIMAGE_NT_HEADERS  pNtHeader = NULL;
	pNtHeader = GetNtHeader(Imagebase);
	if (!pNtHeader)
		return  NULL;
	pFileHeader = &pNtHeader->FileHeader;
	return pFileHeader;
}


PIMAGE_OPTIONAL_HEADER  GetOptionalHeader(LPVOID  ImageBase)
{
	PIMAGE_OPTIONAL_HEADER  pOptionHeader = NULL;
	PIMAGE_NT_HEADERS  pNtHeader = NULL;
	pNtHeader = GetNtHeader(ImageBase);
	if (!pNtHeader)
		return  NULL;
	pOptionHeader = &pNtHeader->OptionalHeader;
	return  pOptionHeader;
}



DWORD RvaToOffset(LPVOID lpMoudle, DWORD Rva)
{
	//定义变量存储转换后的偏移值和节表数
	DWORD FileOffset;
	WORD nSectionNum;


	//取NT结构头
	IMAGE_NT_HEADERS  *pNTHead;
	pNTHead = GetNtHeader(lpMoudle);
	nSectionNum = pNTHead->FileHeader.NumberOfSections;


	//取节表结构头
	IMAGE_SECTION_HEADER *pSectionHead;
	pSectionHead = (IMAGE_SECTION_HEADER *)((DWORD)pNTHead + sizeof(IMAGE_NT_HEADERS));


	//循环比较Rva值所对应节表的偏移
	for (int i = 0; i < nSectionNum; i++)
	{
		if ((pSectionHead->VirtualAddress <= Rva) && (Rva < (pSectionHead->SizeOfRawData + pSectionHead->VirtualAddress)))
		{
			FileOffset = Rva - pSectionHead->VirtualAddress + pSectionHead->PointerToRawData;
			return FileOffset;
		}
		pSectionHead++;
	}
	return 0;
}


DWORD RvaToVirtualAddress(LPVOID lpMoudle, DWORD Rva)
{
	DWORD offect = RvaToOffset(lpMoudle, Rva);
	/*if(offect==NULL||offect==FALSE)
	 return FALSE;*/
	return (DWORD)lpMoudle + offect;
}



VOID HandleSessionTable(LPVOID file, LPVOID base)
{
	char funcname[16] = "MessageBoxA";
	char DLLname[16] = "user32.dll";
	char Caption[16] = "Warning";
	char Content[16] = "This is test";
	DWORD LoadLibraryAAddr = 0x1f864;
	DWORD GetProcAddress = 0x24c46;

	char codes[] = "\x60\xe8\x0\x0\x0\x0\x5f\x83\xef\x6\x8b\x4f\xf8\x8b"   //////这里的数据就只插入代码
		"\x5f\xfc\x64\x8b\x15\x30\x0\x0\x0\x8b\x52\xc\x8b\x52\x1c\x8b"   //////的二进制机器码
		"\x12\x8b\x42\x8\x8b\x42\x50\x3\xc8\x50\x8b\xd7\x83\xea\x38\x52"
		"\xff\xd1\x8b\xc8\x58\x3\xd8\x8b\xd7\x83\xea\x48\x52\x51\xff\xd3"
		"\x8b\xcf\x83\xe9\x18\x6a\x0\x51\x83\xe9\x10\x51\x6a\x0\xff\xd0\x61"
		"\xe9\x00\x00\x00\x00";



	int datalength = 16 * 4 + 8;
	int codeslength = sizeof(codes)-1;

	char* myCode = NULL;
	{
		int startAddr = 0;
		int condeSize = 0;
		CodeInfo(&startAddr, &condeSize);
		myCode = new char[condeSize];
		memcpy(myCode, (const void *)startAddr, condeSize);

		codeslength = condeSize;
	}

	IMAGE_NT_HEADERS *nthead = GetNtHeader(base);
	IMAGE_SECTION_HEADER *sessionhead = (IMAGE_SECTION_HEADER*)((DWORD)nthead + sizeof(IMAGE_NT_HEADERS));
	if (sessionhead->VirtualAddress == NULL)
		return;
	DWORD sessionnum = nthead->FileHeader.NumberOfSections;
	IMAGE_SECTION_HEADER *p = sessionhead;
	DWORD sFileSize = GetFileSize(file, NULL);
	for (int i = 0; i<sessionnum; i++)
	{
		cout << (char*)p->Name << " " << (int)p->SizeOfRawData - (int)p->Misc.VirtualSize << endl;
		IMAGE_SECTION_HEADER tmp;//=sessionhead;
		memcpy(&tmp, p, sizeof(IMAGE_SECTION_HEADER));

		if ((int)p->SizeOfRawData - (int)p->Misc.VirtualSize>codeslength + datalength&&\
			(p->Characteristics&IMAGE_SCN_MEM_EXECUTE))
		{
			DWORD datavirtualbase = p->VirtualAddress + p->Misc.VirtualSize;
			DWORD datafileoffect = p->PointerToRawData + p->Misc.VirtualSize;
			DWORD wLength = 0;
			SetFilePointer(file, datafileoffect, NULL, FILE_BEGIN);
			WriteFile(file, funcname, 16, &wLength, 0);
			WriteFile(file, DLLname, 16, &wLength, 0);
			WriteFile(file, Caption, 16, &wLength, 0);
			WriteFile(file, Content, 16, &wLength, 0);
			WriteFile(file, &LoadLibraryAAddr, 4, &wLength, 0);
			WriteFile(file, &GetProcAddress, 4, &wLength, 0);
			DWORD codevirtualbase = p->VirtualAddress + p->Misc.VirtualSize + datalength;
			DWORD cedefileoffset = p->PointerToRawData + p->Misc.VirtualSize + datalength;
			p->Misc.VirtualSize += (codeslength + datalength);
			SetFilePointer(file, cedefileoffset, NULL, FILE_BEGIN);
			DWORD oldentry = nthead->OptionalHeader.AddressOfEntryPoint;
			DWORD JMPOffset = oldentry - (codevirtualbase + codeslength - 5) - 5;
			memcpy(myCode + codeslength - 4, &JMPOffset, sizeof(DWORD));
			nthead->OptionalHeader.AddressOfEntryPoint = codevirtualbase;
			DWORD writesize = 0;
			SetFilePointer(file, cedefileoffset, NULL, FILE_BEGIN);
			if (!WriteFile(file, myCode, codeslength, &writesize, 0))
			{
				TCHAR  *buffer;
				::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, (LPTSTR)&buffer, 0, NULL);
				MessageBox(0, buffer, L"ok", 0);
			}
			cout << "success" << endl;
			break;

		}

		p++;
	}


}





void _tmain(int argc, _TCHAR* argv[])
{
	std::wstring tempPath = argv[0];
	tempPath = tempPath.substr(0, tempPath.find_last_of(L"\\") + 1);
	tempPath += L"DotMatrix.exe";

	HANDLE  hFile = CreateFile(tempPath.c_str(),           // open  pe file
		GENERIC_READ | GENERIC_WRITE,              // open for reading
		NULL,           // share for reading
		NULL,                      // no security
		OPEN_EXISTING,             // existing file only
		FILE_ATTRIBUTE_NORMAL,   // normal file
		NULL);                     // no attr. template

	HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
	if (!hFileMap)
	{
		TCHAR  *buffer;





		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, (LPTSTR)&buffer, 0, NULL);
		MessageBox(0, buffer, L"ok", 0);
	}
	LPVOID  lpMemory = MapViewOfFile(hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, NULL, NULL, NULL);



	if (IsPeFile(lpMemory))
	{
		//AnalyzeNTHEADER(lpMemory);
		cout << "yes" << endl;
		IMAGE_NT_HEADERS *nthead = GetNtHeader(lpMemory);
		IMAGE_OPTIONAL_HEADER32 *image = GetOptionalHeader(lpMemory);
		cout << "DataDirectory num:" << image->NumberOfRvaAndSizes << endl;






		HandleSessionTable(hFile, lpMemory);






	}
	else
		cout << "no" << endl;


	UnmapViewOfFile(lpMemory);
	CloseHandle(hFileMap);
	CloseHandle(hFile);



	system("pause");	
}
