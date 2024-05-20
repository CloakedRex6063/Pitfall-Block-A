#include "precomp.h"
#include "mapManager.h"
#include "engine/map/map.h"

MapManager::MapManager(Surface* newScreen, Map** newMaps, int newMapCount): screen(newScreen), maps(newMaps), mapCount(newMapCount)
{
    waterTimer.SetTimer(1.5f,true,this,&MapManager::AnimateWater);
}

MapManager::~MapManager()
{
    for (int i = 0; i < mapCount; ++i)
    {
        delete maps[i];
    }
    delete maps;
}

void MapManager::Tick(float deltaTime)
{
    waterTimer.Tick(deltaTime);
}

void MapManager::Render() const
{
    for(auto i = 0; i < mapCount; i++)
    {
        if (maps)
        {
            if (maps[i]->GetMapSprite() != nullptr)
            {
                maps[i]->DrawMap();
            }
        }
    }
}

void MapManager::AnimateWater()
{
    maps[0]->bWaterFrame = !maps[0]->bWaterFrame;
}
