#include "physics.h"
#include "dino.h"
#include "../Engine/Core/time_utils.h"

void Listener::BeginContact(b2Contact *contact)
{
    b2Fixture *a = contact->GetFixtureA();
    b2Fixture *b = contact->GetFixtureB();

    ((Collider*)(a->GetBody()->GetUserData().pointer))->onColliderEnter(b, contact);
    ((Collider*)(b->GetBody()->GetUserData().pointer))->onColliderEnter(a, contact);
}

void Listener::EndContact(b2Contact *contact)
{
    b2Fixture *a = contact->GetFixtureA();
    b2Fixture *b = contact->GetFixtureB();

    ((Collider*)(a->GetBody()->GetUserData().pointer))->onColliderExit(b, contact);
    ((Collider*)(b->GetBody()->GetUserData().pointer))->onColliderExit(a, contact);
}

Physics physics;