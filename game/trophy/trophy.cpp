#include "precomp.h"
#include "game/scene/gameScene/gameScene.h"
#include "game/entity/player/player.h"
#include "trophy.h"

Trophy::Trophy(Surface* screen, GameScene* newGameScene, int2 pos, const char* spriteName): Object(screen, newGameScene)
{
    sprite = new Sprite(new Surface(spriteName), 1);
    root = new Transform(pos, int2(sprite->GetWidth(), sprite->GetHeight()));
    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
}

void Trophy::Render()
{
    const float2 loc = root->GetScreenLoc();
    if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) return;
    sprite->Draw(GetScreen(), root->GetScreenLoc());
}

void Trophy::OnCollision(Object* other)
{
    if (dynamic_cast<Player*>(other))
    {
        GetGameScene()->GetGame()->AddGameScore(2000);
        GetGameScene()->bEnd = true;
        GetGameScene()->GetGame()->SetGameState(Scene_Win);
    }
}
