#include "precomp.h"
#include "engine/ui/button/button.h"
#include "winScene.h"

WinScene::WinScene(Surface* newScreen, Game* newGame): Scene(newScreen, newGame)
{
    const auto elems = new UIElement*[5];
    const auto buttonSprites = new Sprite*[3];
    const auto score = Math::IntToChar(GetGame()->GetGameScore(),5);
    buttonSprites[0] = new Sprite(new Surface("assets/ui/buttonBlue.png"),1);
    buttonSprites[1] = new Sprite(new Surface("assets/ui/buttonBlueHover.png"),1);
    buttonSprites[2] = new Sprite(new Surface("assets/ui/buttonBluePressed.png"),1);
    elems[0] = new Button(GetScreen(), buttonSprites, this, &WinScene::TitleScreen, int2(SCRWIDTH / 2,SCRHEIGHT / 2),
                          "Title Screen", 0xffffff, int2(30, 15), int2(2, 2));
    elems[1] = new Button(GetScreen(),buttonSprites,this,&WinScene::Quit,int2(SCRWIDTH/2,SCRHEIGHT/2+100),
                          "Quit",0xffffff,int2(60,15),int2(2,2));
    elems[2] = new Text(GetScreen(),int2(SCRWIDTH/2,SCRHEIGHT/2-200),"You Win!",0xffffff,int2(2,2));
    elems[3] = new Text(GetScreen(),int2(SCRWIDTH/2,SCRHEIGHT/2-100),"Score: ",0xffffff,int2(2,2));
    elems[4] = new Text(GetScreen(),int2(SCRWIDTH/2 + 100,SCRHEIGHT/2-100),score,0xffffff,int2(2,2));
    uiManager = new UIManager(elems,5);
    GetGame()->ResetGameScore();
}

void WinScene::Tick(float deltaTime)
{
    Scene::Tick(deltaTime);
}

void WinScene::Render()
{
    Scene::Render();
}

void WinScene::TitleScreen()
{
    GetGame()->SetGameState(Scene_MainMenu);
}

void WinScene::Quit()
{
    GetGame()->bRunning = false;
}
