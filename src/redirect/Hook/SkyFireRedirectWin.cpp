#include "stdafx.h"

#include "SkyFireRedirectWin.h"

#include "stdafx.h"
#include "detours.h"

#pragma comment(lib,"detours.lib")

int(*origin_SelectSocket)(unsigned int a1);
int __cdecl SelectSocket(unsigned int a1);
//DWORD __SelectSocket__ = 0x08EC70; // WoW 4.0.3 13329 (release)
//DWORD __SelectSocket__ = 0x091369; // WoW 4.0.6 13596 (release)
DWORD __SelectSocket__ = 0x091229; // WoW 4.0.6a 13623 (release)

int _cdecl SelectSocket(unsigned int a1)
{
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			origin_SelectSocket = (int(*)(unsigned int))DetourFunction((PBYTE)(__SelectSocket__+(DWORD)GetModuleHandle(NULL)), (PBYTE)SelectSocket);
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
	}

	return true;
}