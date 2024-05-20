#pragma once

class Hole : public Object
{
public:
    Hole(Surface* newScreen, GameScene* newGameScene, int2 newPos, int2 newDim, float newSpeed);
    void Tick(float deltaTime) override;
    void PhysicsTick() override;
    void Render() override;

private:
    void Progress();
    void Wait();

    float2 midPoint = float2(0, 0);
    float2 holeTopLeft = float2(0, 0);
    float2 holeBotRight = float2(0, 0);

    float speed;
    TimerHandle<Hole> progressHandle;
    TimerHandle<Hole> waitHandle;
    Timer* timer;
    
    float progress = 0;
    bool flip = false;
    bool bWait = false;

    float maxWaitTime = 1.5f;
};

