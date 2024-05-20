#pragma once

class Croc : public Object
{
public:
    Croc(Surface* newScreen, GameScene* newGameScene, int2 newPos, float newSpeed, const char* newSpriteName);
    void Tick(float deltaTime) override;
    void PhysicsTick() override;
    void Render() override;
    
    void ResolveAABB(float2& playerPos, float2 playerSize, float2 objectPos, float2 objectSize) const;
    void ResolveCollision() const;
    void Open();

private:
    float speed;
    bool open = false;
    TimerHandle<Croc> waitHandle;
    Player* player = nullptr;
};
