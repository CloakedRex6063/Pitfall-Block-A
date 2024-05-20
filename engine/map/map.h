#pragma once

class Map
{
public:
    Map(Surface* newScreen, const char* mapFile, const char* tileSet, float newParallaxFactor = 0.f);
    ~Map();
private:
    void CreateMap(const char* mapFile, const char* tileSet);
public:
    void DrawMap() const;

    Sprite* GetMapSprite() const { return mapSprite; }
    int** GetTileArr() const { return mapTileArr; }

    int GetRows() const { return rows; }
    int GetColumns() const { return cols; }

    bool bWaterFrame = false;

private:
    int** mapTileArr = nullptr;
    Sprite* mapSprite = nullptr;

    Surface* screen = nullptr;

    int rows = 0;
    int cols = 0;
    
    float parallaxFactor = 0;
};
