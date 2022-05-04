#pragma once
#include "main.h"
#include "Buttons.h"

enum gameStatus
	{
		MainMenu,
		ExitYesNo,
		ChooseLevel,
		Rules,
		Control,
		About,
		Game,
		GameWin,
		GameLose
	};

class GameMain
{
	gameStatus gState;
	Buttons ButtonList;
	std::string choosedLevel;
	Texture bgTexture;
	Texture lTexture;
	Font tFont;
	Font tFont2;
	Sprite background;
	Sprite logo;
	int lastLevel;

public:
	void update(RenderWindow* wind, float time);
	void loadInterface(gameStatus i_state); //загрузка интерфейса (кнопок) для разных состояний игры
	std::string getWay(int lvl);
	int getLastLevel();
	void loadData();
	gameStatus getState();
	void setState(gameStatus gs); //метод, устанавливающий состояние игры
	Buttons& getBtnList(); //метод, возвращающий список кнопок в окне
	GameMain();
};

