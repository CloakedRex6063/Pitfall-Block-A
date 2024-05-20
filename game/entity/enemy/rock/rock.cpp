#include "precomp.h"
#include "game/entity/enemy/enemy.h"
#include "rock.h"

#include "game/entity/player/player.h"
#include "game/scene/gameScene/gameScene.h"

Rock::Rock(Surface* newScreen, GameScene* newGameScene, float2 newFirstPoint, float newSpeed, const char* newSpriteName):
    Enemy(newScreen, newGameScene, newFirstPoint, newSpeed)
{
    sprite = new Sprite(new Surface(newSpriteName), 1);
    root = new Transform(firstPoint,int2(sprite->GetHeight(), sprite->GetWidth()));
    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
}

void Rock::PhysicsTick()
{
    Move(-1);
    GetRoot()->Move(vel);
}

void Rock::OnCollision(Object* other)
{
    if (const auto player = dynamic_cast<Player*>(other))
    {
        player->SetVel(float2(0,0));
        GetGameScene()->GetGame()->ReduceGameScore(100);
    }
}

void Rock::Move(int dir)
{
    vel.x = static_cast<float>(dir) * speed;
}
