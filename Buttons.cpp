#include "Buttons.h"
#include <stdio.h>

void Buttons::update(RenderWindow *i_wind)
{
	checkMouse();
	Vector2i mPos = Mouse::getPosition(*i_wind); //позиция курсора мыши
	//Проверка мыши
	for(int i = 0;i<btnList.size();i++)
	{
		if(!btnList[i].isActive)
			continue;
		Vector2f btnPos = countBtnPos(i,i_wind);
		if(
			( ((mPos.x-btnPos.x) * (mPos.x-(btnPos.x+btnParList[i].size.x))) < 0 )
			&&
			( ((mPos.y-btnPos.y) * (mPos.y-(btnPos.y+btnParList[i].size.y))) < 0 )
			)
			if((Mouse::isButtonPressed(Mouse::Button::Left))&&!isButtonHold[1])
			{
				btnList[i].isHover = false;
				if((clickedBtn== -1) || (clickedBtn>btnList[i].index))
					clickedBtn = btnList[i].index;
			}
			else
			{
				btnList[i].isHover = true;
			}
		else
		{
			btnList[i].isHover = false;
		}
	}
}
void Buttons::draw(RenderWindow *i_wind)
{
	Texture* btntex = new Texture;
	btntex->loadFromFile("img/inactive-btn-200x50.png");
	for(int i=0;i<btnList.size();i++)
	{
		Vector2f btnPos = countBtnPos(i,i_wind);
		RectangleShape r;
		r.setSize(Vector2f(btnParList[i].size.x,btnParList[i].size.y));
		r.setPosition(btnPos);
		if(btnList[i].isActive==false)
		{
			{
				btntex->loadFromFile("img/inactive-btn-200x50.png");
				r.setTexture(btntex);
			}
		}
		else
		{
			if(btnList[i].isHover)
			{
				btntex->loadFromFile("img/yellow-btn-200x50.png");
				r.setTexture(btntex);
			}
			else
			{
				btntex->loadFromFile("img/green-btn-200x50.png");
				r.setTexture(btntex);
			}
		}
		i_wind->draw(r);
		drawText(i,Vector2f(btnPos.x+btnParList[i].size.x/2,btnPos.y+btnParList[i].size.y/2),i_wind);
	}
	delete btntex;
}

Vector2f Buttons::countBtnPos(unsigned int i_num,RenderWindow *i_wind)
{
	Vector2f ret(btnList[i_num].position.x,btnList[i_num].position.y);
	switch(btnParList[i_num].alX)
	{
	case centerX: ret.x+=i_wind->getSize().x/2-btnParList[i_num].size.x/2; break;
	case right: ret.x+=i_wind->getSize().x-btnParList[i_num].size.x; break;
	case noneX: break;
	}
	switch(btnParList[i_num].alY)
	{
	case centerY: ret.y+=i_wind->getSize().y/2-btnParList[i_num].size.y/2; break;
	case bottom: ret.y+=i_wind->getSize().y-btnParList[i_num].size.y; break;
	case noneY: break;
	}
	return ret;
}

void Buttons::addButton(FloatRect i_coord,btnAlignX i_alX,btnAlignY i_alY,String i_title,int i_index,bool i_active)
{
	//Создание новой кнопки
	ButtonNode newBtn;
	newBtn.position = Vector2f(i_coord.left,i_coord.top);
	newBtn.title = i_title;
	newBtn.index = i_index;
	newBtn.isHover = false;
	newBtn.isActive = i_active;
	btnList.push_back(newBtn);

	//Создание доп. параметров новой кнопки
	ButtonParameters newPar;
	newPar.size = Vector2f(i_coord.width,i_coord.height);
	newPar.alX = i_alX;
	newPar.alY = i_alY;
	btnParList.push_back(newPar);
}

void Buttons::removeAllButtons()
{
	btnList.clear();
	btnParList.clear();
}

void Buttons::loadData()
{
	btnTexture.loadFromFile("img/inactive-btn-200x50.png");
	btnSprite.setTexture(btnTexture);
}

Buttons::Buttons(void)
{
	loadData();
}


Buttons::~Buttons(void)
{
	removeAllButtons();
}
