#pragma once

#include <list>
#include <string>
#include <algorithm>
#include <glm/glm.hpp>

class Node
{
protected:
    Node *parent = nullptr;
    std::list<Node *> childs;

public:
    std::string name = "";

    void addChild(Node &child);
    void removeChild(Node &child);
    
    std::list<Node *> &getChilds() { return childs; }
    const std::list<Node *> &getChilds() const { return childs; }

    void setParent(Node *p) { parent = p; }

    Node *getParent() { return parent; }
    const Node *getParent() const { return parent; }
    void removeParent();

    virtual glm::mat4 getTransform() {return glm::mat4(1);}
    virtual glm::mat3 getTransform2d() {return glm::mat3(1);}

private:
    friend class Scene;

    void node_init()
    {
        for (auto child : childs)
        {
            child->node_init();
        }
        init();
    }
    void node_update()
    {
        for (auto child : childs)
        {
            child->node_update();
        }
        update();
    }
    void node_draw()
    {
        for (auto child : childs)
        {
            child->node_draw();
        }
        draw();
    }
    void node_destroy()
    {
        for (auto child : childs)
        {
            child->node_destroy();
        }
        destroy();
    }

protected:
    virtual void init(){};
    virtual void update(){};
    virtual void draw(){};
    virtual void destroy(){};
};