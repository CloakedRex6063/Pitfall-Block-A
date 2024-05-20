#include "precomp.h"
#include "enemy.h"
#include "game/scene/gameScene/gameScene.h"
#include "game/entity/player/player.h"

Enemy::Enemy(Surface* newScreen, GameScene* newGameScene, float2 newFirstPoint, float newSpeed) :
    Object(newScreen, newGameScene), firstPoint(newFirstPoint), speed(newSpeed)
{
}

void Enemy::Render()
{
    const float2 loc = root->GetScreenLoc();
    if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) return;
    sprite->Draw(GetScreen(), root->GetScreenLoc());
}

void Enemy::OnCollision(Object* other)
{
    if (dynamic_cast<Player*>(other))
    {
        GetGameScene()->RespawnPlayer();
    }
}

