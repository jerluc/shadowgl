#ifndef LUA_UTILS_H
#define LUA_UTILS_H

// Just a few simple helpers for making it slightly
// easier to interact with the embedded Lua bridge

#ifndef LUAJIT
// When LuaJIT is being used, we need to use
// the lua_rawlen function instead, as lua_objlen
// isn't defined until after Lua 5.2
#define lua_objlen(L, I) lua_rawlen(L, I)
#endif

#endif
