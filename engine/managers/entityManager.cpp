#include "precomp.h"
#include "engine/map/map.h"
#include "entityManager.h"

#include "game/balloon/balloon.h"
#include "game/checkpoint/checkpoint.h"
#include "game/coin/coin.h"
#include "game/entity/enemy/croc/croc.h"
#include "game/entity/enemy/frog/frog.h"
#include "game/entity/enemy/glider/glider.h"
#include "game/entity/enemy/rock/rock.h"
#include "game/entity/enemy/scorpion/scorpion.h"
#include "game/entity/player/player.h"
#include "game/hole/hole.h"
#include "game/rope/rope.h"
#include "game/trophy/trophy.h"

EntityManager::EntityManager(const Map* map, GameScene* gameScene, DynamicArray* objects, Surface* screen) :
    map(map), gameScene(gameScene), objects(objects), screen(screen)
{
}

void EntityManager::SpawnEnemies()
{
    int checkPointIndex = -1;
    for (auto rows = 0; rows < map->GetRows(); rows++)
    {
        for (auto cols = 0; cols < map->GetColumns(); cols++)
        {
            const int tileID = map->GetTileArr()[rows][cols];
            if (tileID != -1)
            {
                switch (tileID)
                {
                case 0:
                    balloonLoc = float2(static_cast<float>(cols) * TILESIZE, static_cast<float>(rows) * TILESIZE);
                    SpawnBalloon();
                    break;
                case 1:
                    objects->AddElem(new Coin(screen, gameScene, int2(cols * TILESIZE, rows * TILESIZE),
                    500,"assets/coin.png"));
                    printf("Added Coin\n");
                    break;
                case 2:
                    objects->AddElem(new Croc(screen,gameScene, int2(cols * TILESIZE, rows * TILESIZE),
                    5,"assets/croc.png"));
                    printf("Added Crocodile\n");
                    break;
                case 3:
                    objects->AddElem(new Frog(screen,gameScene, int2(cols * TILESIZE, rows * TILESIZE),
                    100, 100, 2, 2,"assets/frog.png"));
                    printf("Added Frog\n");
                    break;
                case 4:
                    objects->AddElem(new Glider(screen,gameScene, int2(cols * TILESIZE, rows * TILESIZE),
                    1000,2,"assets/bat.png",1));
                    printf("Added Glider\n");
                    break;
                case 5:
                    objects->AddElem(new Glider(screen,gameScene, int2(cols * TILESIZE, rows * TILESIZE),
                    736,2,"assets/eel.png",2));
                    printf("Added Eel\n");
                    break;
                case 6:
                    objects->AddElem(new Rock(screen,gameScene, int2(cols * TILESIZE, rows * TILESIZE),
                    2,"assets/rock.png"));
                    printf("Added Rock\n");
                    break;
                case 7:
                    objects->AddElem(new Scorpion(screen,gameScene, int2(cols * TILESIZE, rows * TILESIZE), 1000,
                        1, "assets/scorpion.png"));
                    printf("Added Scorpion\n");
                    break;
                case 8:
                    objects->AddElem(new Hole(screen,gameScene, int2(cols * TILESIZE, rows * TILESIZE),
                    int2(192,64),400));
                    printf("Added Hole\n");
                    break;
                case 9:
                    objects->AddElem(new Rope(screen,gameScene, int2(cols * TILESIZE, rows * TILESIZE),
                        int2(32,32), 320, 1.5f));
                    printf("Added Rope\n");
                    break;
                case 10:
                    objects->AddElem(new Trophy(screen,gameScene,int2(cols * TILESIZE, rows * TILESIZE),"assets/trophy.png"));
                    printf("Added Trophy\n");
                    break;
                case 11:
                    objects->AddElem(new Checkpoint(screen,gameScene,int2(cols * TILESIZE, rows * TILESIZE),++checkPointIndex,"assets/checkpoint.png"));
                    break;
                default: break;
                }
            }
        }
    }
}

void EntityManager::SpawnBalloon()
{
    int index = -1;
    printf("Added Balloon\n");
    if (balloon)
    {
        index = objects->RemoveElem(balloon, false);
        objects->FindObjectOfType<Player>()->curBalloon = nullptr;
        balloon = nullptr;
    }
    balloon = new Balloon(screen,gameScene,balloonLoc,1.f);
    if (index != -1)
    {
        objects->SetElem(balloon,index);
        return;
    }
    objects->AddElem(balloon);
}

void EntityManager::Tick(float deltaTime)
{
    balloonHandle.Tick(deltaTime);
}
