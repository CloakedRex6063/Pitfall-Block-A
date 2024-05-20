#include "precomp.h"
#include "loseScene.h"
#include "engine/ui/button/button.h"

LoseScene::LoseScene(Surface* newScreen, Game* newGame): Scene(newScreen, newGame)
{
    const auto elems = new UIElement*[3];
    const auto buttonSprites = new Sprite*[3];
    buttonSprites[0] = new Sprite(new Surface("assets/ui/buttonBlue.png"),1);
    buttonSprites[1] = new Sprite(new Surface("assets/ui/buttonBlueHover.png"),1);
    buttonSprites[2] = new Sprite(new Surface("assets/ui/buttonBluePressed.png"),1);
    elems[0] = new Button(GetScreen(), buttonSprites, this, &LoseScene::Retry, int2(SCRWIDTH / 2,SCRHEIGHT / 2),
                      "Retry", 0xffffff, int2(60, 15), int2(2, 2));
    elems[1] = new Button(GetScreen(), buttonSprites, this, &LoseScene::TitleScreen, int2(SCRWIDTH / 2,SCRHEIGHT / 2 + 100),
                          "Title Screen", 0xffffff, int2(30, 15), int2(2, 2));
    elems[2] = new Button(GetScreen(),buttonSprites,this,&LoseScene::Quit,int2(SCRWIDTH/2,SCRHEIGHT/2+200),
                          "Quit",0xffffff,int2(60,15),int2(2,2));
    uiManager = new UIManager(elems,3);
    GetGame()->ResetGameScore();
}

void LoseScene::Tick(float deltaTime)
{
    Scene::Tick(deltaTime);
}

void LoseScene::Render()
{
    Scene::Render();
}

void LoseScene::Retry()
{
    GetGame()->SetGameState(Scene_Playing);
}

void LoseScene::TitleScreen()
{
    GetGame()->SetActiveCheckpoint(-1);
    GetGame()->SetGameState(Scene_MainMenu);
}

void LoseScene::Quit()
{
    GetGame()->bRunning = false;
}
