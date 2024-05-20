#include "precomp.h"
#include "engine/transform.h"
#include "engine/array/dynamicArray.h"
#include "engine/map/map.h"
#include "collider2D.h"

Collider2D::~Collider2D()
{
    delete colliderTransform;
}

void Collider2D::AABBCollision(const DynamicArray* objectList) 
{
    if(colliderTransform)
    {
        const float2 objectPos = colliderTransform->GetWorldLoc();
        const float2 objectSize = colliderTransform->GetDim();
    
        for (auto i = 0; i < objectList->GetSize(); i++)
        {
            if (objectList->AtIndex(i) && parent != objectList->AtIndex(i) && objectList->AtIndex(i)->GetCollider() && objectList->AtIndex(i)->GetCollider()->colliderTransform)
            {
                const float2 otherPos = objectList->AtIndex(i)->GetCollider()->colliderTransform->GetWorldLoc();
                if (Math::GetDis(objectPos,otherPos) < 200)
                {
                    const float2 otherSize = objectList->AtIndex(i)->GetCollider()->colliderTransform->GetDim();
                    if (objectPos.x < otherPos.x + otherSize.x &&
                        objectPos.x + objectSize.x > otherPos.x &&
                        objectPos.y < otherPos.y + otherSize.y &&
                        objectPos.y + objectSize.y > otherPos.y)
                    {
                        if (objectList->AtIndex(i)->GetSprite() && parent->GetSprite())
                        {
                            if (PixelPerfectCollision(objectPos, objectSize, otherPos, otherSize, parent->GetSprite(), objectList->AtIndex(i)->GetSprite()))
                            {
                                parent->OnCollision(objectList->AtIndex(i));
                            }
                        }
                        return;
                    }
                }
            }
        }
    }
}

void Collider2D::ResolveCollision(const Collider2D* other) const
{
    float2 objectPos = colliderTransform->GetWorldLoc();
    const float2 objectSize = colliderTransform->GetDim();

    const float2 otherPos = other->colliderTransform->GetWorldLoc();
    const float2 otherSize = other->colliderTransform->GetDim();
    
    // Calculate the overlap on both the X and Y axes
    const float xOverlap = Math::Min(objectPos.x + objectSize.x, otherPos.x + otherSize.x) - Math::Max(objectPos.x, otherPos.x);
    const float yOverlap = Math::Min(objectPos.y + objectSize.y, otherPos.y + otherSize.y) - Math::Max(objectPos.y, otherPos.y);

    // Check if there's a collision (both xOverlap and yOverlap are positive)
    if (xOverlap > 0 && yOverlap > 0)
    {
        // Determine which axis has the smaller overlap (to separate on that axis)
        if (xOverlap < yOverlap)
        {
            if (objectPos.x < otherPos.x)
            {
                objectPos.x -= xOverlap;
            }
            else
            {
                objectPos.x += xOverlap;
            }
        }
        else
        {
            // Adjust positions along the Y-axis
            if (objectPos.y < otherPos.y)
            {
                objectPos.y -= yOverlap;
            }
            else
            {
                objectPos.y += yOverlap;
            }
        }
        colliderTransform->GetParent()->SetWorldLoc(objectPos);
    }
}

void Collider2D::TileCollision()
{
    hitInfo = {};
    float2 objectPos = colliderTransform->GetWorldLoc();
    const float2 objectSize = colliderTransform->GetDim();

    const int2 floorTile = int2(Math::Round(static_cast<const float>(objectPos.x) / TILESIZE),
                                Math::Round(static_cast<const float>(objectPos.y) / TILESIZE)) + int2(0, 2);
    const int2 floorTilePos = floorTile * TILESIZE;

    const int2 leftWallTile = floorTile + int2(-1,-1);
    const int2 rightWallTile = floorTile + int2(1,-1);

    // Handle Floor Collision
    if (colliderMap->GetTileArr()[floorTile.y][floorTile.x] != -1)
    {
        if (objectPos.y < static_cast<float>(floorTilePos.y + TILESIZE) && objectPos.y + objectSize.y > static_cast<
            float>(floorTilePos.y))
        {
            const float overlapY = objectPos.y + objectSize.y - static_cast<float>(floorTilePos.y);
            objectPos.y -= overlapY;
            colliderTransform->GetParent()->SetWorldLoc(objectPos);
            hitInfo.bOnFloor = true;
        }
    }

    // Handle Left Wall Collision
    if (colliderMap->GetTileArr()[leftWallTile.y][leftWallTile.x] != -1)
    {
        const float2 leftWallTilePos = leftWallTile * TILESIZE;
        if (objectPos.x < leftWallTilePos.x + TILESIZE && objectPos.x + objectSize.x > leftWallTilePos.x)
        {
            const float overlapX = leftWallTilePos.x + TILESIZE - objectPos.x;
            objectPos.x += overlapX;
            colliderTransform->GetParent()->SetWorldLoc(objectPos);
            hitInfo.bHitWall = true;
        }
    }

    // Handle Right Wall Collision
    if (colliderMap->GetTileArr()[rightWallTile.y][rightWallTile.x] != -1)
    {
        const float2 rightWallTilePos = rightWallTile * TILESIZE;
        if (objectPos.x < rightWallTilePos.x + TILESIZE && objectPos.x + objectSize.x > rightWallTilePos.x)
        {
            const float overlapX = objectPos.x + objectSize.x - rightWallTilePos.x;
            objectPos.x -= overlapX;
            colliderTransform->GetParent()->SetWorldLoc(objectPos);
            hitInfo.bHitWall = true;
        }
    }
}

bool Collider2D::PixelPerfectCollision(float2 objectPos, float2 objectSize, float2 otherPos, float2 otherSize, Sprite* objectSprite, Sprite* otherSprite)
{
    int2 start;
    int2 end;
    start.x = static_cast<int>(Math::Max(objectPos.x, otherPos.x));
    end.x = static_cast<int>(Math::Min(objectPos.x + objectSize.x, otherPos.x + otherSize.x));
    start.y = static_cast<int>(Math::Max(objectPos.y, otherPos.y));
    end.y = static_cast<int>(Math::Min(objectPos.y + objectSize.y, otherPos.y + otherSize.y));

    for (int x = start.x; x < end.x; x++)
    {
        for (int y = start.y; y < end.y; y++)
        {
            const int2 pixel1 = int2(x - static_cast<int>(objectPos.x), y - static_cast<int>(objectPos.y));
            const int2 pixel2 = int2(x - static_cast<int>(otherPos.x), y - static_cast<int>(otherPos.y));
            // Check for collision within the pixel data of both sprites.
            if (!objectSprite->IsPixelTransparent(pixel1) && !otherSprite->IsPixelTransparent(pixel2))
            {
                return true; // Collision detected.
            }
        }
    }
    return false; // No collision detected.
}


