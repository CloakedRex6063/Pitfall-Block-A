#pragma once

class Checkpoint : public Object
{
public:
    Checkpoint(Surface* screen, GameScene* newGameScene, float2 pos, int checkPointID, const char* spriteName);
    void Render() override;
    void OnCollision(Object* other) override;
    int checkpointID;
};
