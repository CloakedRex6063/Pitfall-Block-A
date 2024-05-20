#include "precomp.h"
#include "game.h"
#include "engine/animator/animator.h"
#include "engine/managers/soundManager.h"
#include "engine/map/map.h"
#include "game/rope/rope.h"
#include "player.h"
#include <iostream>
#include "game/balloon/balloon.h"
#include "game/scene/gameScene/gameScene.h"

Player::Player(Surface* newScreen, GameScene* newGameScene, Map* colliderMap, float2 newPos, const char* newSpriteName) : Object(newScreen,newGameScene)
{
    sprite = new Sprite(new Surface(newSpriteName), 9);
    root = new Transform(newPos,int2(sprite->GetWidth(),sprite->GetHeight()));

    const auto transform = new Transform(root,root->GetWorldLoc(),root->GetDim());
    collider = new Collider2D(transform, this);
    collider->colliderMap = colliderMap;

    collider->bTrigger = false;

    const auto idleAnimFrames = new int[1] {0};
    const auto runAnimFrames = new int[5] {1,2,3,4,5};
    const auto jumpAnimFrames = new int[1] {1}; 
    const auto ropeAnimFrames = new int[1] {6};
    const auto climbAnimFrames = new int[2] {7,8};
    const auto idleAnim = new Animation(idleAnimFrames, 1, 0.f);
    const auto runAnim = new Animation(runAnimFrames,5, 0.1f);
    const auto jumpAnim = new Animation(jumpAnimFrames,1,0.f);
    const auto ropeAnim = new Animation(ropeAnimFrames,1,0.f);
    const auto climbAnim = new Animation(climbAnimFrames,2,0.1f);
    const auto anims = new Animation*[5] {idleAnim,runAnim, jumpAnim, ropeAnim, climbAnim};
    animator = new Animator(sprite,anims,4);
    bJumpRequested = true;
}

Player::~Player()
{
    delete animator;
}

void Player::Tick(float deltaTime)
{
    animator->Tick(deltaTime);
    HandleInput();
}

void Player::PhysicsTick()
{
    if (GetMoveState() != State_Sinking)
    {
        HandleCollision();
        HandleMovementStates();
    }
    vel.x = Math::Clamp(vel.x,-walkSpeed,walkSpeed);
    vel.y = Math::Clamp(vel.y,jumpHeight,maxGrav);
    root->Move(vel);
    
    prevPos = curPos;
    curPos = root->GetWorldLoc();
}

void Player::Render()
{
    sprite->Draw(GetScreen(), root->GetScreenLoc());
}

void Player::OnCollision(Object* other)
{
    if (!other->GetCollider()->bTrigger)
    {
        collider->ResolveCollision(other->GetCollider());
    }
}

void Player::HandleCollision() 
{
    collider->TileCollision();
    const ColHitInfo hitInfo = collider->hitInfo;

    if (hitInfo.bHitWall && GetMoveState() == State_Jumping)
    {
        vel.x = 0;
    }
    
    if (bOnCrocodile)
    {
        SetMoveState(State_Grounded);
        return;
    }
        
    CheckForLadders();
    CheckForWater();

    if (GetMoveState() == State_Jumping)
    {
        CheckForRopes();
    }
    if (curBalloon)
    {
        SetMoveState(State_OnBalloon);
        return;
    }
    if (curRope && GetMoveState() == State_Jumping && bCanSwing)
    {
        SetMoveState(State_OnRope);
        return;
    }
    if (bCanClimb && ((vertDir == 1 && ladderClimbDir == 1) || vertDir == -1 && ladderClimbDir == -1))
    {
        SetMoveState(State_OnLadder);
    }
    else
    {
        if (GetMoveState() != State_OnRope)
        {
            if (bInWater)
            {
                SetMoveState(State_Swimming);
                return;
            }
            if (hitInfo.bOnFloor)
            {
                SetMoveState(State_Grounded);
                return;
            }
            if (GetMoveState() != State_OnLadder && GetMoveState() != State_Swimming)
            {
                SetMoveState(State_Jumping);
            }
        }
    }
}

void Player::HandleInput()
{
    Input::IsKeyPressed('A') ? sideDir = -1 : Input::IsKeyPressed('D')  ? sideDir = 1 : sideDir = 0;
    Input::IsKeyPressed('W') ? vertDir = -1 : Input::IsKeyPressed('S')  ? vertDir = 1 : vertDir = 0;
    if (Input::IsKeyPressed(VK_SPACE))
    {
        bJumpRequested = true;
    }
}

void Player::CheckBoundary() const
{
    // Check if the player is within the boundaries of the level
    if (root->GetWorldLoc().x < 0)
    {
        root->SetWorldLoc(float2(0,root->GetWorldLoc().y));
    }
    if (root->GetWorldLoc().x + 32 >= LVLWIDTH)
    {
        root->SetWorldLoc(float2(LVLWIDTH - 32,root->GetWorldLoc().y));
    }
}

