#ifndef H_STDAFXHEAD

#define H_STDAFXHEAD

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Common.h"
#include "ByteStream.h"
#include "DebugInfo.h"

extern CDebugInfo cDebug;

#define DEBUG_ENABLE(dbg, type, level, fun)    cDebug.DebugEnable(dbg, type, level, fun);
#define DEBUG_ENTRY()                cDebug.DebugEntry(SRCFILE, CODELINE, FUNCNAME);
#define DEBUG_INFO(fmt,...)             cDebug.DebugInfo(SRCFILE, CODELINE, fmt, ## __VA_ARGS__);
#define DEBUG_RETCODE(str, ret)        cDebug.DebugRetCode(SRCFILE, CODELINE, str, ret);
#define DEBUG_STREAM(level, pCmd, str)     cDebug.DebugByteStream(SRCFILE, CODELINE, level, pCmd, str);
#define DEBUG_BYTEBUF(level, pdata, len, str)     cDebug.DebugByteStream(SRCFILE, CODELINE, level, pdata, len, str);
#define DEBUG_EXIT(ret)            cDebug.DebugExit(SRCFILE, CODELINE, FUNCNAME, ret);
#define DEBUG_REG(fun)                  cDebug.DebugCBRegister(fun);

#endif