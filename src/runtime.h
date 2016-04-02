#ifndef RUNTIME_H
#define RUNTIME_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "bridge.h"

// Helper function to print Lua stack traces
// when a runtime error occurs
static int traceback(lua_State *L) {
    // Basically, this is Lua stack-ese for
    // "debug.traceback(1, 5)" to print the last
    // 5 stack frames where the error occurred
    lua_getfield(L, LUA_REGISTRYINDEX, "debug");
    lua_getfield(L, -1, "traceback");
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 5);
    lua_call(L, 2, 1);
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    return 1;
}

// TODO: Ughhh, there's probably a better way to do this
static lua_State* L;
static int initPtr;
static int drawPtr;

void gameInit() {
    lua_rawgeti(L, LUA_REGISTRYINDEX, initPtr);
    lua_pcall(L, 0, 0, 0);
}

void gameDraw() {
    lua_rawgeti(L, LUA_REGISTRYINDEX, drawPtr);
    lua_pcall(L, 0, 0, 0);
}

int run_program(char* filename) {
    L = luaL_newstate();
    if (!L)
        return -1;

    luaL_openlibs(L);

	lua_pushcfunction(L, traceback);

    luaopen_shadowgl(L);

    if (luaL_loadfile(L, filename) != 0) {
        return -1;
    }

    if (lua_pcall(L, 0, LUA_MULTRET, lua_gettop(L) - 1) != 0) {
        return -1;
    }

    lua_getfield(L, -1, "init");
    if (!lua_isfunction(L, -1))
        exit(EXIT_FAILURE);
    initPtr = luaL_ref(L, LUA_REGISTRYINDEX);

    lua_getfield(L, -1, "draw");
    if (!lua_isfunction(L, -1))
        exit(EXIT_FAILURE);
    drawPtr = luaL_ref(L, LUA_REGISTRYINDEX);

    graphics_main(gameInit, gameDraw);

    lua_close(L);

    return 0;
}

#endif
