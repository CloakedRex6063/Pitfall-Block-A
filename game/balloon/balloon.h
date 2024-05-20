#pragma once

class EntityManager;

class Balloon final : public Object
{
public:
    Balloon(Surface* newScreen, GameScene* newGameScene, float2 newPos, float newSpeed);
    void OnCollision(Object* other) override;
    void Tick(float deltaTime) override;
    void PhysicsTick() override;
    void Render() override;

    void CheckForCollision() const;
    

    bool bPlayerAttached = false;
    float speed = 5;
    float2 vel = float2(0,0);

    Timer timer;
};
