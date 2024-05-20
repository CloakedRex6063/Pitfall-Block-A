#include "precomp.h"
#include "game/scene/gameScene/gameScene.h"
#include "game/entity/player/player.h"
#include "coin.h"

#include "engine/managers/soundManager.h"

Coin::Coin(Surface* newScreen, GameScene* newGameScene, float2 newPos, int newScore, const char* newSpriteImage): Object(newScreen, newGameScene)
{
    sprite = new Sprite(new Surface(newSpriteImage), 1);
    root = new Transform(newPos, int2(sprite->GetHeight(), sprite->GetWidth()));
    score = newScore;

    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
}

void Coin::OnCollision(Object* other)
{
    if (dynamic_cast<Player*>(other))
    {
        GetGameScene()->GetGame()->AddGameScore(score);
        GetGameScene()->GetGame()->GetSoundManager()->Play(1);
        GetGameScene()->GetObjectArray()->RemoveElem(this, false);
    }
}

void Coin::Render()
{
    const float2 loc = root->GetScreenLoc();
    if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) return;
    sprite->Draw(GetScreen(), root->GetScreenLoc());
}
