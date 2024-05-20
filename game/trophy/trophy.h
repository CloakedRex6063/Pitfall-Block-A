#pragma once

class Trophy : public Object
{
public:
    Trophy(Surface* screen, GameScene* newGameScene,int2 pos, const char* spriteName);
    void Render() override;
    
    void OnCollision(Object* other) override;
};
