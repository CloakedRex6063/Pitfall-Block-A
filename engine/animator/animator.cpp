#include "precomp.h"
#include "engine/timer/timer.h"
#include "animator.h"

void Animator::Play(int animIndex)
{
    if (curAnim == animIndex) return;
    Resume();
    animHandle.InvalidateTimer();
    curAnim = animIndex;
    if (anims[animIndex]->GetNumFrames() > 1)
    {
        animHandle.SetTimer(anims[animIndex]->GetFrameTime(), true, this, &Animator::IncreaseFrame);
        return;
    }
    sprite->SetFrame(anims[animIndex]->GetCurFrame());
}

void Animator::Pause()
{
    bPaused = true;
}

void Animator::Resume()
{
    bPaused = false;
}

Animator::~Animator()
{
    for (auto i = 0; i < numAnims; i++)
    {
        delete anims[i];
    }
    delete[] anims;
}

void Animator::Tick(float deltaTime)
{
    animHandle.Tick(deltaTime);
}

void Animator::IncreaseFrame()
{
    if (!bPaused)
    {
        anims[curAnim]->AddToCurFrame(1);
        if (anims[curAnim]->GetCurFrame() > anims[curAnim]->GetFrames()[anims[curAnim]->GetNumFrames() - 1])
        {
            anims[curAnim]->SetCurFrame(anims[curAnim]->GetFrames()[0]);
        }
        sprite->SetFrame(anims[curAnim]->GetCurFrame());
    }
}