void Player::SetMoveState(EMoveState newState)
{
    if (curMoveState != newState)
    {
        switch (newState)
        {
        case State_Grounded:
            OnLanded();
            break;
        case State_Jumping:
            animator->Play(2);
            if (!bJumpRequested)
            {
                vel.x = 0;
                GetGameScene()->GetGame()->GetSoundManager()->Play(4);
            }
            bJumpRequested = false;
            break;
        case State_OnRope:
            animator->Play(3);
            GetGameScene()->GetGame()->GetSoundManager()->Play(3);
            vel = {0,0};
            bCanSwing = false;
            break;
        case State_OnLadder:
            AttachToLadder();
            vel = {0,0};
            break;
        case State_Swimming:
            animator->Play(2);
            vel = {0,0};
            break;
        case State_Sinking:
            vel = float2(0,0.25f);
            break;
        case State_OnBalloon:
            animator->Play(3);
            vel = {0,0};
            break;
        }
        curMoveState = newState;
    }
}

void Player::HandleMovementStates()
{
    switch (curMoveState)
    {
    case State_Grounded:
        HandleGroundState();
        break;
    case State_Jumping:
        HandleJumpState();
        break;
    case State_OnRope:
        HandleRopeState();
        break;
    case State_OnLadder:
        HandleLadderState();
        break;
    case State_Swimming:
        HandleSwimState();
        break;
    case State_Sinking:
        break;
    case State_OnBalloon:
        HandleBalloonState();
        break;
    }
}

void Player::HandleGroundState()
{
    Run();
    Jump();
    if (sideDir != 0)
    {
        animator->Play(1);
    }
    else
    {
        animator->Play(0);
    }
}

void Player::HandleJumpState()
{
    HandleGravity();
}

void Player::HandleRopeState() 
{
    AttachToRope();
    DetachFromRope();
}

void Player::HandleLadderState()
{
    if (vertDir == 0)
    {
        animator->Pause();
    }
    else
    {
        animator->Resume();
        animator->Play(4);
    }
    Climb();
    if (!LadderUp() && sideDir != 0)
    {
        vel.x = static_cast<float>(sideDir) * ladderJumpSpeed;
        vel.y = jumpHeight * 2;
        bJumpRequested = true;
        SetMoveState(State_Jumping);
    }
}

void Player::HandleSwimState()
{
    Swim();
    HandleSwimGravity();
}

void Player::HandleBalloonState()
{
    AttachToBalloon();
    MoveWithBalloon();
}

void Player::OnLanded()
{
    bJumpRequested = false;
    bCanSwing = true;
}

void Player::Run()
{
    vel.x = static_cast<float>(sideDir) * walkSpeed;
}

void Player::Jump()
{
    if (GetMoveState() == State_Grounded && bJumpRequested)
    {
        bOnCrocodile = false;
        vel.y = jumpHeight;
        GetGameScene()->GetGame()->GetSoundManager()->Play(0);
    }
}

void Player::HandleGravity()
{
    vel.y += grav;
    vel.y = Math::Clamp(vel.y,jumpHeight,maxGrav);
}

void Player::CheckForLadders()
{
    ladderLoc = int2(0,0);
    if (GetMoveState() == State_Grounded)
    {
        const int2 playerTile = int2(Math::Round(static_cast<const float>(root->GetWorldLoc().x) / TILESIZE),
                                     Math::Round(static_cast<const float>(root->GetWorldLoc().y) / TILESIZE));
        const int2 lowerCheckTile1 = playerTile + int2(1,3);
        const int2 lowerCheckTile2 = playerTile + int2(-1,3);

        const int lowerCheckTileID = GetGameScene()->GetMaps()[0]->GetTileArr()[lowerCheckTile1.y][lowerCheckTile1.x];
        const int lowerCheckTileID2 = GetGameScene()->GetMaps()[0]->GetTileArr()[lowerCheckTile2.y][lowerCheckTile2.x];
        
        if (lowerCheckTileID == 19)
        {
            ladderLoc = lowerCheckTile1 + float2(0.5f,0);
            ladderClimbDir = 1;
            bCanClimb = true;
            return;
        }
        if (lowerCheckTileID2 == 20)
        {
            ladderLoc = lowerCheckTile2 - float2(0.5f,0);
            ladderClimbDir = 1;
            bCanClimb = true;
            return;
        }
        for (auto i = playerTile.x - 1; i < playerTile.x + 1; i++)
        {
            const int tileID = GetGameScene()->GetMaps()[0]->GetTileArr()[playerTile.y][i];
            if (tileID == 21)
            {
                ladderLoc = int2(i,playerTile.y) + float2(0.5f,0);
                ladderClimbDir = -1;
                bCanClimb = true;
                return;
            }
            if (tileID == 22)
            {
                ladderLoc = int2(i,playerTile.y) - float2(0.5f,0);
                ladderClimbDir = -1;
                bCanClimb = true;
                return;
            }
        }
    }
    bCanClimb = false;
}

