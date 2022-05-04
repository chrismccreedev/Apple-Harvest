#include "GameMain.h"
#include "Game.hpp"
#include "main.h"

GameMain::GameMain():gState(MainMenu),choosedLevel("levels/Level1.tmx"),lastLevel(0)
{ 
	loadData();
	loadInterface(MainMenu);
}

FILE* data;
int sc = 0, apps = 0, he = 100, coins = 0; //�����, ������, ��������, ������

void GameMain::update(RenderWindow* wind, float time)
{
	background.setTextureRect(IntRect((bgTexture.getSize().x-wind->getSize().x)/2,(bgTexture.getSize().y-wind->getSize().y)/2,wind->getSize().x,wind->getSize().y));
	wind->draw(background);
	switch(gState)
	{
	case MainMenu:
		{
			wind->draw(logo);
			switch(ButtonList.getClick())
			{
			case 0:
				{
					ButtonList.removeAllButtons();
					loadInterface(ChooseLevel);
					gState = ChooseLevel;
					break;
				}
			case 2:
				{
					ButtonList.removeAllButtons();
					loadInterface(ExitYesNo);
					gState = ExitYesNo;
					break;
				}
			case 3:
				{
					ButtonList.removeAllButtons();
					loadInterface(About);
					gState = About;
					break;
				}
			case 4:
				{
					ButtonList.removeAllButtons();
					loadInterface(Control);
					gState = Control;
					break;
				}
			case 5:
				{
					ButtonList.removeAllButtons();
					loadInterface(Rules);
					gState = Rules;
					break;
				}
			}
			break;
		}
	case ExitYesNo:
		{
			Text title("�� ������������� ������ ����� �� ����?",tFont,30);
			title.setColor(Color::White);
			title.setStyle(Text::Bold);
			title.setPosition(wind->getSize().x/2-350,150);
			wind->draw(title);
			switch(ButtonList.getClick())
			{
			case 0:
				wind->close();
				break;
			case 1:
				ButtonList.removeAllButtons();
				loadInterface(MainMenu);
				gState = MainMenu;
				break;
			}
			break;
		}
	case About:
		{
			Text title("�� ����",tFont,30);
			title.setColor(Color::White);
			title.setStyle(Text::Bold);
			title.setPosition(wind->getSize().x/2-80,5);
			Text t("",tFont2,30);
			t.setColor(Color::Black);
			t.setStyle(Text::Regular);
			t.setPosition(50,100);
			String about;
			about = "Apple Harvest v1.0\n����� ����: ������� ��-13-1 ��������� ������ ����������\n\n(�) ��������� �.�. 2017\n\n�������������:\n-������ ����������� ���������� SFML;\n-������ ���������� TinyXML;\n-����� kychka-pc.ru � ����� ����� �������� - �� ������� �\n�������� ����� �� SFML, � ����� SFML-����������� ��� �����\n\"���\" �� ��������� ���� ��� ������� � ��������;\n-FamTrinli, ������������ YouTube - �� ����� �� �������� ������\n��� �����������.";
			t.setString(about);
			wind->draw(title);
			wind->draw(t);
			t.setPosition(48,98);
			t.setColor(Color::White);
			wind->draw(t);
			switch(ButtonList.getClick())
			{
			case 0:
				ButtonList.removeAllButtons();
				loadInterface(MainMenu);
				gState = MainMenu;
				break;
			}
			break;
		}
	case Rules:
		{
			Text title("�������",tFont,30);
			title.setColor(Color::White);
			title.setStyle(Text::Bold);
			title.setPosition(wind->getSize().x/2-100,5);
			Text t("",tFont2,27);
			t.setPosition(25,50);
			t.setColor(Color::Black);
			t.setStyle(Text::Regular);
			String rules;
			rules = "�� ������� �� ���� �� ����� ������, ������� ������� ����� �������\n������.\n�������� �� �����������            � ���������           ����������, ���������\n������     � ������     , ����� ���������� ��� ����� ������ ������,\n\n� ����������� ������������ �� ���� ������ (������       � ���������       ).\n\n����� ������ ��������� ������ � ������� �������     .\n\n���������� - �������-������� ���� ������� W, A, D.\n����� �������� �����, ���������� � ���� �������, ����� ������� SPACE.\n����� �������� ��������, �������� ��� �� ������.\n�� ������� ������ ��� - ��� �� ������� �������� ������� ��� ������\n��������. �������� ���������, ����� ������� H, � ���������� �� ������,\n����� I.\n\n��������!\n��������� ����������� (����          � �����          ) � �� ������������� �\n������� - ��� �������� ��������. ����� ��� ���������������,\n���������� ������� ������       .";
			t.setString(rules);

			Texture* rul_tex = new Texture[10]; //����� �� ����� �������� ��������, ������ � �.�.
			rul_tex[0].loadFromFile("etc/rul_sPlat.png");
			rul_tex[1].loadFromFile("etc/rul_mPlat.png");
			rul_tex[2].loadFromFile("etc/rul_apple.png");
			rul_tex[3].loadFromFile("etc/rul_coin.png");
			rul_tex[4].loadFromFile("etc/rul_wolf.png");
			rul_tex[5].loadFromFile("etc/rul_hunt.png");
			rul_tex[6].loadFromFile("etc/rul_end.png");
			rul_tex[7].loadFromFile("etc/rul_water.png");
			rul_tex[8].loadFromFile("etc/rul_bran.png");
			rul_tex[9].loadFromFile("etc/rul_chic.png");
			Sprite* s_rul = new Sprite[10];
			for(int i = 0; i<=9; i++)
				s_rul[i].setTexture(rul_tex[i]);
			s_rul[0].setPosition(Vector2f(380,115));
			s_rul[1].setPosition(Vector2f(620,115));
			s_rul[2].setPosition(Vector2f(116,140));
			s_rul[3].setPosition(Vector2f(268,140));
			s_rul[4].setPosition(Vector2f(708,180));
			s_rul[5].setPosition(Vector2f(905,170));
			s_rul[6].setPosition(Vector2f(700,240));
			s_rul[7].setPosition(Vector2f(412,522));
			s_rul[8].setPosition(Vector2f(568,522));
			s_rul[9].setPosition(Vector2f(390,569));
			for(int i = 0; i<=9; i++)
				wind->draw(s_rul[i]);
			delete [] rul_tex, s_rul;

			wind->draw(title);
			wind->draw(t);
			t.setColor(Color::White);
			t.setPosition(23,48);
			wind->draw(t);
			switch(ButtonList.getClick())
			{
			case 0:
				ButtonList.removeAllButtons();
				loadInterface(MainMenu);
				gState = MainMenu;
				break;
			}
			break;
		}
	case Control:
		{
			Text title("��������� ���������� � ������ ����",tFont,30);
			title.setColor(Color::White);
			title.setStyle(Text::Bold);
			title.setPosition(wind->getSize().x/2-320,5);
			wind->draw(title);
			switch(ButtonList.getClick())
			{
			case 0:
				ButtonList.removeAllButtons();
				loadInterface(MainMenu);
				gState = MainMenu;
				break;
			case 1:
				setFullScreenMode(!getFullScreenMode());
				ButtonList.removeAllButtons();
				loadInterface(gState);
				break;	
			case 2:
				setWASDcontrol(!getWASDcontrol());
				ButtonList.removeAllButtons();
				loadInterface(gState);
				break;
			case 3:
				setAutoSave(!getAutoSave());
				ButtonList.removeAllButtons();
				loadInterface(gState);
				break;
			}
			if(!getAutoSave())
				drawText("    ��������! �������������� ���������.\n��� ������������� ���������� ���� �������.",Vector2f(910,440),wind);
			break;
		}
	case ChooseLevel:
		{
			Text title("�������� �������",tFont,30);
			title.setColor(Color::White);
			title.setStyle(Text::Bold);
			title.setPosition(wind->getSize().x/2-150,5);
			wind->draw(title);
			switch(ButtonList.getClick())
			{
			case 0:
				ButtonList.removeAllButtons();
				loadInterface(MainMenu);
				gState = MainMenu;
				break;
			}
			if(ButtonList.getClick()>0 && ButtonList.getClick()!=11)
			{
				lastLevel = ButtonList.getClick();
				choosedLevel = getWay(lastLevel);
				ButtonList.removeAllButtons();
				loadInterface(Game);
				gState = Game;
			}
			if(ButtonList.getClick()==11) //������ �� ������ "��������� ��������� ����"
			{
				//��������� �������� ���������� ������ �� �����, � ����� ������, ��������, ���-�� �����, �����
				if((data = fopen("userdata.usd","rb"))!=NULL)
				{
					char path[20];
					fscanf(data,"%s %d %d %d %d", &path, &sc, &coins, &apps, &he);
					choosedLevel = path;
					fclose(data);
					ButtonList.removeAllButtons();
					loadInterface(Game);
					gState = Game;
				}
				else //���� ���� � ������� �� ������, �� ��������� �������� �� ���������
				{
					choosedLevel = "levels/Level1.tmx";
					sc = 0; coins = 0; apps = 0; he = 100;
					ButtonList.removeAllButtons();
					loadInterface(Game);
					gState = Game;
				}
			}
			break;
		}
	case Game:
		{
			EndGameVariants res;
			res = RunGame(choosedLevel,wind,sc,coins,apps,he,ButtonList);
			switch(res)
			{
			case Exit:
				{
					ButtonList.removeAllButtons();
					loadInterface(MainMenu);
					gState = MainMenu;
					break;
				}
			case Win:
				{
					ButtonList.removeAllButtons();
					loadInterface(GameWin);
					gState = GameWin;
					break;
				}
			case Lose:
				{
					ButtonList.removeAllButtons();
					loadInterface(GameLose);
					gState = GameLose;
					break;
				}
			case Replay:
				{
					ButtonList.removeAllButtons();
					loadInterface(Game);
					gState = Game;
				}
			}
			break;
		}
	case GameWin:
		{
			Texture* wintex = new Texture;
			wintex->loadFromFile("img/empty.png");
			RectangleShape EGD;
			EGD.setTexture(wintex);
			EGD.setPosition(0,0);
			EGD.setSize(Vector2f(1024,600));
			wind->draw(EGD);
			if(lastLevel!=10)
			{
				drawText("�����������! �� ������ �������!",Vector2f(500,200),wind);
			}
			else
			{
				drawText("���! �� ������ ��� ������\n  � ����� ������� ������.\n  ������ ������ ��������!",Vector2f(980,30),wind);
				int _coins = coins, _apps = apps, _sc = sc;
				std::ostringstream os1, os2, os3;
				os1<<_coins, os2<<_apps, os3<<_sc;
				drawText("���� ����������:",Vector2f(520,200),wind);
				String str = "�����:  "+os2.str()+"\n�����:  "+os1.str()+"\n\n�����:  "+os3.str()+" ������";
				drawText(str,Vector2f(720,250),wind);
			}
			ButtonList.removeAllButtons();
			loadInterface(GameWin);
			gState = GameWin;
			switch(ButtonList.getClick())
			{
			case 0:
				{
					ButtonList.removeAllButtons();
					loadInterface(ChooseLevel);
					gState = ChooseLevel;
					break;
				}
			case 1: //������ "����. �������"
				{
					lastLevel++;
					choosedLevel = getWay(lastLevel);
					if(getAutoSave())
					{
						data = fopen("userdata.usd","wb");
						char* tmp = new char[choosedLevel.size()+1];
						for(int i = 0; i<choosedLevel.size(); i++)
							tmp[i] = choosedLevel[i];
						tmp[choosedLevel.size()] = '\0';
						fprintf(data,"%s %d %d %d %d",tmp,sc,coins,apps,he);
						fclose(data);
						delete tmp;
					}
					else
					{
						if((data = fopen("userdata.usd","rb"))!=NULL)
						{
							char path[20];
							fscanf(data,"%*s %d %d %d %d",&sc,&coins,&apps,&he);
							fclose(data);
						}
						else
						{
							sc = 0; apps = 0;
							he = 100; coins = 0;
						}
					}

					ButtonList.removeAllButtons();
					loadInterface(Game);
					gState = Game;
					break;
				}
			case 2:
				{
					ButtonList.removeAllButtons();
					loadInterface(MainMenu);
					gState = MainMenu;
					break;
				}
			}
			delete wintex;
			break;
		}
	case GameLose:
		{
			Texture* losetex = new Texture;
			losetex->loadFromFile("img/empty.png");
			RectangleShape EGD;
			EGD.setTexture(losetex);
			EGD.setPosition(0,0);
			EGD.setSize(Vector2f(1024,600));
			wind->draw(EGD);
			drawText("� ���������, �� ���������!",Vector2f(500,200),wind);
			switch(ButtonList.getClick())
			{
			case 0:
				{
					ButtonList.removeAllButtons();
					loadInterface(ChooseLevel);
					gState = ChooseLevel;
					break;
				}
			case 1:
				{
					ButtonList.removeAllButtons();
					loadInterface(MainMenu);
					gState = MainMenu;
					break;
				}
			}
			delete losetex;
			break;
		}
	default:
		gState = MainMenu;
	}
	ButtonList.update(wind);
	ButtonList.draw(wind);
}

