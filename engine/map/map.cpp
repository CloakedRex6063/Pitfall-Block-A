#include "precomp.h"
#include "map.h"
#include "engine/parser/parser.h"

Map::Map(Surface* newScreen, const char* mapFile, const char* tileSet, float newParallaxFactor) :
    screen(newScreen), parallaxFactor(newParallaxFactor)
{
    CreateMap(mapFile,tileSet);
}

Map::~Map()
{
    delete mapSprite;
    for (int row = 0; row < rows; row++)
    {
        delete mapTileArr[row];
    }
    delete[] mapTileArr;
}

void Map::CreateMap(const char* mapFile, const char* tileSet)
{
    // Store the parsed csv data into a 2 dimensional array so the map can be rendered
    mapTileArr = Parser::ParseCSV(mapFile, rows, cols);
    
    if (tileSet != nullptr)
    {
        // Create a tilemap sprite 
        mapSprite = new Sprite(new Surface(tileSet), 25);
        return;
    }

    delete mapSprite;
}

void Map::DrawMap() const
{
    // Loop through the array and use the values to draw the correct tiles on the screen
    for (auto row = 0; row < rows; row++)
    {
        for (auto col = 0; col < cols; col++)
        {
            // Check if its not empty tile (it will crash without this check)
            if (mapTileArr[row][col] != -1)
            {
                const float ParallaxMult = parallaxFactor != 0.f ? parallaxFactor : 1.f;
                const auto loc = float2(static_cast<float>(col) * TILESIZE - Camera::GetPos().x * ParallaxMult, static_cast
                                        <float>(row) * TILESIZE - Camera::GetPos().y);
                if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) continue;
                // Set the frame of the tilemap sprite to the value of the array
                if (mapTileArr[row][col] == 23)
                {
                    if (row == 13)
                    {
                        mapSprite->SetFrame(bWaterFrame ? 24 : 23);
                    }
                    else
                    {
                        mapSprite->SetFrame(23);
                    }
                }
                else
                {
                    mapSprite->SetFrame(mapTileArr[row][col]); 
                }
                mapSprite->Draw(screen, loc);
            }
        }
    }
}
