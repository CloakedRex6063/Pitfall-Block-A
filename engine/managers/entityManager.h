#pragma once

class EntityManager
{
public:
    EntityManager(const Map* map, GameScene* gameScene, DynamicArray* objects,Surface* screen);
    void SpawnEnemies();

private:
    const Map* map = nullptr;
    GameScene* gameScene = nullptr;
    DynamicArray* objects = nullptr;
    Surface* screen = nullptr;
    
    TimerHandle<EntityManager> balloonHandle;
    public:
    Balloon* balloon = nullptr;
    private:
    float2 balloonLoc = float2(0,0);

public:
    void SpawnBalloon();
    void Tick(float deltaTime);
};
