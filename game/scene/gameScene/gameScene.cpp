#include "precomp.h"
#include "engine/map/map.h"
#include "engine/managers/mapManager.h"
#include "game/entity/player/player.h"
#include "gameScene.h"
#include "engine/managers/entityManager.h"
#include "game/checkpoint/checkpoint.h"

GameScene::GameScene(Surface* newScreen, Game* newGame): Scene(newScreen,newGame)
{
    const auto elems = new UIElement*[2];
    elems[0] = new Text(GetScreen(), float2(0,10), "Score:", 0xffffff, int2(3,3));
    elems[1] = new Text(GetScreen(), float2(125,10), "00000", 0xffffff, int2(3,3));
    uiManager = new UIManager(elems,2);
    CreateMap();
    CreateObjects();
}

GameScene::~GameScene()
{
    delete objects;
    delete mapManager;
}

void GameScene::Tick(float deltaTime)
{
    mapManager->Tick(deltaTime);
    entityManager->Tick(deltaTime);
    HandleObjectTick(deltaTime);
    Scene::Tick(deltaTime);
    const char* score = Math::IntToChar(GetGame()->GetGameScore(), 5);
    dynamic_cast<Text*>(uiManager->GetElement(1))->SetText(score);
}

void GameScene::Render()
{
    GetMapManager()->Render();
    HandleObjectRender();
    Scene::Render();
}

void GameScene::PhysicsTick()
{
    HandleObjectPhysics();
    if (bEnd) return;
    HandleCamera();
}

void GameScene::RespawnPlayer()
{
    auto playerPos = float2(100,354);
    if (GetGame()->GetActiveCheckpoint() != -1)
    {
        playerPos = checkpoints[GetGame()->GetActiveCheckpoint()]->GetRoot()->GetWorldLoc() - float2(0,32);
    }
    const auto player = objects->FindObjectOfType<Player>();
    player->GetRoot()->SetWorldLoc(playerPos);
    player->SetMoveState(State_Grounded);
    Camera::SetPos(int2(0,0));
}

void GameScene::HandleCamera() const
{
    if (const auto* pc = objects->FindObjectOfType<Player>())
    {
        Camera::SetPos(pc->GetRoot()->GetWorldLoc() - int2(SCRWIDTH/2,SCRHEIGHT/2));
    }
}

void GameScene::HandleObjectTick(float deltaTime) const
{
    for(int i = 0; i < objects->GetSize(); ++i)
    {
        if (objects->AtIndex(i))
        {
            objects->AtIndex(i)->Tick(deltaTime);
        }
    }
}

void GameScene::HandleObjectPhysics() const
{
    for(auto i = 0; i < objects->GetSize(); i++)
    {
        if (objects->AtIndex(i))
        {
            objects->AtIndex(i)->PhysicsTick();
            if (bEnd) return;
            if (objects->AtIndex(i)->GetCollider())
            {
                objects->AtIndex(i)->GetCollider()->AABBCollision(objects);
            }
            if (bEnd) return;
        }
    }
}

void GameScene::HandleObjectRender() const
{
    for(auto i = 0; i < objects->GetSize(); i++)
    {
        if (objects->AtIndex(i))
        {
            objects->AtIndex(i)->Render();
        }
    }
}

Map** GameScene::GetMaps() const
{
    return GetMapManager()->maps;
}

void GameScene::CreateMap()
{
    const auto maps = new Map* [4];
    maps[0] = new Map(GetScreen(), "assets/pitfall_Game.csv", "assets/gameMap.png");
    maps[1] = new Map(GetScreen(), "assets/pitfall_BG.csv", "assets/gameMap.png",0.25f);
    maps[2] = new Map(GetScreen(), "assets/pitfall_Collider.csv", nullptr);
    maps[3] = new Map(GetScreen(), "assets/pitfall_Entity.csv", nullptr);
    mapManager = new MapManager(GetScreen(),maps,4);
}

void GameScene::CreateObjects()
{
    objects = new DynamicArray();
    objects->AddElem(new Player(GetScreen(),this,GetMaps()[2],int2(0,0),"assets/player.png"));
    entityManager = new EntityManager(GetMaps()[3],this,objects,GetScreen());
    entityManager->SpawnEnemies();
    checkpoints = objects->FindObjectsOfType<Checkpoint>(numCheckpoints);
    auto playerPos = float2(100,354);
    if (GetGame()->GetActiveCheckpoint() != -1)
    {
        playerPos = checkpoints[GetGame()->GetActiveCheckpoint()]->GetRoot()->GetWorldLoc() - float2(0,32);
    }
    objects->FindObjectOfType<Player>()->GetRoot()->SetWorldLoc(playerPos);
}
