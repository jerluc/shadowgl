#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>

static int traceback(lua_State *L) {
    lua_getfield(L, LUA_GLOBALSINDEX, "debug");
    lua_getfield(L, -1, "traceback");
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 2);
    lua_call(L, 2, 1);
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    return 1;
}

int run_program(char* filename) {
    if (1) {
        return do_main();
    }

    lua_State* L;
    
    L = luaL_newstate();
    if (!L)
        return -1;

    luaL_openlibs(L);

	lua_pushcfunction(L, traceback);

    if (luaL_loadfile(L, filename) != 0) {
        return -1;
    }

    if (lua_pcall(L, 0, LUA_MULTRET, lua_gettop(L) - 1) != 0) {
        return -1;
    }

    lua_close(L);

    return 0;
}