void GameMain::loadInterface(gameStatus i_state)
{
	switch(i_state)
	{
	case MainMenu:
		bgTexture.loadFromFile("img/screensaver.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,250,75),Buttons::left,Buttons::top,"�� ����",3,true);
		ButtonList.addButton(FloatRect(0,0,300,75),Buttons::centerX,Buttons::top,"���������",4,true);
		ButtonList.addButton(FloatRect(0,0,250,75),Buttons::right,Buttons::top,"�������",5,true);
		ButtonList.addButton(FloatRect(0,420,200,75),Buttons::centerX,Buttons::noneY,"������",0,true);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"�����",2,true);
		break;
	case ExitYesNo:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(288,300,200,50),Buttons::noneX,Buttons::noneY,"��",0,true);
		ButtonList.addButton(FloatRect(536,300,200,50),Buttons::noneX,Buttons::noneY,"���",1,true);
		break;
	case ChooseLevel:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"�����",0,true);
		ButtonList.addButton(FloatRect(240,180,200,50),Buttons::noneX,Buttons::noneY,"������� 1",1,true);
		ButtonList.addButton(FloatRect(240,250,200,50),Buttons::noneX,Buttons::noneY,"������� 2",2,true);
		ButtonList.addButton(FloatRect(240,320,200,50),Buttons::noneX,Buttons::noneY,"������� 3",3,true);
		ButtonList.addButton(FloatRect(240,390,200,50),Buttons::noneX,Buttons::noneY,"������� 4",4,true);
		ButtonList.addButton(FloatRect(240,460,200,50),Buttons::noneX,Buttons::noneY,"������� 5",5,true);
		ButtonList.addButton(FloatRect(580,180,200,50),Buttons::noneX,Buttons::noneY,"������� 6",6,true);
		ButtonList.addButton(FloatRect(580,250,200,50),Buttons::noneX,Buttons::noneY,"������� 7",7,true);
		ButtonList.addButton(FloatRect(580,320,200,50),Buttons::noneX,Buttons::noneY,"������� 8",8,true);
		ButtonList.addButton(FloatRect(580,390,200,50),Buttons::noneX,Buttons::noneY,"������� 9",9,true);
		ButtonList.addButton(FloatRect(580,460,200,50),Buttons::noneX,Buttons::noneY,"������� 10",10,true);
		ButtonList.addButton(FloatRect(290,90,440,50),Buttons::noneX,Buttons::noneY,"��������� ��������� ����",11,true);
		break;
	case About:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"�����",0,true);
		break;
	case Control:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"�����",0,true);
		
		if(getFullScreenMode())
			ButtonList.addButton(FloatRect(0,230,470,50),Buttons::centerX,Buttons::top,"�����: ������",1,true);
		else
			ButtonList.addButton(FloatRect(0,230,470,50),Buttons::centerX,Buttons::top,"�����: ������� �����",1,true);
		if(getWASDcontrol())
			ButtonList.addButton(FloatRect(0,290,470,50),Buttons::centerX,Buttons::top,"����������: WASD",2,true);
		else
			ButtonList.addButton(FloatRect(0,290,470,50),Buttons::centerX,Buttons::top,"����������: ������������",2,true);
		if(getAutoSave())
			ButtonList.addButton(FloatRect(0,350,470,50),Buttons::centerX,Buttons::top,"��������������: ���",3,true);
		else
			ButtonList.addButton(FloatRect(0,350,470,50),Buttons::centerX,Buttons::top,"��������������: ����",3,true);
		break;
	case Rules:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"�����",0,true);
		break;
	case Game:
		ButtonList.addButton(FloatRect(0,-38,300,50),Buttons::centerX,Buttons::centerY,"����������",0,true);
		ButtonList.addButton(FloatRect(0,38,300,50),Buttons::centerX,Buttons::centerY,"������ �������",3,true);
		if(!getAutoSave())
			ButtonList.addButton(FloatRect(0,114,300,50),Buttons::centerX,Buttons::centerY,"��������� ����",2,true);
		else
			ButtonList.addButton(FloatRect(0,114,300,50),Buttons::centerX,Buttons::centerY,"��������� ����",2,false);
		ButtonList.addButton(FloatRect(0,190,300,50),Buttons::centerX,Buttons::centerY,"������� ����",1,true);
		break;
	case GameWin:
		
		if(lastLevel!=10) //���� �� ����� �� ���������� (10) ������
		{
			ButtonList.addButton(FloatRect(0,20,300,50),Buttons::centerX,Buttons::centerY,"����� ������",0,true);
			ButtonList.addButton(FloatRect(0,90,300,50),Buttons::centerX,Buttons::centerY,"����. �������",1,true); //���� �� ���������
			ButtonList.addButton(FloatRect(0,160,300,50),Buttons::centerX,Buttons::centerY,"������� ����",2,true);
		}
		else
			{
				ButtonList.addButton(FloatRect(0,120,300,50),Buttons::centerX,Buttons::centerY,"����� ������",0,true);
				ButtonList.addButton(FloatRect(0,190,300,50),Buttons::centerX,Buttons::centerY,"������� ����",2,true);
			}
		break;
	case GameLose:
		ButtonList.addButton(FloatRect(0,45,300,50),Buttons::centerX,Buttons::centerY,"����� ������",0,true);
		ButtonList.addButton(FloatRect(0,115,300,50),Buttons::centerX,Buttons::centerY,"������� ����",1,true);
		break;
	}
}

