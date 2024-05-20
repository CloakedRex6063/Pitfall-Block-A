#include "precomp.h"
#include "scene.h"
#include "engine/managers/uiManager.h"

void Scene::Tick(float)
{
    GetUIManager()->Tick();
}

void Scene::Render()
{
    GetUIManager()->Render();
}

void Scene::PhysicsTick()
{

}

void Scene::MouseMove(int x, int y)
{
    uiManager->MouseMove(x,y);
    mousePos.x = x; mousePos.y = y;
}
