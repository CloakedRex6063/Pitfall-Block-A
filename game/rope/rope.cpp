#include "precomp.h"
#include "rope.h"

#include <iostream>

Rope::Rope(Surface* newScreen, GameScene* newGameScene, int2 pos, int2 dim, int ropeLength, float ropeSpeed) : Object(newScreen,newGameScene)
{
    root = new Transform(pos, dim);
    this->ropeLength = ropeLength;
    this->ropeSpeed = ropeSpeed;
    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
}

void Rope::PhysicsTick()
{
    // Oscillate the rope
    // Made using formulas given by Damy Y1 from https://www.desmos.com/calculator/7csw1v6hwt
    
    timePassed += FIXED_DELTA_TIME;
    
    timeOsc = cos(timePassed * ropeSpeed) * maxAngle;

    prevPos = curPos;
    curPos = float2(sin(timeOsc) * static_cast<float>(ropeLength),-cos(timeOsc) * static_cast<float>(ropeLength));

    add.x = curPos.x;
    add.y = curPos.y;
}

void Rope::Render()
{
    const float2 loc = root->GetScreenLoc();
    if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) return;
    const float2 startPoints = {root->GetScreenLoc().x, root->GetScreenLoc().y};
    const float2 endPoints = { startPoints.x + add.x,startPoints.y - add.y };
    GetScreen()->ThickLine(startPoints.x, startPoints.y, endPoints.x, endPoints.y, 5, 0x964B00);
}

float2 Rope::GetEndPoints() const
{
    return {root->GetWorldLoc().x + add.x,root->GetWorldLoc().y - add.y};
}

float2 Rope::GetVel() const
{
    return curPos - prevPos;
}


