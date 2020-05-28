#pragma once
#include "../Engine/XorStr.h"
#include <VMProtectSDK.h>

//#define ENABLE_XOR_STR
//#define ENABLE_VMP 
//#define YOUGAMEBIZ

#define PRESENT_ENABLE

//#define ENABLE_CONSOLE_LOG
//#define ENABLE_DEBUG_FILE 1

#define MAX_FONT_SIZE 30
#define ENABLE_HOOK_CS_WND_PROC

#define PATH_TO_CHEAT_SETTINGS "\\X1N3\\"

#define MAX_ENTITY_PLAYERS 64

#define CHEAT_HEAD "X1N3"

#ifdef ENABLE_CONSOLE_LOG
#define ADD_LOG(m, ...) printf(m, __VA_ARGS__)
#else
#define ADD_LOG(m, ...)
#endif

#define VGUI2_DLL XorStr("vgui2.dll")
#define VGUIMAT_DLL	XorStr("vguimatsurface.dll")
#define D3D9_DLL XorStr("d3d9.dll")
#define SHADERPIDX9_DLL XorStr("shaderapidx9.dll")
#define GAMEOVERLAYRENDERER_DLL XorStr("GameOverlayRenderer.dll")
#define D3D9_MASK XorStr("x????xxxxxx")
#define GMOR_MASK XorStr("x????x????xxxx????xxxxxxx")

#define D3D9_PATTERN XorStr("\xA1\x00\x00\x00\x00\x50\x8B\x08\xFF\x51\x0C")
#define FORCE_FULL_UPDATE_PATTERN XorStr("A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85")
#define GMOR_PATTERN XorStr("\xA3\x00\x00\x00\x00\x68\x00\x00\x00\x00\xFF\x76\x54\xE8\x00\x00\x00\x00\x83\xC4\x08\x84\xC0\x75\x17")
#define SMOK_PATTERN XorStr("\x55\x8B\xEC\x83\xEC\x08\x8B\x15\x00\x00\x00\x00\x0F\x57\xC0")

#define KEY_VALUES_MASK  XorStr("55 8B EC 51 33 C0 C7 45")
#define KEY_VALUES_LOAD_FROM_BUFFER_MASK  XorStr("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04")

#define DELETE_PTR(name) delete name; name = nullptr

#define EX_ARRAYSIZE(_ARR)      ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define EX_PI                   3.14159265358979323846f
#define EX_OFFSETOF(_TYPE,_ELM) ((size_t)&(((_TYPE*)0)->_ELM))

#ifdef ENABLE_XOR_STR
#define XorStr( s ) ( XorCompileTime::XorString< sizeof( s ) - 1, __COUNTER__ >( s, std::make_index_sequence< sizeof( s ) - 1>() ).decrypt() )
#define XorString( String ) ( ( string ( XS < XS_CONSTRUCT_INDEX_LIST < sizeof ( String ) - 1 > :: Result> ( String ).Decrypt( ) ) ).c_str( ) )
#else
#define XorStr( s ) s
#define XorString( String ) String
#endif

#ifdef ENABLE_VMP
#define VMP_VIRTUAL(e) VMProtectBeginVirtualization(e);
#define VMP_MUTATION(e) VMProtectBeginMutation(e);
#define VMP_ULTRA(e) VMProtectBeginUltra(e);
#define VMP_BEGIN(e) VMProtectBegin(e);
#define VMP_END VMProtectEnd();
#else
#define VMP_VIRTUAL(e)
#define VMP_MUTATION(e)
#define VMP_ULTRA(e)
#define VMP_BEGIN(e)
#define VMP_END 
#endif