#include "precomp.h"
#include "balloon.h"

#include "engine/managers/entityManager.h"
#include "engine/map/map.h"
#include "game/entity/player/player.h"
#include "game/scene/gameScene/gameScene.h"

Balloon::Balloon(Surface* newScreen, GameScene* newGameScene, float2 newPos,float newSpeed) : Object(newScreen, newGameScene)
{
    sprite = new Sprite(new Surface("assets/balloon.png"), 1);
    root = new Transform(newPos, float2(static_cast<float>(sprite->GetWidth()),static_cast<float>(sprite->GetHeight())));
    speed = newSpeed;

    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
}

void Balloon::OnCollision(Object* other)
{
    if (const auto player = dynamic_cast<Player*>(other))
    {
        if (player->GetMoveState() != State_OnBalloon)
        {
            player->curBalloon = this;
            bPlayerAttached = true;
            vel.x = 0;
        }
    }
}

void Balloon::Tick(float)
{
    if (timer.elapsed() > 15 && !bPlayerAttached)
    {
        GetGameScene()->GetEntityManager()->SpawnBalloon();
        timer.reset();
    }
}

void Balloon::PhysicsTick()
{
    if (bPlayerAttached)
    {
        vel.y = -speed;
    }
    else
    {
        vel.x = -speed;
    }
    root->Move(vel);
    CheckForCollision();
}

void Balloon::Render()
{
    const float2 loc = root->GetScreenLoc();
    if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) return;
    sprite->Draw(GetScreen(), root->GetScreenLoc());
}

void Balloon::CheckForCollision() const
{
    const int2 balloonTileLeft = int2(Math::Round(static_cast<const float>(root->GetWorldLoc().x) / TILESIZE),
                         Math::Round(static_cast<const float>(root->GetWorldLoc().y) / TILESIZE)) + int2(-1, 0);
    const int balloonTileIDLeft = GetGameScene()->GetMaps()[0]->GetTileArr()[balloonTileLeft.y][balloonTileLeft.x];
    const int2 balloonTileRight = int2(Math::Round(static_cast<const float>(root->GetWorldLoc().x) / TILESIZE),
                        Math::Round(static_cast<const float>(root->GetWorldLoc().y) / TILESIZE)) + int2(1, 0);
    const int balloonTileIDRight = GetGameScene()->GetMaps()[0]->GetTileArr()[balloonTileRight.y][balloonTileRight.x];

    if (bPlayerAttached)
    {
        if (balloonTileIDLeft == 0 || balloonTileIDLeft == 1 || balloonTileIDLeft == 4 || balloonTileIDRight == 0 ||
            balloonTileIDRight == 1 || balloonTileIDRight == 4)
        {
            GetGameScene()->GetEntityManager()->SpawnBalloon();
        }
    }
}
