#include "precomp.h"
#include "scorpion.h"

Scorpion::Scorpion(Surface* newScreen, GameScene* newGameScene, float2 newPos, int dis, float newSpeed,
    const char* newSpriteName): Enemy(newScreen, newGameScene, newPos, newSpeed),
                                secondPoint(newPos + int2(dis,0))
{
    sprite = new Sprite(new Surface(newSpriteName), 1);
    root = new Transform(firstPoint,int2(sprite->GetHeight(), sprite->GetWidth()));
    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
}

void Scorpion::PhysicsTick()
{
    if (root->GetWorldLoc().x >= secondPoint.x)
    {
        dir = -1;
    }
    if (root->GetWorldLoc().x <= firstPoint.x)
    {
        dir = 1;
    }
    Move();
    GetRoot()->Move(vel);
}

void Scorpion::Move()
{
    vel.x = static_cast<float>(dir) * speed;
}
