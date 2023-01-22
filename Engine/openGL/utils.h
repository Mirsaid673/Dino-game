#pragma once

#include <GL/glew.h>
#include <spdlog/spdlog.h>

class Utils
{
public:

    static void getError()
    {
        int code = glGetError();
        if(code)
            spdlog::error("opengl error code: {}\n", code);
    }
};