#include <stdio.h>
#include <windows.h>
#include "detours.h"
#pragma comment(lib, "user32.lib")

BOOL Hookem(void);
BOOL UnHookem(void);

int (WINAPI * pOrigWideCharToMultiByte)(
  UINT                               CodePage,
  DWORD                              dwFlags,
  _In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
  int                                cchWideChar,
  LPSTR                              lpMultiByteStr,
  int                                cbMultiByte,
  LPCCH                              lpDefaultChar,
  LPBOOL                             lpUsedDefaultChar
) = WideCharToMultiByte;

int HookedWideCharToMultiByte(
	UINT CodePage,
	DWORD dwFlags,
	_In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
	int cchWideChar,
	LPSTR lpMultiByteStr,
	int cbMultiByte,
	LPCCH lpDefaultChar,
	LPBOOL lpUsedDefaultChar) {

	int ret = pOrigWideCharToMultiByte(
		CodePage,
		dwFlags,
		lpWideCharStr,
		cchWideChar,
		lpMultiByteStr,
		cbMultiByte,
		lpDefaultChar,
		lpUsedDefaultChar);

	char buffer[1024];
	sprintf(buffer, "DATA = %s\n", lpMultiByteStr);
	//OutputDebugStringA(buffer);

	char tempFolder[MAX_PATH];
	GetEnvironmentVariableA("TEMP", tempFolder, MAX_PATH);
	char path[MAX_PATH];
	sprintf(path, "%s\\vcdata.bin", tempFolder);
	//OutputDebugStringA(path);

	HANDLE hFile = CreateFile(
		path,
		FILE_APPEND_DATA,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		OutputDebugStringA("Error opening the log file!\n");
	else {
		DWORD numBytes;
		WriteFile(hFile, buffer, strlen(buffer), &numBytes, NULL);
	}

	CloseHandle(hFile);
	return ret;
}

BOOL Hookem(void) {
    LONG err;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)pOrigWideCharToMultiByte, HookedWideCharToMultiByte);
	err = DetourTransactionCommit();
	//OutputDebugStringA("WideCharToMultiByte() hooked!\n");
	return TRUE;
}

BOOL UnHookem(void) {
	LONG err;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)pOrigWideCharToMultiByte, HookedWideCharToMultiByte);
	err = DetourTransactionCommit();
	//OutputDebugStringA("Hook removed from WideCharToMultiByte()\n");
	return TRUE;
}

extern "C" __declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {
	switch (dwReason)  {
		case DLL_PROCESS_ATTACH:
			Hookem();
			break;
		case DLL_THREAD_ATTACH:
			break;	
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			UnHookem();
			break;
	}

	return TRUE;
}
