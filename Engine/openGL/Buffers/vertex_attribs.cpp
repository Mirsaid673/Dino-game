#include "vertex_attribs.h"

const GLuint VertexAttribs::count[] =
    {
        3, // position
        3, // normal
        3, // color
        2, // texture st
        2, // texture st 2
        2, // position 2d
        4, // color 4
};

std::vector<VertexAttribs> VertexAttribs::POS_NORM_TEX =
{
    VertexAttribs::POSITION,
    VertexAttribs::NORMAL,
    VertexAttribs::TEXTURE_ST,
};

std::vector<VertexAttribs> VertexAttribs::POS2D_TEX =
{
    VertexAttribs::POSITION2D,
    VertexAttribs::TEXTURE_ST,
};