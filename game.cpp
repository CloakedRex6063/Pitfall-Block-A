// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"
#include "json.hpp"
#include <iostream>
#include "engine/managers/soundManager.h"
#include "game/scene/gameScene/gameScene.h"
#include "game/scene/mainMenuScene/mainMenuScene.h"
#include "game/scene/optionsScene/optionsScene.h"
#include "game/scene/winScene/winScene.h"
#include "game.h"

Game::~Game()
{
	delete curScene;
	delete soundManager;
}

void Game::Init()
{
	LoadSettings();
	LoadGameData();
	CreateSounds();
	SetGameState(Scene_MainMenu);
}

void Game::Tick(float deltaTime)
{
	this->dT = deltaTime;

	screen->Clear(0);
	HandleStateTick();
	HandleInput();
}

void Game::PhysicsTick()
{
	HandleStatePhysics();
}

void Game::Shutdown()
{
	SaveSettings();
	SaveGameData();
}

void Game::LoadSettings()
{
	if (fopen(settingsFileName, "r"))
	{
		string text = TextFileRead(settingsFileName);
		if (!text.empty())
		{
			nlohmann::json jsonData = nlohmann::json::parse(text);
			settings.bUseCRT = jsonData["useCRT"];
			settings.bUseFXAA = jsonData["useFXAA"];
			settings.soundVolume = jsonData["soundVolume"];
			settings.musicVolume = jsonData["musicVolume"];
		}
	}
	else
	{
		SaveSettings();
	}
}

void Game::SaveSettings()
{
	FILE* file = fopen(settingsFileName, "w");
	nlohmann::json jsonData;
	jsonData["useCRT"] = settings.bUseCRT;
	jsonData["useFXAA"] = settings.bUseFXAA;
	jsonData["soundVolume"] = settings.soundVolume;
	jsonData["musicVolume"] = settings.musicVolume;
	const auto text = jsonData.dump(0);
	const auto result = fputs(text.c_str(), file);
	if (result == EOF)
	{
		printf("Failed to save settings\n");
	}
	else
	{
		printf("Saved Settings Successfully\n");
	}
	if (fclose(file) == 0)
	{
		printf("File closed successfully.\n");
	}
	else
	{
		printf("Failed to close the file.\n");
	}
}

void Game::LoadGameData()
{
	if (fopen(dataFileName, "r"))
	{
		string text = TextFileRead(dataFileName);
		if (!text.empty())
		{
			nlohmann::json jsonData = nlohmann::json::parse(text);
			gameData.checkPointID = jsonData["checkPointID"];
			gameData.score = jsonData["score"];
		}
	}
	else
	{
		SaveGameData();
	}
}

void Game::SaveGameData()
{
	FILE* file = fopen(dataFileName, "w");
	nlohmann::json jsonData;
	jsonData["checkPointID"] = gameData.checkPointID;
	jsonData["score"] = gameData.score;
	const auto text = jsonData.dump(0);
	const auto result = fputs(text.c_str(), file);
	if (result == EOF)
	{
		printf("Failed to save data\n");
	}
	else
	{
		printf("Saved Game Data Successfully\n");
	}
	if (fclose(file) == 0)
	{
		printf("File closed successfully.\n");
	}
	else
	{
		printf("Failed to close the file.\n");
	}
}

void Game::SetGameState(GameState state)
{
	if (state != curGameState)
	{
		Camera::SetPos(int2(0,0));
		curGameState = state;
		delete curScene;
		curScene = nullptr;
		switch (curGameState)
		{
		case Scene_MainMenu:
			soundManager->ReplayMusic(0);
			curScene = new MainMenuScene(screen,this);
			break;
		case Scene_Options:
			curScene = new OptionsScene(screen,this);
			break;
		case Scene_Playing:
			curScene = new GameScene(screen,this);
			break;
		case Scene_Win:
			SetActiveCheckpoint(-1);
			curScene = new WinScene(screen,this);
			break;
		}
	}
}

void Game::HandleInput()
{
	if (Input::IsKeyPressed(VK_ESCAPE))
	{
		bRunning = false;
	}
}

void Game::HandleStateTick() const
{
	curScene->Render();
	curScene->Tick(dT);
}

void Game::HandleStatePhysics() const
{
	curScene->PhysicsTick();
}

void Game::MouseDown(int)
{
}

void Game::MouseUp(int)
{
}

void Game::MouseWheel(float)
{
}

void Game::MouseMove(int x, int y)
{
	curScene->MouseMove(x,y);
	mousePos.x = x; mousePos.y = y;
}

void Game::CreateSounds()
{
	const auto music = new Audio::Sound*[1];
	music[0] = new Audio::Sound("assets/sounds/bgMusic.ogg",Audio::Sound::Type::Music);
	music[0]->loadMusic("assets/sounds/bgMusic.ogg");
	music[0]->setLooping(true);
	
	const auto sounds = new Audio::Sound*[5];
	sounds[0] = new Audio::Sound("assets/sounds/jump.ogg");
	sounds[1] = new Audio::Sound("assets/sounds/coin.ogg");
	sounds[2] = new Audio::Sound("assets/sounds/death.ogg");
	sounds[3] = new Audio::Sound("assets/sounds/rope.ogg");
	sounds[4] = new Audio::Sound("assets/sounds/fall.ogg");
	
	
	soundManager = new SoundManager(this,sounds,5,music,1);
}

SoundManager* Game::GetSoundManager() const
{
	return soundManager;
}

void Game::ResetGameScore()
{
	gameData.score = 0;
	printf("Score: %d\n",gameData.score);
}

void Game::AddGameScore(int score)
{
	gameData.score += score;
	printf("Score: %d\n",gameData.score);
}

void Game::ReduceGameScore(int score)
{
	gameData.score -= score;
	Math::Clamp(gameData.score,0,1000000);
	printf("Score: %d\n",gameData.score);
}

int Game::GetGameScore() const
{
	return gameData.score;
}

int Game::GetActiveCheckpoint() const
{
	return gameData.checkPointID;
}

void Game::SetActiveCheckpoint(int newCheckpointID)
{
	gameData.checkPointID = newCheckpointID;
}
