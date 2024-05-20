#pragma once

namespace Tmpl8
{
    class Game;
}

enum EMoveState
{
    State_Grounded,
    State_Jumping,
    State_OnRope,
    State_OnLadder,
    State_Swimming,
    State_Sinking,
    State_OnBalloon,
};

class Animator;
class GameScene;

class Player final : public Object
{
public:
    Player(Surface* newScreen, GameScene* newGameScene, Map* colliderMap, float2 newPos, const char* newSpriteName);
    ~Player() override;
    void Tick(float deltaTime) override;
    void PhysicsTick() override;
    void Render() override;
    void OnCollision(Object* other) override;
    
    void HandleCollision();
    void HandleInput();

    Animator* animator = nullptr;

    /*
     * Movement
     */
    float2 vel = {0,0};
    
    float2 prevPos = {0,0};
    float2 curPos = {0,0};

public:
    float2 GetVel() const {return curPos - prevPos;}
    void SetVel(float2 newVel) {vel = newVel;}
    
private:
    void CheckBoundary() const;

#pragma region Constants
public:
    float walkSpeed = 3;
    float balloonSpeed = 3;
    float climbSpeed = 2;
    float swimSpeed = 2;
    float jumpHeight = -12;
    float ladderJumpSpeed = 2;
    float grav = 1;
    float maxGrav = 2;
    float swimGrav = -1;
    float maxSwimGrav = -2;
#pragma endregion

#pragma region Movement States
private:
    EMoveState curMoveState = State_Grounded;

public:
    EMoveState GetMoveState() const {return curMoveState;}
    void SetMoveState(EMoveState newState);
    
    void HandleMovementStates();
    void HandleGroundState();
    void HandleJumpState();
    void HandleRopeState();
    void HandleLadderState();
    void HandleSwimState();
    void HandleBalloonState();

    void OnLanded();
#pragma endregion

#pragma region Ground Movement
    bool bOnCrocodile = false;
private:
    int sideDir = 0;
    int vertDir = 0;
    void Run();
#pragma endregion

#pragma region Aerial Movement
    bool bJumpRequested = false;
    void Jump();
    void HandleGravity();
#pragma endregion

#pragma region Ladder Movement
    void CheckForLadders();
    bool bCanClimb = false;
    int ladderClimbDir = 0;
    bool LadderUp() const;
    void Climb();
    void AttachToLadder() const;
    float2 ladderLoc;
#pragma endregion

#pragma region Rope Movement
    Rope* curRope = nullptr;
    bool bCanSwing = false;
    void CheckForRopes();
    void AttachToRope() const;
    void DetachFromRope();
    void RopeTransferVel();
#pragma endregion

#pragma region Water Movement
    void CheckForWater();
    void HandleSwimGravity();
    bool bInWater = false;
    void Swim();
#pragma  endregion

#pragma region Balloon
public:
    Balloon* curBalloon = nullptr;
private:
    void AttachToBalloon() const;
    void MoveWithBalloon();
#pragma endregion
    
};