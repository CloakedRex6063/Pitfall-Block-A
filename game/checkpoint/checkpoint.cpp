#include "precomp.h"
#include "checkpoint.h"

#include "game/entity/player/player.h"
#include "game/scene/gameScene/gameScene.h"

Checkpoint::Checkpoint(Surface* screen, GameScene* newGameScene, const float2 pos, const int checkPointID,
                       const char* spriteName): Object(screen, newGameScene), checkpointID(checkPointID)
{
    sprite = new Sprite(new Surface(spriteName), 1);
    root = new Transform(pos, int2(sprite->GetWidth(), sprite->GetHeight()));
    const auto transform = new Transform(root, root->GetWorldLoc(), root->GetDim());
    collider = new Collider2D(transform, this);
}

void Checkpoint::Render()
{
    const float2 loc = root->GetScreenLoc();
    if (loc.x < -100 || loc.x > SCRWIDTH || loc.y < -100 || loc.y > SCRHEIGHT) return;
    sprite->Draw(GetScreen(), root->GetScreenLoc());
}

void Checkpoint::OnCollision(Object* other)
{
    if (dynamic_cast<Player*>(other))
    {
        GetGameScene()->GetGame()->SetActiveCheckpoint(checkpointID);
    }
}
