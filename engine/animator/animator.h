#pragma once

class Animation
{
public:
    Animation(int* newFrames, int newNumFrames, float newFrameTime) : frames(newFrames), numFrames(newNumFrames),
                                                                      curFrame(frames[0]), frameTime(newFrameTime) {}
    ~Animation() {delete[] frames;}
private:
    int* frames = nullptr;
    int numFrames = 0;
    int curFrame = 0;
    float frameTime = 0;

public:
    int* GetFrames() const {return frames;}
    
    int GetNumFrames() const {return numFrames;}

    float GetFrameTime() const {return frameTime;}
    void SetFrameTime(float newFrameTime) {frameTime = newFrameTime;}
    
    int GetCurFrame() const {return curFrame;}
    void AddToCurFrame(int i) {curFrame+= i;}
    void SetCurFrame(int newCurFrame) {curFrame = newCurFrame;}
};

class Animator
{
    Sprite* sprite = nullptr;
    Animation** anims = nullptr;
    int numAnims = 0;
    int curAnim = 0;
    TimerHandle<Animator> animHandle;
    bool bPaused = false;

public:
    Animator(Sprite* newSprite, Animation** newAnims, int newNumAnims) : sprite(newSprite), anims(newAnims), numAnims(newNumAnims) {}
    ~Animator();
    void Tick(float deltaTime);
    
    void Play(int animIndex);
    void Pause();
    void Resume();
    void IncreaseFrame();
};