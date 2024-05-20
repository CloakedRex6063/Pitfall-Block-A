// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023
#pragma once

class Scene;
class WinScene;
class OptionsScene;
class MainMenuScene;
class SoundManager;
class Enemy;
class Map;
class Balloon;
class Hole;
class Coin;
class Rope;
class Player;

// Json parser from https://github.com/nlohmann/json

namespace Tmpl8
{
    struct Settings
    {
        bool bUseCRT;
        bool bUseFXAA;
    	float musicVolume = 1.f;
    	float soundVolume = 1.f;
    };

	struct GameData
	{
		int checkPointID = -1;
		int score = 0;
	};

	enum GameState
	{
		Scene_MainMenu,
		Scene_Options,
		Scene_Playing,
		Scene_Win,
	};
	
    class Game : public TheApp
    {
    public:
    	~Game();
	    // game flow methods
        void Init() override;
        void Tick(float deltaTime) override;
    	void PhysicsTick() override;
        void Shutdown() override;

    	float GetDeltaTime() const {return dT;}

    private:
    	float dT = 0;

    	char const* settingsFileName = "settings.json";

    public:
    	// Settings
    	void LoadSettings();
    	void SaveSettings();
        Settings settings {false,false};

    	GameState GetGameState() const {return curGameState;}
    	void SetGameState(GameState state);

    	void HandleInput();
    	
    private:
    	GameState curGameState = Scene_Win;
		void HandleStateTick() const;
    	void HandleStatePhysics() const;
    	
    	Scene* curScene = nullptr;

    	void MouseDown(int button) override;
    	void MouseUp(int button) override;
        void MouseWheel(float x) override;
        void MouseMove(int x, int y) override;
        int2 mousePos = int2(0,0);

    	void CreateSounds();
    	SoundManager* soundManager = nullptr;
    public:
    	SoundManager* GetSoundManager() const;

    	const char* dataFileName = "data.json";
    	// GameState
    	void LoadGameData();
    	void SaveGameData();
    	GameData gameData {-1,0};
    	
    	void ResetGameScore();
	    void AddGameScore(int score);
    	void ReduceGameScore(int score);
	    [[nodiscard]] int GetGameScore() const;

	    int GetActiveCheckpoint() const;
    	void SetActiveCheckpoint(int newCheckpointID);
    };
	
} 