#include "precomp.h"
#include "mainMenuScene.h"

#include <iostream>

#include "engine/managers/uiManager.h"
#include "engine/ui/button/button.h"

MainMenuScene::MainMenuScene(Surface* newScreen, Game* newGame): Scene(newScreen, newGame)
{
    const auto elems = new UIElement*[7];
    const auto buttonSprites = new Sprite*[3];
    buttonSprites[0] = new Sprite(new Surface("assets/ui/buttonBlue.png"),1);
    buttonSprites[1] = new Sprite(new Surface("assets/ui/buttonBlueHover.png"),1);
    buttonSprites[2] = new Sprite(new Surface("assets/ui/buttonBluePressed.png"),1);
    elems[0] = new Button(GetScreen(), buttonSprites, this, &MainMenuScene::Play, int2(SCRWIDTH / 2 - 50,SCRHEIGHT / 2 - 100),
                          "New Game", 0xffffff, int2(60, 15), int2(2, 2));
    elems[1] = new Button(GetScreen(), buttonSprites, this, &MainMenuScene::Resume, int2(SCRWIDTH / 2 - 50,SCRHEIGHT / 2),
                      "Resume", 0xffffff, int2(60, 15), int2(2, 2));
    elems[2] = new Button(GetScreen(),buttonSprites,this,&MainMenuScene::Options,int2(SCRWIDTH/2 - 50,SCRHEIGHT/2 + 100),
                          "Options",0xffffff,int2(60,15),int2(2,2));
    elems[3] = new Button(GetScreen(),buttonSprites,this,&MainMenuScene::Quit,int2(SCRWIDTH/2 - 50,SCRHEIGHT/2 + 200),
                          "Quit",0xffffff,int2(60,15),int2(2,2));
    elems[4] = new Text(GetScreen(),int2(0,SCRHEIGHT - 25),"WASD : Movement",0xffffff, int2(4,4));
    elems[5] = new Text(GetScreen(),int2(0,SCRHEIGHT - 75),"Space: Jump",0xffffff, int2(4,4));
    elems[6] = new Text(GetScreen(),int2(0,SCRHEIGHT - 125),"S : Detach From Rope",0xffffff, int2(4,4));
    uiManager = new UIManager(elems,7);
}

void MainMenuScene::Tick(float deltaTime)
{
    Scene::Tick(deltaTime);
}

void MainMenuScene::Render()
{
    Scene::Render();
}

void MainMenuScene::PhysicsTick()
{
}

void MainMenuScene::Play()
{
    GetGame()->SetActiveCheckpoint(-1);
    GetGame()->SetGameState(Scene_Playing);
}

void MainMenuScene::Resume()
{
    GetGame()->SetGameState(Scene_Playing);
}

void MainMenuScene::Options()
{
    cout << "Options" << endl;
    GetGame()->SetGameState(Scene_Options);
}

void MainMenuScene::Quit()
{
    cout << "Quit" << endl;
    GetGame()->bRunning = false;
}
