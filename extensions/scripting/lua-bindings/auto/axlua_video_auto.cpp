#include "scripting/lua-bindings/auto/axlua_video_auto.hpp"
#include "ui/UIVideoPlayer/UIVideoPlayer.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_ax_video_VideoPlayer_setFileName(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_setFileName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "axui.VideoPlayer:setFileName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_setFileName'", nullptr);
            return 0;
        }
        cobj->setFileName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:setFileName",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_setFileName'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_getFileName(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_getFileName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_getFileName'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFileName();
        lua_pushlstring(tolua_S,ret.data(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:getFileName",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_getFileName'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_setURL(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_setURL'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "axui.VideoPlayer:setURL");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_setURL'", nullptr);
            return 0;
        }
        cobj->setURL(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:setURL",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_setURL'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_getURL(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_getURL'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_getURL'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getURL();
        lua_pushlstring(tolua_S,ret.data(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:getURL",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_getURL'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_setLooping(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_setLooping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "axui.VideoPlayer:setLooping");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_setLooping'", nullptr);
            return 0;
        }
        cobj->setLooping(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:setLooping",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_setLooping'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_setUserInputEnabled(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_setUserInputEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "axui.VideoPlayer:setUserInputEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_setUserInputEnabled'", nullptr);
            return 0;
        }
        cobj->setUserInputEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:setUserInputEnabled",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_setUserInputEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_setStyle(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_setStyle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ax::ui::VideoPlayer::StyleType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "axui.VideoPlayer:setStyle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_setStyle'", nullptr);
            return 0;
        }
        cobj->setStyle(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:setStyle",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_setStyle'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_setPlayRate(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_setPlayRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "axui.VideoPlayer:setPlayRate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_setPlayRate'", nullptr);
            return 0;
        }
        cobj->setPlayRate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:setPlayRate",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_setPlayRate'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_play(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_play'", nullptr);
            return 0;
        }
        cobj->play();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:play",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_play'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_stop(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:stop",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_seekTo(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_seekTo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "axui.VideoPlayer:seekTo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_seekTo'", nullptr);
            return 0;
        }
        cobj->seekTo(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:seekTo",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_seekTo'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_isPlaying(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_isPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_isPlaying'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:isPlaying",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_isPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_isLooping(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_isLooping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_isLooping'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isLooping();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:isLooping",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_isLooping'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_isUserInputEnabled(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_isUserInputEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_isUserInputEnabled'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isUserInputEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:isUserInputEnabled",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_isUserInputEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_setKeepAspectRatioEnabled(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_setKeepAspectRatioEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "axui.VideoPlayer:setKeepAspectRatioEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_setKeepAspectRatioEnabled'", nullptr);
            return 0;
        }
        cobj->setKeepAspectRatioEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:setKeepAspectRatioEnabled",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_setKeepAspectRatioEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_isKeepAspectRatioEnabled(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_isKeepAspectRatioEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_isKeepAspectRatioEnabled'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isKeepAspectRatioEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:isKeepAspectRatioEnabled",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_isKeepAspectRatioEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_setFullScreenEnabled(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_setFullScreenEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "axui.VideoPlayer:setFullScreenEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_setFullScreenEnabled'", nullptr);
            return 0;
        }
        cobj->setFullScreenEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:setFullScreenEnabled",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_setFullScreenEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_isFullScreenEnabled(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_isFullScreenEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_isFullScreenEnabled'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isFullScreenEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:isFullScreenEnabled",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_isFullScreenEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_onPlayEvent(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if _AX_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ax::ui::VideoPlayer*)tolua_tousertype(tolua_S,1,0);

#if _AX_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ax_video_VideoPlayer_onPlayEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "axui.VideoPlayer:onPlayEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_onPlayEvent'", nullptr);
            return 0;
        }
        cobj->onPlayEvent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:onPlayEvent",argc, 1);
    return 0;

