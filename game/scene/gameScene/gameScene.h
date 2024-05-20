#pragma once

class EntityManager;
class Checkpoint;
class MapManager;

class GameScene final : public Scene
{
public:
    GameScene(Surface* newScreen,Game* newGame);
    ~GameScene() override;
    void Tick(float deltaTime) override;
    void Render() override;
    void PhysicsTick() override;

    [[nodiscard]] DynamicArray* GetObjectArray() const {return objects;}
    EntityManager* GetEntityManager() const {return entityManager;}

private:
    DynamicArray* objects = nullptr;
    EntityManager* entityManager = nullptr;

    Checkpoint** checkpoints = nullptr;
    int numCheckpoints = 0;

public:
    void RespawnPlayer();

private:
    void CreateMap();
public:
    Map** GetMaps() const;
    MapManager* GetMapManager() const {return mapManager;}
private:
    MapManager* mapManager = nullptr;
    
    // event handling methods
    void HandleCamera() const;
    void HandleObjectTick(float deltaTime) const;
    void HandleObjectRender() const;
    void HandleObjectPhysics() const;
    
    void CreateObjects();
    
public:
    bool bEnd = false;
};
