#include "precomp.h"
#include "game/entity/enemy/enemy.h"
#include "glider.h"

Glider::Glider(Surface* newScreen, GameScene* newGameScene, int2 newFirstPoint, int distance, float newSpeed,
               const char* newSpriteName, int frameCount) : Enemy(newScreen, newGameScene, newFirstPoint, newSpeed),
                                            secondPoint(firstPoint + int2(distance, 0))
{
    sprite = new Sprite(new Surface(newSpriteName), frameCount);
    root = new Transform(firstPoint,int2(sprite->GetHeight(), sprite->GetWidth()));
    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
}

void Glider::PhysicsTick()
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

void Glider::Move()
{
    vel.x = static_cast<float>(dir) * speed;
    vel.y = sin(timer.elapsed() * 2);
}
