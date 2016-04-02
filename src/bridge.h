#ifndef BRIDGE_H
#define BRIDGE_H
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "lua_utils.h"
#include "graphics.h"

typedef struct shapeT {
    int    vao;
    int    numVertices;
} shapeT;

int shape(lua_State* L) {
    int size = lua_objlen(L, 1);
    float* vertices = calloc(size, sizeof(float));

    for (int i = 0; i < size; i++) {
        lua_pushinteger(L, i + 1);
        lua_gettable(L, 1);
        vertices[i] = (float) lua_tonumber(L, -1);
        lua_pop(L, 1);
    }

    shapeT* newShape = lua_newuserdata(L, sizeof(shapeT));
    newShape->vao = createVertexBuffer(vertices, size / 2);
    newShape->numVertices = size;

    free(vertices);

    return 1;
}

int drawShape(lua_State* L) {
    shapeT* theShape = (shapeT*) lua_touserdata(L, 1);
    graphicsDrawShape(theShape->vao, theShape->numVertices);
    return 0;
}

LUALIB_API int luaopen_shadowgl(lua_State* L) {
    lua_register(L, "shape", shape);
    lua_register(L, "drawShape", drawShape);
    return 0;
}

#endif
