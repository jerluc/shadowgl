#ifndef LUA_UTILS_H
#define LUA_UTILS_H

#ifndef LUAJIT
#define lua_objlen(L, I) lua_rawlen(L, I)
#endif

#endif
