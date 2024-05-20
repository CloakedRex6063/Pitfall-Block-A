#pragma once

class GameScene;
class Collider2D;
class Transform;
// Object base class
// Any game object derives from this class
class Object
{
public:
    Object(Surface* newScreen, GameScene* newGameScene) {screen = newScreen; gameScene = newGameScene;}
    virtual void Tick(float) {}
    virtual void PhysicsTick() {}
    virtual void Render() {}
    virtual void OnCollision(Object*) {}
    virtual ~Object() {delete root; delete collider; delete sprite;}
    
    Surface* GetScreen() const {return screen;}
private:
    Surface* screen = nullptr;

public:
    GameScene* GetGameScene() const {return gameScene;}
private:
    GameScene* gameScene = nullptr;

public:
    Transform* GetRoot() const {return root;}
protected:
    Transform* root = nullptr;

public:
    Collider2D* GetCollider() const {return collider;}
protected:
    Collider2D* collider = nullptr;

public:
    Sprite* GetSprite() const {return sprite;}
protected:
    Sprite* sprite = nullptr;
};
