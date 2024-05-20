#pragma once

class Camera
{
    inline static float2 pos = { 0,0 };
    Camera() = default;

public:

    static float2 GetPos() { return pos; }
    
    static void Move(float2 target)
    {
        // Move the camera
        pos += target;
        pos.x = pos.x <= 0 ? 0 : pos.x;
        pos.x = pos.x >= LVLWIDTH - SCRWIDTH ? LVLWIDTH - SCRWIDTH : pos.x;
        pos.y = pos.y <= 0 ? 0 : pos.y;
        pos.y = pos.y >= LVLHEIGHT - SCRHEIGHT ? LVLHEIGHT - SCRHEIGHT : pos.y;
    }

    static void SetPos(float2 target)
    {
        pos = target;
        pos.x = pos.x <= 0 ? 0 : pos.x;
        pos.x = pos.x >= LVLWIDTH - SCRWIDTH ? LVLWIDTH - SCRWIDTH : pos.x;
        pos.y = pos.y <= 0 ? 0 : pos.y;
        pos.y = pos.y >= LVLHEIGHT - SCRHEIGHT ? LVLHEIGHT - SCRHEIGHT : pos.y;
    }
};
