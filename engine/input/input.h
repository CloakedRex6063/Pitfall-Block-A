#pragma once

class Input
{
public:
    static bool IsKeyPressed(int key)
    {
        static bool keyWasPressed = false;
        const bool isKeyPressed = IsKeyHeld(key);

        if (isKeyPressed && !keyWasPressed)
        {
            keyWasPressed = true;
            return true;
        }
        if (!isKeyPressed)
        {
            keyWasPressed = false;
        }

        return false;
    }
    static bool IsKeyReleased(int key)
    {
        static bool keyWasPressed = false;
        const bool isKeyPressed = IsKeyHeld(key);

        if (!isKeyPressed && keyWasPressed)
        {
            keyWasPressed = false;
            return true;
        }
        if (isKeyPressed)
        {
            keyWasPressed = true;
        }

        return false;
    }
    static bool IsKeyHeld(int key)
    {
        return GetAsyncKeyState(key) & 0x8000;
    }
};
