#include "ButtonsBase.h"

int ButtonsBase::getClick()
{
	if(isButtonHold[1])
		return -1;
	return clickedBtn;
}

void ButtonsBase::checkMouse()
{
	clickedBtn = -1;
	if(!Mouse::isButtonPressed(Mouse::Button::Left))
		isButtonHold[0]=isButtonHold[1]=false;
	else
	{
		if(isButtonHold[0])
			isButtonHold[1]=true;
		else
			isButtonHold[0]=true;
	}
}

void ButtonsBase::drawText(unsigned int i_num,Vector2f btnPos,RenderWindow *i_wind)
{
	// === Вывод текста на кнопке ===
	btnTitle.setString(btnList[i_num].title);
	btnTitle.setOrigin(Vector2f(9*btnList[i_num].title.getSize(),20));
	// -- Вывод тени --
	btnTitle.setPosition(btnPos.x+3,btnPos.y+3);
	btnTitle.setColor(Color::Black);
	i_wind->draw(btnTitle);
	// -- Вывод основного текста --
	btnTitle.setPosition(btnPos.x,btnPos.y);
	if(btnList[i_num].isActive)
		btnTitle.setColor(Color::White);
	else
		btnTitle.setColor(Color::Color(100,100,100,255));
	i_wind->draw(btnTitle);
}

void ButtonsBase::loadBaseData()
{
	btnFont.loadFromFile("etc/EuropeB.otf");
	btnTitle=Text("",btnFont,30);
	btnTitle.setStyle(Text::Regular);
}

ButtonsBase::ButtonsBase(void)
{
	loadBaseData();
}


ButtonsBase::~ButtonsBase(void)
{
	btnList.clear();
}