#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_onPlayEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_ax_video_VideoPlayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if _AX_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"axui.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_create'", nullptr);
            return 0;
        }
        auto&& ret = ax::ui::VideoPlayer::create();
        object_to_luaval<ax::ui::VideoPlayer>(tolua_S, "axui.VideoPlayer",(ax::ui::VideoPlayer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "axui.VideoPlayer:create",argc, 0);
    return 0;
#if _AX_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_ax_video_VideoPlayer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    ax::ui::VideoPlayer* cobj = nullptr;
    bool ok  = true;

#if _AX_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ax_video_VideoPlayer_constructor'", nullptr);
            return 0;
        }
        cobj = new ax::ui::VideoPlayer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"axui.VideoPlayer");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "axui.VideoPlayer:VideoPlayer",argc, 0);
    return 0;

#if _AX_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_ax_video_VideoPlayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_ax_video_VideoPlayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (VideoPlayer)");
    return 0;
}

int lua_register_ax_video_VideoPlayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"axui.VideoPlayer");
    tolua_cclass(tolua_S,"VideoPlayer","axui.VideoPlayer","axui.Widget",nullptr);

    tolua_beginmodule(tolua_S,"VideoPlayer");
        tolua_function(tolua_S,"new",lua_ax_video_VideoPlayer_constructor);
        tolua_function(tolua_S,"setFileName",lua_ax_video_VideoPlayer_setFileName);
        tolua_function(tolua_S,"getFileName",lua_ax_video_VideoPlayer_getFileName);
        tolua_function(tolua_S,"setURL",lua_ax_video_VideoPlayer_setURL);
        tolua_function(tolua_S,"getURL",lua_ax_video_VideoPlayer_getURL);
        tolua_function(tolua_S,"setLooping",lua_ax_video_VideoPlayer_setLooping);
        tolua_function(tolua_S,"setUserInputEnabled",lua_ax_video_VideoPlayer_setUserInputEnabled);
        tolua_function(tolua_S,"setStyle",lua_ax_video_VideoPlayer_setStyle);
        tolua_function(tolua_S,"setPlayRate",lua_ax_video_VideoPlayer_setPlayRate);
        tolua_function(tolua_S,"play",lua_ax_video_VideoPlayer_play);
        tolua_function(tolua_S,"stop",lua_ax_video_VideoPlayer_stop);
        tolua_function(tolua_S,"seekTo",lua_ax_video_VideoPlayer_seekTo);
        tolua_function(tolua_S,"isPlaying",lua_ax_video_VideoPlayer_isPlaying);
        tolua_function(tolua_S,"isLooping",lua_ax_video_VideoPlayer_isLooping);
        tolua_function(tolua_S,"isUserInputEnabled",lua_ax_video_VideoPlayer_isUserInputEnabled);
        tolua_function(tolua_S,"setKeepAspectRatioEnabled",lua_ax_video_VideoPlayer_setKeepAspectRatioEnabled);
        tolua_function(tolua_S,"isKeepAspectRatioEnabled",lua_ax_video_VideoPlayer_isKeepAspectRatioEnabled);
        tolua_function(tolua_S,"setFullScreenEnabled",lua_ax_video_VideoPlayer_setFullScreenEnabled);
        tolua_function(tolua_S,"isFullScreenEnabled",lua_ax_video_VideoPlayer_isFullScreenEnabled);
        tolua_function(tolua_S,"onPlayEvent",lua_ax_video_VideoPlayer_onPlayEvent);
        tolua_function(tolua_S,"create", lua_ax_video_VideoPlayer_create);
    tolua_endmodule(tolua_S);
    auto typeName = typeid(ax::ui::VideoPlayer).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "axui.VideoPlayer";
    g_typeCast[typeName] = "axui.VideoPlayer";
    return 1;
}
TOLUA_API int register_all_ax_video(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"axui",0);
	tolua_beginmodule(tolua_S,"axui");

	lua_register_ax_video_VideoPlayer(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

