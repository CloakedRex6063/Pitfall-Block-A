#include "precomp.h"
#include "croc.h"

#include "game/entity/player/player.h"
#include "game/scene/gameScene/gameScene.h"

Croc::Croc(Surface* newScreen, GameScene* newGameScene, int2 newPos, float newSpeed, const char* newSpriteName):
    Object(newScreen, newGameScene), speed(newSpeed)
{
    sprite = new Sprite(new Surface(newSpriteName), 2);
    root = new Transform(newPos, int2(sprite->GetWidth(),sprite->GetHeight()));
    player = GetGameScene()->GetObjectArray()->FindObjectOfType<Player>();
    waitHandle.SetTimer(speed, true, this, &Croc::Open);
}

void Croc::Tick(float deltaTime)
{
    waitHandle.Tick(deltaTime);
}

void Croc::PhysicsTick()
{
    ResolveCollision();
}

void Croc::Render()
{
    const float2 loc = root->GetScreenLoc();
    if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) return;
    sprite->Draw(GetScreen(), root->GetScreenLoc());
}

void Croc::ResolveAABB(float2& playerPos, const float2 playerSize, const float2 objectPos, const float2 objectSize) const
{
    // Calculate the overlap on both the X and Y axes
    const float xOverlap = Math::Min(objectPos.x + objectSize.x, playerPos.x + playerSize.x) - Math::Max(objectPos.x, playerPos.x);
    const float yOverlap = Math::Min(objectPos.y + objectSize.y, playerPos.y + playerSize.y) - Math::Max(objectPos.y, playerPos.y);

    // Check if there's a collision (both xOverlap and yOverlap are positive)
    if (xOverlap > 0 && yOverlap > 0)
    {
        // Determine which axis has the smaller overlap (to separate on that axis)
        if (xOverlap < yOverlap)
        {
            if (playerPos.x < objectPos.x)
            {
                playerPos.x -= xOverlap;
            }
            else
            {
                playerPos.x += xOverlap;
            }
        }
        else
        {
            // Adjust positions along the Y-axis
            if (playerPos.y < objectPos.y)
            {
                playerPos.y -= yOverlap;
            }
            else
            {
                playerPos.y += yOverlap;
            }
        }
        player->GetRoot()->SetWorldLoc(playerPos);
        player->bOnCrocodile = true;
    }
}

void Croc::ResolveCollision() const
{
    auto playerPos = player->GetRoot()->GetWorldLoc();
    const auto playerSize = player->GetRoot()->GetDim();
    const auto objectPos = root->GetWorldLoc();
    const auto objectSize = root->GetDim();

    if (objectPos.x < playerPos.x + playerSize.x &&
        objectPos.x + objectSize.x > playerPos.x &&
        objectPos.y < playerPos.y + playerSize.y &&
        objectPos.y + objectSize.y > playerPos.y)
    {
        
        if (!open)
        {
            ResolveAABB(playerPos, playerSize, objectPos, objectSize);
            return;
        }
        GetGameScene()->RespawnPlayer();
    }
}

void Croc::Open()
{
    open = !open;
    sprite->SetFrame(open);
}
