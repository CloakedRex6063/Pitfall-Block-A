#pragma once

class Math
{
public:
    static float GetDis(const float2 a, const float2 b) 
    {
        const float dx = a.x - b.x;
        const float dy = a.y - b.y;
        return sqrt(dx * dx + dy * dy);
    }

    static float Min(const float a, const float b)
    {
        return a < b ? a : b;
    }

    static int Min(const int a, const int b)
    {
        return a < b ? a : b;
    }

    static float Max(const float a, const float b)
    {
        return a > b ? a : b;
    }

    static int Max(const int a, const int b)
    {
        return a > b ? a : b;
    }
    
    static int Abs(const int a)
    {
        return a < 0 ? -a : a;
    }

    static int Round(const float a)
    {
        return static_cast<int>(a + 0.5f);
    }

    static int2 Round(const float2 a)
    {
        return {static_cast<int>(a.x + 0.5f), static_cast<int>(a.y + 0.5f)};
    }

    static int Clamp(int& value,const int min,const int max)
    {
        value = value < min ? min : value;
        value = value > max ? max : value;
        return value;
    }
    
    static float Clamp(float& value,const float min,const float max)
    {
        value = value < min ? min : value;
        value = value > max ? max : value;
        return value;
    }

    // Made with help of chatgpt
    static const char* IntToChar(int newInt, int width)
    {
        const auto buffer = new char [20] ;
        snprintf(buffer, sizeof(buffer), "%0*d", width, newInt);
        return buffer;
    }
};
