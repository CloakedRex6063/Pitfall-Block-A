#include "precomp.h"
#include "engine/timer/timer.h"
#include "game/entity/enemy/enemy.h"
#include "frog.h"

Frog::Frog(Surface* newScreen, GameScene* newGameScene, float2 newFirstPoint, int newMaxHeight, int newMaxDis,
    float newSpeed, float newWaitTimer, const char* newSpriteName): Enemy(newScreen, newGameScene, newFirstPoint, newSpeed)
{
    sprite = new Sprite(new Surface(newSpriteName), 2);
    root = new Transform(firstPoint,int2(sprite->GetHeight(), sprite->GetWidth()));
    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
    secondPoint = float2(firstPoint.x + static_cast<float>(newMaxDis) / 2, firstPoint.y - static_cast<float>(newMaxHeight));
    thirdPoint = float2(firstPoint.x + static_cast<float>(newMaxDis), firstPoint.y);
    waitTimer = newWaitTimer;
}

void Frog::Reset()
{
    waitHandle.InvalidateTimer();
}

void Frog::StartResetTimer()
{
    sprite->SetFrame(1);
    resetHandle.SetTimer(0.2f,false,this,&Frog::Reset);
}

void Frog::Tick(float deltaTime)
{
    waitHandle.Tick(deltaTime);
    resetHandle.Tick(deltaTime);
}

void Frog::PhysicsTick()
{
    if (Math::GetDis(root->GetWorldLoc(),secondPoint) < 0.01f )
    {
        bFallDown = true;
        fa = 0;
        ra = 0;
    }
    
    if (Math::GetDis(root->GetWorldLoc(),thirdPoint) < 0.01f )
    {
        bFallDown = false;
        bFlip = true;
        ra = 0;
        fa = 0;

        if (!resetHandle.IsValid() && !waitHandle.IsValid())
        {
            sprite->SetFrame(0);
            waitHandle.SetTimer(waitTimer,false,this,&Frog::StartResetTimer);
        }
    }

    if (Math::GetDis(root->GetWorldLoc(), firstPoint) < 0.01f)
    {
        bFallDown = false;
        bFlip = false;
        ra = 0;
        fa = 0;

        if (!resetHandle.IsValid() && !waitHandle.IsValid())
        {
            sprite->SetFrame(0);
            waitHandle.SetTimer(waitTimer,false,this,&Frog::StartResetTimer);
        }
    }

    if (!waitHandle.IsValid())
    {
        fa += speed * FIXED_DELTA_TIME;
        fa = clamp(fa,0.f,1.f);

        ra += speed * FIXED_DELTA_TIME;
        ra = clamp(ra,0.f,1.f);
    }

    // Move from left to right
    const float2 firstLerp = lerp(firstPoint,secondPoint,fa);
    const float2 secondLerp = lerp(secondPoint,thirdPoint,fa);

    // Move from right to left
    const float2 thirdLerp = lerp(thirdPoint,secondPoint,ra);
    const float2 fourthLerp = lerp(secondPoint,firstPoint,ra);

    if (bFlip && !bFallDown)
    {
        root->SetWorldLoc(thirdLerp);
    }
    else if (bFlip && bFallDown)
    {
        root->SetWorldLoc(fourthLerp);
    }
    else if (!bFlip && bFallDown)
    {
        root->SetWorldLoc(secondLerp);
    }
    else if (!bFlip && !bFallDown)
    {
        root->SetWorldLoc(firstLerp);
    }
}

