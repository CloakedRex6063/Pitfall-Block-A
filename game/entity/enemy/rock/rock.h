#pragma once

class Rock final : public Enemy
{
public:
    Rock(Surface* newScreen,GameScene* newGameScene, float2 newFirstPoint, float newSpeed, const char* newSpriteName);
    void PhysicsTick() override;
    void OnCollision(Object* other) override;
    
    void Move(int dir);
};
