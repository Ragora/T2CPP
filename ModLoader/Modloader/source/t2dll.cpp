/*
 *	t2dll.cpp
 *	Original code by Linker
 *	Modified by Robert MacGregor
*/

#include <stdafx.h>

#include <LinkerAPI.h>
#include <modLoader.h>

#include <unordered_set>

#define endian(hex) (((hex & 0x000000FF) << 24)+((hex & 0x0000FF00) << 8)+((hex & 0x00FF0000)>>8)+((hex & 0xFF000000) >> 24))

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return true;
}
const unsigned char moduroutine[] = {0x8B, 0x3D, 0xEC, 0x82, 0x9E, 0x00, 0x89, 0xF8, 0x8B, 0x14, 0x85, 0xFC, 0xA5, 0x88, 0x00, 0x83, 0xFA, 0x00, 0x74, 0x30, 0x8B, 0x3D, 0xEC, 0x82, 0x9E, 0x00, 0x89, 0xF8, 0x31, 0xD2, 0x89, 0xF8, 0x8B, 0x04, 0x85, 0x00, 0xA6, 0x88, 0x00, 0xF7, 0x34, 0xBD, 0xFC, 0xA5, 0x88, 0x00, 0xFF, 0x0D, 0xEC, 0x82, 0x9E, 0x00, 0x89, 0xF8, 0x89, 0x14, 0x85, 0xFC, 0xA5, 0x88, 0x00, 0xB8, 0xC7, 0xCE, 0x42, 0x00, 0xFF, 0xE0, 0xFF, 0x0D, 0xEC, 0x82, 0x9E, 0x00, 0xC7, 0x04, 0x85, 0xFC, 0xA5, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB8, 0xC7, 0xCE, 0x42, 0x00, 0xFF, 0xE0};
const char* congetServPAddr(Linker::SimObject *obj, S32 argc, const char *argv[]) 
{
		char test[256] = "";
		char test2[256]="";
		int spr=(signed int)*serverProcessReplacement;
		sprintf(test2,"B8%08XFFD089EC5DC3",endian(spr));
		/*test2[0]=test[6];
		test2[1]=test[7];
		test2[2]=test[4];
		test2[3]=test[5];
		test2[4]=test[2];
		test2[5]=test[3];
		test2[6]=test[0];
		test2[7]=test[1];
		test2[8]=0;*/
		return test2;
}
const char* congetModuAddr(Linker::SimObject *obj, S32 argc, const char *argv[]) 
{
		char test[256] = "";
		char test2[256]="";
		int spr=(signed int)moduroutine;
		sprintf(test2,"B8%08XFFE0",endian(spr));
		/*test2[0]=test[6];
		test2[1]=test[7];
		test2[2]=test[4];
		test2[3]=test[5];
		test2[4]=test[2];
		test2[5]=test[3];
		test2[6]=test[0];
		test2[7]=test[1];
		test2[8]=0;*/
		return test2;
}
	

class CImmCompoundEffect 
{
	public:
		_declspec(dllexport) int Start(unsigned long x, unsigned long y) { return 8; }
		_declspec(dllexport) int Stop() { return 1; }
};

class CImmDevice 
{
	public:
		_declspec(dllexport) static CImmDevice * CreateDevice(HINSTANCE__ *, HWND__ *) 
		{ 
			Con::addVariable("$cpuspeed",TypeS32,reinterpret_cast<void*>(0x8477F8)); //1 - S32, this is so i can set my cpu speed to 31337 or osmething =P
			Con::addVariable("$GameBase::showBoundingBox",TypeBool,reinterpret_cast<void*>(0x9ECF24));
			DWORD oldprotect=0;
			// Mod Loader Function
			Con::addMethodB(NULL, "loadMod", &conLoadMod, "Loads a C++ modification.",2,2);
			Con::addMethodS(NULL, "getServPAddr",&congetServPAddr,"Gets the memPatch data for ServerProcess",1,1);
			VirtualProtect( (LPVOID)moduroutine,sizeof(moduroutine),PAGE_EXECUTE_READWRITE,&oldprotect);
			Con::addMethodS(NULL, "getModuAddr",&congetModuAddr,"Gets the memPatch data for the MODULO operator routine",1,1); // memPatch("42D89D",getModuAddr());
			// Load the original TribesNext DLL if available
			typedef void (*LPINITT2DLL)(void);
			HINSTANCE hDLL = NULL;
			LPINITT2DLL lpinitT2DLL = NULL;
			hDLL = LoadLibrary(L"tribesnext.dll"); // AfxLoadLibrary is probably better.

			if (hDLL == NULL)
				return 0; // The DLL doesn't exist
			else
				lpinitT2DLL = (LPINITT2DLL)GetProcAddress(hDLL, "_Z9initT2Dllv"); // Attempt to load our entry point

			if (lpinitT2DLL == NULL)
				return 0; // Unable to load entry point
			else
				lpinitT2DLL(); // The function was loaded, call TribesNext and move on to postTN Startup

			return 0;
		}

	_declspec(dllexport) int UsesWin32MouseServices(int) { return 4; }
};

class CImmProject 
{
	public:
		_declspec(dllexport) CImmProject() {}
		_declspec(dllexport) ~CImmProject() {}

		_declspec(dllexport) CImmCompoundEffect *GetCreatedEffect(int) { return 0; } 
		_declspec(dllexport) CImmCompoundEffect *GetCreatedEffect(const char *) { return 0; } 
		_declspec(dllexport) CImmCompoundEffect *CreateEffect(char const *, CImmDevice *, unsigned long) { return 0; }
		_declspec(dllexport) int Start(char const *, unsigned long, unsigned long, class CImmDevice *) { return 1; }
		_declspec(dllexport) int Stop(const char *) { return 1; }
		_declspec(dllexport) int LoadProjectFromMemory(void *, CImmDevice *) { return 1; }
};

#ifdef _MANAGED
#pragma managed(pop)
#endif

