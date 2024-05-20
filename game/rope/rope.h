#pragma once

class Rope : public Object
{
public:
    Rope(Surface* newScreen, GameScene* newGameScene, int2 pos, int2 dim, int ropeLength, float ropeSpeed);
    void PhysicsTick() override;
    void Render() override;
    
    float2 GetEndPoints() const;
    float2 GetVel() const;


private:
    float2 prevPos = int2(0, 0);
    float2 curPos = int2(0, 0);
    float2 add = 0;
    float timeOsc = 0;

    float maxAngle = 0.6f;
    float ropeSpeed = 0.5f;
    float timePassed = 0.f;
    int ropeLength = 0;
};
