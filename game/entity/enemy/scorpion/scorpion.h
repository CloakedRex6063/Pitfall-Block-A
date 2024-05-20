#pragma once

class Scorpion : public Enemy
{
public:
    Scorpion(Surface* newScreen, GameScene* newGameScene, float2 newPos, int dis, float newSpeed,
             const char* newSpriteName);
    void PhysicsTick() override;
    void Move();
private:
    float2 secondPoint = float2(0, 0);
    int dir = 1;
};