Buttons& GameMain::getBtnList()
{
	return this->ButtonList;
}

gameStatus GameMain::getState()
{
	return gState;
}

void GameMain::setState(gameStatus gs)
{
	gState = gs;
}

std::string GameMain::getWay(int lvl)
{
	switch(lvl)
	{
	case 1: return "levels/Level1.tmx";
	case 2: return "levels/Level2.tmx";
	case 3: return "levels/Level3.tmx";
	case 4: return "levels/Level4.tmx";
	case 5: return "levels/Level5.tmx";
	case 6: return "levels/Level6.tmx";
	case 7: return "levels/Level7.tmx";
	case 8: return "levels/Level8.tmx";
	case 9: return "levels/Level9.tmx";
	case 10: return "levels/Level10.tmx";
	default: return "";
	}
}

int GameMain::getLastLevel()
{
	return lastLevel;
}

void GameMain::loadData()
{
	bgTexture.loadFromFile("img/screensaver.png");
	background.setTexture(bgTexture);
	lTexture.loadFromFile("img/logo.png");
	logo.setOrigin(200,125);
	logo.setTexture(lTexture);
	logo.setPosition(512,200);
	tFont.loadFromFile("etc/EuropeB.otf");
	tFont2.loadFromFile("etc/EuropeN.ttf");
}
