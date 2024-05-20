#pragma once

// Made with help from chatGPT

template <typename F>
class TimerHandle
{

    bool bValid = false;
public:
    bool IsValid() const {return bValid;}

private:
    float curTime = 0;
    float maxTime = 0;

public:
    float GetTime() const {return curTime;}
    void SetTime(float time) {curTime = time;}
    float GetMaxTime() const {return maxTime;}

private:
    bool bCanLoop = false;
    bool bStarted = false;

public:
    bool CanLoop() const {return bCanLoop;}
    bool IsStarted() const {return bStarted;}

private:
    F* object = nullptr;
    void (F::*function)() = nullptr;

public:
    void SetTimer(float time, bool bNewLoop, F* obj, void(F::*newFunction)())
    {
        maxTime = time;
        bCanLoop = bNewLoop;
        bValid = true;
        bStarted = true;
        object = obj;
        function = newFunction;
    }

    void Reset()
    {
        curTime = 0;
        bStarted = true;
    }

    void InvalidateTimer()
    {
        bValid = false;
    }

    void Tick(float deltaTime)
    {
        if (!IsValid()) return;
        curTime += deltaTime;
        if (curTime >= maxTime)
        {
            curTime = 0;
            (object->*function)();
            if (bCanLoop) return;
            InvalidateTimer();
        }
    }
};
