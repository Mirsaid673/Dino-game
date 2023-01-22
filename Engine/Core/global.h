#pragma once

#include "openGL/gpu.h"
#include "openGL/Program/program.h"
#include "openGL/Texture/texture.h"
#include "openGL/Texture/cubemap.h"
#include "openGL/Framebuffer/framebuffer.h"
#include "openGL/Renderer/renderer.h"
#include "Platform/window.h"
#include "Core/input.h"
#include "Core/Mesh/material.h"
#include "Core/Mesh/mesh.h"
#include "Core/Camera/camera.h"
#include "Core/Camera/camera2d.h"
#include "Core/Resources/resource_manager.h"
#include "Core/time_utils.h"
#include "Core/scene.h"

extern Window window;
extern Input input;
extern Camera camera;
extern Camera2d camera2d;
extern Scene scene;
extern Scene *current_scene;