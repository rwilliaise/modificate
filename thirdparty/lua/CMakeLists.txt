
set(LUA_SOURCES
	lapi.c lauxlib.c lbaselib.c lcode.c lcorolib.c lctype.c ldblib.c ldebug.c ldo.c
    ldump.c lfunc.c lgc.c linit.c liolib.c llex.c lmathlib.c lmem.c loadlib.c lobject.c lopcodes.c
    loslib.c lparser.c lstate.c lstring.c lstrlib.c ltable.c ltablib.c ltests.c ltm.c lundump.c
    lutf8lib.c lvm.c lzio.c	
)

set(LUA_HEADERS
	lua.h
	lualib.h
	lauxlib.h

	lua.hpp
)

add_library(lua ${LUA_SOURCES})
