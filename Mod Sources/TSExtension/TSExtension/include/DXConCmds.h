/**
 *	@brief The DXAPI is an API that allows you to manipulate various game objects 
 *	in Tribes 2 from raw C++ code. It dynamically resolves the addresses of member
 *	variables as you can't really trust the compiler to produce binary compatible classes,
 *	especially with all the inheritance involved in the original Tribes 2 codebase.
 *
 *	This code wouldn't be possible without Linker's original gift on the-construct.net forums,
 *	whose files are appropriately labeled in this codebase.
 *
 *	@copyright (c) 2014 Robert MacGregor
 */

#pragma once
#pragma check_stack(off)
#include <LinkerAPI.h>
#ifdef NEW_DB_CODE
#undef NEW_DB_CODE
#endif
void serverProcessReplacement(unsigned int timeDelta) ;
bool conShapeBaseSetCloakValue(Linker::SimObject *obj, S32 argc, const char* argv[]);
const char* congetServPAddr(Linker::SimObject *obj, S32 argc, const char *argv[]);
// Returns the address of an object in memory
const char* conGetAddress(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conGetAddressDec(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conDumpHex(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conDumpUInt(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conDumpFloat(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conFloatToHex(Linker::SimObject *obj, S32 argc, const char *argv[]);
// Player Commands -----------------------------------
bool conPlayerGetJumpingState(Linker::SimObject *obj, S32 argc, const char* argv[]);
bool conPlayerGetJettingState(Linker::SimObject *obj, S32 argc, const char* argv[]);

bool conGameConnectionSetHeatLevel(Linker::SimObject *obj, S32 argc, const char *argv[]);
bool conSetProcessTicks(Linker::SimObject *obj, S32 argc, const char* argv[]) ;
bool conclientCmdSetProcessTicks(Linker::SimObject *obj, S32 argc, const char* argv[]) ;
bool conclientCmdSetGhostTicks(Linker::SimObject *obj, S32 argc, const char* argv[]);
// GrenadeProjectile Commands ------------------------
const char* conGrenadeProjectileGetPosition(Linker::SimObject *obj, S32 argc, const char* argv[]);
const char* conGrenadeProjectileGetVelocity(Linker::SimObject *obj, S32 argc, const char* argv[]);

// Projectile explode -------------------------------
bool conProjectileExplode(Linker::SimObject *obj, S32 argc, const char* argv[]);
bool conProjectileMakeNerf(Linker::SimObject *obj, S32 argc, const char* argv[]);

// TCPObject Commands -------------------------------
const char* conTCPObjectConnect(Linker::SimObject *obj, S32 argc, const char *argv[]);
bool conTCPObjectSend(Linker::SimObject *obj, S32 argc, const char *argv[]);
bool conTCPObjectDisconnect(Linker::SimObject *obj, S32 argc, const char *argv[]);

// HTTPObject Commands ------------------------------
bool conHTTPObjectDoNothing(Linker::SimObject *obj, S32 argc, const char *argv[]);

// BinaryObject Commands ----------------------------
bool conBinaryObjectOpenForRead(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conBinaryObjectReadU32(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conBinaryObjectReadF32(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conBinaryObjectReadU8(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conBinaryObjectGetBufferLength(Linker::SimObject *obj, S32 argc, const char *argv[]);
bool conBinaryObjectSetBufferPointer(Linker::SimObject *obj, S32 argc, const char *argv[]);
const char *conBinaryObjectGetBufferPointer(Linker::SimObject *obj, S32 argc, const char *argv[]);
bool conBinaryObjectClose(Linker::SimObject *obj, S32 argc, const char *argv[]);
bool conBinaryObjectSave(Linker::SimObject *obj, S32 argc, const char *argv[]);
S32 conResolveGhostParent(Linker::SimObject *obj, S32 argc, const char* argv[]);
S32 conResolveGhost(Linker::SimObject *obj, S32 argc, const char* argv[]);
// Network Commands ---------------------------------
S32 conGetGhostIndex(Linker::SimObject *obj, S32 argc, const char* argv[]);
bool conForceUpdate(Linker::SimObject *obj, S32 argc, const char* argv[]);
// General Commands ---------------------------------
const char* conSprintf(Linker::SimObject *obj, S32 argc, const char* argv[]);
bool conTSExtensionUpdate(Linker::SimObject *obj, S32 argc, const char *argv[]);
// memPatch Disabler -------------------------------
bool disableMempatch(Linker::SimObject* obj, S32 argc, const char* argv[]);
// Regex Commands ----------------------------------
const char* reIterNext(Linker::SimObject* obj, S32 argc, const char* argv[]);
bool reIterEnd(Linker::SimObject* obj, S32 argc, const char* argv[]);
bool reIterBegin(Linker::SimObject* obj, S32 argc, const char* argv[]);
const char* reReplace(Linker::SimObject* obj, S32 argc, const char* argv[]);
bool reSearch(Linker::SimObject* obj, S32 argc, const char* argv[]);
bool reMatch(Linker::SimObject* obj, S32 argc, const char* argv[]);