bool Player::LadderUp() const
{
    const int2 playerTile = int2(Math::Round(static_cast<const float>(root->GetWorldLoc().x) / TILESIZE),
                                 Math::Round(static_cast<const float>(root->GetWorldLoc().y) / TILESIZE));
    const int2 playerTile2 = playerTile + int2(0,1);
    const int playerTileID = GetGameScene()->GetMaps()[0]->GetTileArr()[playerTile.y][playerTile.x];
    const int playerTileID2 = GetGameScene()->GetMaps()[0]->GetTileArr()[playerTile2.y][playerTile2.x];
    if (playerTileID == 19 || playerTileID == 20 || playerTileID == 21 || playerTileID == 22)
    {
        return true;
    }
    if (playerTileID2 == 19 || playerTileID2 == 20 || playerTileID2 == 21 || playerTileID2 == 22)
    {
        return true;
    }
    return false;
}

void Player::Climb()
{
    if (!LadderUp())
    {
        if (vertDir == -1)
        {
            vel.y = 0;
            return;
        }
    }
    vel.y = static_cast<float>(vertDir) * climbSpeed;
}

void Player::AttachToLadder() const
{
    root->SetWorldLoc(ladderLoc * TILESIZE);
}

void Player::CheckForRopes()
{
    const auto playerTopLeft = GetRoot()->GetWorldLoc();
    const auto playerBotRight = playerTopLeft + GetRoot()->GetDim();

    if (const auto rope = GetGameScene()->GetObjectArray()->FindObjectOfType<Rope>())
    {
        const auto ropeTopLeft = rope->GetEndPoints() - rope->GetRoot()->GetDim();
        const auto ropeBotRight = rope->GetEndPoints() + rope->GetRoot()->GetDim();
                
        const auto colX = playerBotRight.x >= ropeTopLeft.x && playerTopLeft.x <= ropeBotRight.x;
        const auto colY = playerBotRight.y >= ropeTopLeft.y && playerTopLeft.y <= ropeBotRight.y;

        // check if the player is on a rope
        if (colX && colY)
        {
            curRope = rope;
            return;
        }
        curRope = nullptr;
    }
}

void Player::AttachToRope() const
{
    root->SetWorldLoc(curRope->GetEndPoints() - int2(16,0));
}

void Player::DetachFromRope()
{
    if (Input::IsKeyPressed('S'))
    {
        RopeTransferVel();
    }
}

void Player::RopeTransferVel()
{
    vel = float2(curRope->GetVel().x, 0);
    SetMoveState(State_Jumping);
    curRope = nullptr;
}

void Player::CheckForWater()
{
    const int2 playerTile = int2(Math::Round(static_cast<const float>(root->GetWorldLoc().x) / TILESIZE),
                             Math::Round(static_cast<const float>(root->GetWorldLoc().y) / TILESIZE));
    const int2 checkTile = playerTile;
    const int checkTileID = GetGameScene()->GetMaps()[0]->GetTileArr()[checkTile.y][checkTile.x];

    if (checkTileID == 23)
    {
        bInWater = true;
        return;
    }
    bInWater = false;
}

void Player::HandleSwimGravity()
{
    if (bInWater)
    {
        vel.y += swimGrav;
        vel.y = Math::Clamp(vel.y,maxSwimGrav,swimSpeed);
        return;
    }
    if (vertDir != 1 && GetMoveState() == State_Swimming)
    {
        vel.y = 0;
    }
}

void Player::Swim()
{
    vel.x = static_cast<float>(sideDir) * swimSpeed;
    if (!bInWater)
    {
        if (collider->hitInfo.bHitWall)
        {
            vel.x = ladderJumpSpeed * static_cast<float>(sideDir);
            vel.y = jumpHeight * 2;
            bJumpRequested = true;
            SetMoveState(State_Jumping);
            return;
        }
        if (vertDir == -1)
        {
            vel.y = 0;
            return;
        }
    }
    vel.y = static_cast<float>(vertDir) * climbSpeed;
}

void Player::AttachToBalloon() const
{
    if (curBalloon)
    {
        root->SetWorldLoc(curBalloon->GetRoot()->GetWorldLoc() + float2(4,56));
    }
}

void Player::MoveWithBalloon()
{
    if (curBalloon)
    {
        vel.x = static_cast<float>(sideDir) * balloonSpeed;
        curBalloon->GetRoot()->Move(vel);
    }
}


