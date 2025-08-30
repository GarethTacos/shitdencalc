#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// 1. Add two numbers: add(a, b)
int l_add(lua_State *L) {
    double a = luaL_checknumber(L, 1);
    double b = luaL_checknumber(L, 2);
    lua_pushnumber(L, a + b);  // return value
    return 1; // one return value
}

// 2. Return a string: get_string()
int l_get_string(lua_State *L) {
    lua_pushstring(L, "Hello from C!");
    return 1; // one return value
}

// 3. Return a table: get_table()
int l_get_table(lua_State *L) {
    lua_newtable(L);

    lua_pushstring(L, "name");
    lua_pushstring(L, "Shitdencalc");
    lua_settable(L, -3);

    lua_pushstring(L, "version");
    lua_pushnumber(L, 1.0);
    lua_settable(L, -3);

    return 1; // return the table
}

// 4. Return 2 floats: get_coords()
int l_get_coords(lua_State *L) {
    lua_pushnumber(L, 3.14);  // first return
    lua_pushnumber(L, 2.71);  // second return
    return 2; // two return values
}

// Function registration table
static const struct luaL_Reg mylib[] = {
    {"add", l_add},
    {"get_string", l_get_string},
    {"get_table", l_get_table},
    {"get_coords", l_get_coords},
    {NULL, NULL} // sentinel
};


int main(void) {
    lua_State *L = luaL_newstate(); // Create a new Lua state
    if (!L) {
        fprintf(stderr, "Failed to create Lua state\n");
        return 1;
    }

    luaL_openlibs(L); // Open standard Lua libraries
	lua_pushvalue(L, LUA_GLOBALSINDEX);

    // Register functions as globals
    luaL_register(L, NULL, mylib);

    // Run script.lua
    if (luaL_dofile(L, "script.lua") != 0) { // 0 = success in LuaJIT
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);
    return 0;
}

