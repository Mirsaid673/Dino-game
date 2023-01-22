#pragma once

#include "Core/rid.h"
#include "Program/program.h"

struct Material
{
    const Program *program;
    RID texture;

    Material() = default;

    Material(const Program &p) : program(&p) {}
    Material(RID t) : texture(t) {}
    Material(const Program &p, RID t) : program(&p), texture(t) {}
};