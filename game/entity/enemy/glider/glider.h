#pragma once

class Glider : public Enemy
{
public:
    Glider(Surface* newScreen, GameScene* newGameScene, int2 newFirstPoint, int distance, float newSpeed,
           const char* newSpriteName, int frameCount);
    void PhysicsTick() override;
    void Move();

private:
    Timer timer;
    float2 secondPoint = float2(0, 0);
    int dir = 1;
};
