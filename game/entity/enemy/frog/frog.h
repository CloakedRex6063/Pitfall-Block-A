#pragma once

class Frog : public Enemy
{
    
public:
    Frog(Surface* newScreen, GameScene* newGameScene, float2 newFirstPoint, int newMaxHeight, int newMaxDis, float newSpeed,
         float newWaitTimer, const char* newSpriteName);
    void Tick(float deltaTime) override;
    void PhysicsTick() override;
    void Reset();
    void StartResetTimer();
    
private:
    float2 secondPoint = float2(0, 0);
    float2 thirdPoint = float2(0, 0);
    float fa = 0;
    float ra = 0;
    TimerHandle<Frog> waitHandle;
    TimerHandle<Frog> resetHandle;
    
    bool bFallDown = false;
    bool bFlip  = false;
    
    float waitTimer = 0.5f;
};
