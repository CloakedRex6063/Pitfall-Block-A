#pragma once

class Transform
{
    // The parent according to which the relative position is calculated
    Transform* parent = nullptr;

    float2 dim = {0,0};
    float2 localPos = {0,0};
    float2 worldPos = {0,0};
    float2 screenPos = {0,0};

public:

    Transform(Transform* newParent,float2 newPos, float2 newDim)
    {
        // Initialise the parent with the given new parent
        parent = newParent;
        SetWorldLoc(newPos);
        dim = newDim;
    }

    Transform(float2 newPos, float2 newDim)
    {
        SetWorldLoc(newPos);
        dim = newDim;
    }

    // Get the transform parent of the current object transform
    Transform* GetParent() const { return parent; }

    /*
     * World Location
     */

    // Get the location of the object in the world space
    float2 GetWorldLoc() const { return GetParent() != nullptr ? GetParent()->GetWorldLoc() + localPos : worldPos; }

    // Set the location of the object in the world space
    void SetWorldLoc(const float2 newPos)
    {
        worldPos = newPos;
        localPos = GetParent() != nullptr ? GetWorldLoc() - GetParent()->GetWorldLoc() : worldPos;
        screenPos = worldPos - Camera::GetPos();
    }

    /*
     * Relative Location
     */

     // Get the location of the object relatively to the parent
     // Same as world position if there is no parent
    float2 GetRelLoc() const { return localPos; }

    // Set the location of the object relatively to the parent
    void SetRelLoc(const float2 newPos)
    {
        localPos = newPos;
        worldPos = GetParent() != nullptr ? GetParent()->GetWorldLoc() + GetRelLoc() : localPos;
        screenPos = worldPos - Camera::GetPos();
    }

    /*
     * Screen Location
     */

    float2 GetScreenLoc()
    {
        screenPos = GetWorldLoc() - Camera::GetPos();
        return screenPos;
    }

    void SetScreenLoc(const float2 newPos)
    {
        screenPos = newPos;
        worldPos = screenPos + Camera::GetPos();
        localPos = GetParent() != nullptr ? GetWorldLoc() - GetParent()->GetWorldLoc() : worldPos;
    }

    /*
     * Size
     */

    float2 GetDim() const { return dim; }
    void SetDim(const float2 newDim) { dim = newDim; }

    // Move the transform by the given vector
    void Move(float2 pos)
    {
        const float2 newPos = GetWorldLoc() + pos;
        SetWorldLoc(newPos);
    }
};
