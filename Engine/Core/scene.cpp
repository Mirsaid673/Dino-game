#include "scene.h"

void Scene::addNode(Node &node)
{
    root.addChild(node);
}

void Scene::removeNode(Node &node)
{
    root.removeChild(node);
}

void Scene::destroy()
{
    root.node_destroy();
}

void Scene::update()
{
    root.node_update();
}

void Scene::draw()
{
    root.node_draw();
}