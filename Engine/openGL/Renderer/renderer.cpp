#include "renderer.h"

#include <spdlog/spdlog.h>

const Camera *Renderer::current_camera = nullptr;
const Camera2d *Renderer::current_camera2d = nullptr;
const Program *Renderer::current_program = nullptr;
const Program *Renderer::framebuffer_program = &Program::framebuffer;
bool Renderer::depthTestEnabled = false;
std::vector<const Framebuffer *> Renderer::framebuffers_stack;

GLbitfield Renderer::clear_buffers_bits = GL_COLOR_BUFFER_BIT;

void Renderer::init()
{
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        spdlog::critical("Failed to initialize GLEW");
}

void Renderer::enableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
    clear_buffers_bits |= GL_DEPTH_BUFFER_BIT;
    depthTestEnabled = true;
}
void Renderer::disableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
    clear_buffers_bits &= ~GL_DEPTH_BUFFER_BIT;
    depthTestEnabled = false;
}

void Renderer::setMaterial(const Material &material)
{
    current_program = material.program;
    current_program->use();
    GPU::gpu.getTexture(material.texture).use();
}

void Renderer::setTransform(const glm::mat4 &model)
{
    current_program->use();
    current_program->setPVM(current_camera->getPV() * model);
}

void Renderer::setTransform2d(const glm::mat3 &model)
{
    current_program->use();
    current_program->setPVM(current_camera2d->getPV() * model);
}

void Renderer::drawVAO(const VertexArray &vao)
{
    vao.bind();
    glDrawElements(vao.getMode(), vao.getIndexCount(), vao.getIndexDataType(), 0);
}

void Renderer::drawVAO(RID v)
{
    const VertexArray &vao = GPU::gpu.getVertexArray(v);
    vao.bind();
    glDrawElements(vao.getMode(), vao.getIndexCount(), vao.getIndexDataType(), 0);
}

void Renderer::drawFramebuffer(const Framebuffer &fbo)
{
    glDisable(GL_DEPTH_TEST);

    framebuffer_program->use();
    fbo.getTexture().use();
    drawVAO(GPU::gpu.getDeafultQuad());
    if (isDepthTestEnabled)
        glEnable(GL_DEPTH_TEST);
}

void Renderer::pushDrawTarget(const Framebuffer &fbo)
{
    fbo.bind();
    setViewport(fbo.getSize());
    Renderer::clearBuffers();
    framebuffers_stack.push_back(&fbo);
}

void Renderer::popDrawTarget()
{
    framebuffers_stack.pop_back();

    if (framebuffers_stack.empty())
    {
        Framebuffer::bindMain();
        setViewport(window.getSize());
        return;
    }

    auto last = framebuffers_stack.back();
    last->bind();
    setViewport(last->getSize());
}