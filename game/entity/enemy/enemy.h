#pragma once

class GameScene;

class Enemy : public Object
{
public:
    Enemy(Surface* newScreen, GameScene* newGameScene, float2 newFirstPoint, float newSpeed);
    void Render() override;
    void OnCollision(Object* other) override;

protected:
    float2 vel = 0;
    float2 firstPoint = {};
    float speed = 0;
};
