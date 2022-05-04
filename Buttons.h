#pragma once
#include "main.h"
#include "ButtonsBase.h"

class Buttons: public ButtonsBase
{
public:
	enum btnAlignX
	{
		left,
		centerX,
		right,
		noneX
	};
	enum btnAlignY
	{
		top,
		centerY,
		bottom,
		noneY
	};
	struct ButtonParameters
	{
		Vector2f size;
		btnAlignX alX;
		btnAlignY alY;
	};
private:
	vector<ButtonParameters> btnParList; //параметры кнопок
	Vector2f countBtnPos(unsigned int i_num,RenderWindow* i_wind);
public:
	void addButton(FloatRect i_coord, btnAlignX i_alX, btnAlignY i_alY, String i_title, int i_index, bool i_active);//добавление кнопки
	void removeAllButtons();
	void update(RenderWindow* i_wind);
	void draw(RenderWindow* i_wind);
	void loadData();
	Buttons();
	~Buttons();
};
