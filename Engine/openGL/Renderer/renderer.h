#pragma once

#include "global.h"
#include "Math/rect.h"
#include "Buffers/vertex_array.h"
#include "Texture/cubemap.h"
#include "Framebuffer/framebuffer.h"
#include "Mesh/material.h"
#include "Camera/camera.h"
#include "Camera/camera2d.h"
#include "gpu.h"

class Renderer
{
public:
     enum DepthFunc
     {
          NEVER = GL_NEVER,
          LESS = GL_LESS,
          EUQUAL = GL_EQUAL,
          LEUQUAL = GL_LEQUAL,
          GREATER = GL_GREATER,
          NOT_EUQUAL = GL_NOTEQUAL,
          GEQUAL = GL_GEQUAL,
          ALWAYS = GL_ALWAYS,
     };

private:
     static const Camera *current_camera;
     static const Camera2d *current_camera2d;
     static const Program *current_program;
     static const Program *framebuffer_program;

     static GLbitfield clear_buffers_bits;
     static bool depthTestEnabled;

     static std::vector<const Framebuffer*> framebuffers_stack;

public:
     static void init();

     static void setViewport(const Rect &rect) { glViewport(rect.origin.x, rect.origin.y, rect.size.x, rect.size.y); }
     static void setViewport(const glm::vec2 &size) { glViewport(0, 0, size.x, size.y); }

     static void setClearColor(const glm::vec4 &color) { glClearColor(color.r, color.g, color.b, color.a); }
     static void setClearColor(const glm::vec3 &color) { glClearColor(color.r, color.g, color.b, 0.0f); }

     static void setLineWidth(float width) {glLineWidth(width);}

     static void enableDepthTest();
     static void disableDepthTest();

     static void clearBuffers() { glClear(clear_buffers_bits); };

     static void setProgram(const Program &program) { current_program = &program; program.use();}
     static void setMaterial(const Material &material);
     static void setTransform(const glm::mat4 &model);
     static void setTransform2d(const glm::mat3 &model);
     static void useTexture(RID id){GPU::gpu.getTexture(id).use();}
     static void useCubeMap(RID id){GPU::gpu.getCubeMap(id).use();}

     static void drawVAO(const VertexArray &vao);
     static void drawVAO(RID vao);
     static void drawFramebuffer(const Framebuffer &framebuffer);

     static void setCamera(const Camera &camera) { current_camera = &camera; }
     static void setCamera2d(const Camera2d &camera) { current_camera2d = &camera; }

     static void depthFunc(DepthFunc func) { glDepthFunc(func); }
     static bool isDepthTestEnabled() { return depthTestEnabled; }

     static void pushDrawTarget(const Framebuffer& fbo);
     static void popDrawTarget();
};