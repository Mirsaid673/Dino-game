#include "node.h"

void Node::addChild(Node &child)
{
    Node *p = child.getParent();
    if (p != nullptr)
        p->removeChild(child);
    child.setParent(this);
    childs.push_back(&child);
    child.init();
}

void Node::removeChild(Node &child)
{
    const auto &c = std::find(childs.begin(), childs.end(), &child);
    if (c != childs.end())
    {
        (*c)->setParent(nullptr);
        child.node_destroy();
        childs.erase(c);
    }
}

void Node::removeParent()
{
    parent->removeChild(*this);
    parent = nullptr;
}