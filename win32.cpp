//links
http://www.win-api.de/tutorials.php
//fenster in den vordergrund
HWND window = FindWindow(NULL, "window");
if (window) SetForegroundWindow(window);
//bildschirmgröße
RECT fenster;
GetWindowRect(window, &fenster);
//screenshot
HDC dc = GetDC(0);
//getpixelcolor
COLORREF c = GetPixel(dc, 575, 550);
GetRValue(c), GetGValue(c), GetBValue(c)
//mouseevents
SetCursorPos(x, y);
mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
GetCursorPos(&p);
//tastenabfrage
if (GetAsyncKeyState('A') == -32767)
//tastaturbefehl senden
keybd_event(VK_LSHIFT , 0, 0, 0);
keybd_event(VkKeyScan('H'),0x9e, 0 , 0);
keybd_event(VkKeyScan('H'),0x9e, 0 , KEYEVENTF_KEYUP);
keybd_event(VK_LSHIFT , 0, KEYEVENTF_KEYUP, 0);
//hide
ShowWindow(GetConsoleWindow(), SW_HIDE);
//check already open
CreateMutexA(0, FALSE, exeName.c_str());
if(GetLastError() == ERROR_ALREADY_EXISTS) return -1;
//get exe path
TCHAR szExeFileName[MAX_PATH]; 
GetModuleFileName(NULL, szExeFileName, MAX_PATH);
string exePath = szExeFileName;
//copyfile
void copyFile(string src, string dst) {
ifstream isrc(src, ios::binary);
ofstream odst(dst, ios::binary);
odst << isrc.rdbuf();
isrc.close();
odst.close(); }
//getusername
char acUserName[100];
DWORD nUserName = sizeof(acUserName);
GetUserName(acUserName, &nUserName);
string username(acUserName);
//getcomputername
char acComputerName[100];
DWORD nComputerName = sizeof(acComputerName);
GetComputerName(acComputerName, &nComputerName);
string Computername(acComputerName);
//time
#include <time.h> //or <ctime>
time_t theTime = time(NULL);
struct tm *aTime = localtime(&theTime);
int lastHour = aTime->tm_hour; //tm_sec;tm_min;tm_mday;tm_mon + 1;tm_year + 1900;
//screen
void gdiscreen(string screenshotString) {
	//-lgdiplus -lgdi32 -lOle32 #include <gdiplus.h> #include <Windows.h>
	using namespace Gdiplus;
	IStream* istream;
	HRESULT res = CreateStreamOnHGlobal(NULL, true, &istream);
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	{
		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = ::GetDC(0);
		int Height = GetSystemMetrics(SM_CYSCREEN);
		int Width = GetSystemMetrics(SM_CXSCREEN);
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		HBITMAP hOldBitmap =(HBITMAP) SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);
		Gdiplus::Bitmap bitmap(membit, NULL);
		CLSID clsid, *pClsid = &clsid;
		UINT  num = 0;
		UINT  size = 0;
		ImageCodecInfo* pImageCodecInfo = NULL;
		GetImageEncodersSize(&num, &size);
		pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
		GetImageEncoders(num, size, pImageCodecInfo);
		for(UINT j = 0; j < num; ++j)
		{
			if(wcscmp(pImageCodecInfo[j].MimeType, L"image/jpeg") == 0) {
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
			}    
		}
		free(pImageCodecInfo);
		wstring widestr = wstring(screenshotString.begin(), screenshotString.end());
		const wchar_t* widecstr = widestr.c_str();
		bitmap.Save(widecstr, &clsid, NULL);
		bitmap.Save(istream, &clsid, NULL);
		DeleteObject(memdc);
		DeleteObject(membit);
		::ReleaseDC(0,scrdc);
	}
	GdiplusShutdown(gdiplusToken);
}
//delete recursive
int deletedir(const std::string &refcstrRootDirectory, bool bDeleteSubdirectories)
{
	//#include <Windows.h>
	bool bSubdirectory = false;
	HANDLE hFile;
	std::string strFilePath;
	std::string strPattern;
	WIN32_FIND_DATA FileInformation;
	strPattern = refcstrRootDirectory + "\\*.*";
	hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
	if(hFile == INVALID_HANDLE_VALUE) return 0;
	do
	{
		if (FileInformation.cFileName[0] != '.') {
			strFilePath.erase();
			strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;
			if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (bDeleteSubdirectories) {
					int iRC = deletedir(strFilePath, bDeleteSubdirectories);
					if (iRC) return iRC;
				}
				else bSubdirectory = true;
			}
			else
			{
				if (::SetFileAttributes(strFilePath.c_str(), FILE_ATTRIBUTE_NORMAL) == FALSE) return ::GetLastError();
				if (::DeleteFile(strFilePath.c_str()) == FALSE) return ::GetLastError();
			}
		}
	} while(::FindNextFile(hFile, &FileInformation) == TRUE);
	::FindClose(hFile);
	DWORD dwError = ::GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) return dwError;
	else {
		if (!bSubdirectory) {
			if (::SetFileAttributes(refcstrRootDirectory.c_str(), FILE_ATTRIBUTE_NORMAL) == FALSE) return ::GetLastError();
			if (::RemoveDirectory(refcstrRootDirectory.c_str()) == FALSE) return ::GetLastError();
		}
	}
	return 0;
}