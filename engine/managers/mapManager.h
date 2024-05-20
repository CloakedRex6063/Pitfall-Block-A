#pragma once

class MapManager
{
public:
    MapManager(Surface* newScreen,Map** newMaps, int newMapCount);
    ~MapManager();
    void Tick(float deltaTime);
    void Render() const;

    void AnimateWater();
    
    Surface* screen;
    Map** maps;
    int mapCount = 0;
    TimerHandle<MapManager> waterTimer;
};
