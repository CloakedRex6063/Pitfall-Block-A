#pragma once

class Object;
class Rope;
class Map;
class Transform;
class DynamicArray;

struct ColHitInfo
{
    bool bOnFloor = false;
    bool bHitWall = false;
};

class Collider2D
{
public:
    Collider2D(Transform* newTransform, Object* newParent) : colliderTransform(newTransform), parent(newParent) {}
    ~Collider2D();

    void AABBCollision(const DynamicArray* objectList);
    void ResolveCollision(const Collider2D* other) const;
    void TileCollision();
    bool PixelPerfectCollision(float2 objectPos, float2 objectSize, float2 otherPos, float2 otherSize, Sprite* objectImage, Sprite* otherImage);

    Transform* colliderTransform = nullptr;
    Object* parent = nullptr;
    Map* colliderMap = nullptr;
    bool bTrigger = true;
    ColHitInfo hitInfo;
};
