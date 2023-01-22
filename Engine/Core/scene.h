#pragma once

#include "node.h"

class Scene
{
private:
    Node root;

public:
    void addNode(Node &node);
    void removeNode(Node &node);
    //void removeNode(size_t index) { root.getChilds().erase(root.getChilds().begin() + index); }

    std::list<Node *> &getNodes() { return root.getChilds(); }
    const std::list<Node *> &getNodes() const { return root.getChilds(); }

    //Node &operator[](size_t index) { return root[index]; }

    void update();
    void draw();
    void destroy();
};