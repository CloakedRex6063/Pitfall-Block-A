#include "precomp.h"
#include "hole.h"

#include <iostream>

#include "game/scene/gameScene/gameScene.h"
#include "game/entity/player/player.h"

Hole::Hole(Surface* newScreen, GameScene* newGameScene, int2 newPos, int2 newDim, float newSpeed) : Object(newScreen,newGameScene)
{
    root = new Transform(newPos, newDim);
    speed = newSpeed;
    const auto transform = new Transform(newPos, newDim);
    collider = new Collider2D(transform, this);
    progressHandle.SetTimer(0.01f,true,this, &Hole::Progress);
}

void Hole::Tick(float deltaTime)
{
    progressHandle.Tick(deltaTime);
    waitHandle.Tick(deltaTime);
    midPoint = float2(root->GetWorldLoc().x,root->GetWorldLoc().y) + float2(root->GetDim().x/2,0);
    holeTopLeft = midPoint - float2(root->GetDim().x/2 * progress,0);
    holeBotRight = midPoint + float2(root->GetDim().x/2 * progress,root->GetDim().y);
}

void Hole::PhysicsTick()
{
    if (const auto player = GetGameScene()->GetObjectArray()->FindObjectOfType<Player>())
    {
        const auto playerTopLeft = player->GetRoot()->GetWorldLoc();
        const auto playerBotRight = player->GetRoot()->GetWorldLoc() + player->GetRoot()->GetDim();
        if (playerTopLeft.x > holeTopLeft.x && playerBotRight.x < holeBotRight.x && playerBotRight.y > holeTopLeft.y)
        {
            if (progress > 0 && player->GetMoveState() != State_Sinking)
            {
                player->SetMoveState(State_Sinking);
                timer = new Timer();
            }
            if (timer)
            {
                if (timer->elapsed() > 1.2)
                {
                    delete timer;
                    GetGameScene()->RespawnPlayer();
                }
            }
        }
    }
}

void Hole::Render()
{
    const float2 loc = root->GetScreenLoc();
    if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) return;
    const auto mid = int2(static_cast<int>(root->GetScreenLoc().x),static_cast<int>(root->GetScreenLoc().y)) + int2(static_cast<int>(root->GetDim().x / 2),0);
    const auto holeTopLeftInt = mid - int2(static_cast<int>(root->GetDim().x / 2 * progress),0);
    const auto holeBotRightInt = mid + int2(static_cast<int>(root->GetDim().x / 2 * progress),static_cast<int>(root->GetDim().y));
    if (progress > 0)
    {
        GetScreen()->Bar(holeTopLeftInt, holeBotRightInt, 0x230007);
    }
}

void Hole::Progress()
{
    if (!bWait)
    {
        progress += (flip ? -progressHandle.GetMaxTime() : progressHandle.GetMaxTime()) * speed * GetGameScene()->
            GetGame()->GetDeltaTime();
        progress = Math::Clamp(progress,0.f,1.f);
        collider->colliderTransform->SetDim(float2(root->GetDim().x * progress,root->GetDim().y));
        if (progress == 1.f || progress == 0.f)
        {
            bWait = true;
            waitHandle.SetTimer(maxWaitTime,false,this, &Hole::Wait);
        }
    }
}

void Hole::Wait()
{
    flip = !flip;
    bWait = false;
    waitHandle.Reset();
}
