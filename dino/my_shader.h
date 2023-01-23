#pragma once

#include "../Engine/Core/application.h"

class MyShader
{
public:
    static Program program;
    static void initialize()
    {
        program.create("../Engine/openGL/Program/Shaders/2d/basic.vert",
                       "../dino/resource/alpha.frag");
    }
    static void determionate()
    {
        program.destroy();
    }
};