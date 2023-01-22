#pragma once

#include "../Engine/Core/node.h"
#include "../Engine/Core/time_utils.h"
#include <box2d/box2d.h>

class Collider
{
public:
    enum ID
    {
        NONE,
        DINO,
        ENEMY,
        GROUND,
    } id;
    virtual void onColliderEnter(b2Fixture *other, b2Contact *contact){};
    virtual void onColliderExit(b2Fixture *other, b2Contact *contact){};
};

class Listener : public b2ContactListener
{
    void BeginContact(b2Contact *contact) override;

    void EndContact(b2Contact *contact) override;
};

class Physics : public Node
{
private:
    b2World world;
    Listener listener;
    int velocityIterations = 6;
    int positionIterations = 2;

public:
    Physics() : world({0.0f, -20.0f})
    {
        world.SetContactListener(&listener);
    }

    b2Body *createBody(const b2BodyDef *def)
    {
        return world.CreateBody(def);
    }

    void update() override
    {
        world.Step(Time::delta_time, velocityIterations, positionIterations);
    }
};
extern Physics physics;