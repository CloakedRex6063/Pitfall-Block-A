#pragma once

class Coin final : public Object
{
public:
    Coin(Surface* newScreen, GameScene* newGameScene, float2 newPos, int newScore,
     const char* newSpriteImage);
    void OnCollision(Object* other) override;
    void Render() override;
    
    int score = 500;
};
