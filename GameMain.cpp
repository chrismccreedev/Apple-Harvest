#include "GameMain.h"
#include "Game.hpp"
#include "main.h"

GameMain::GameMain():gState(MainMenu),choosedLevel("levels/Level1.tmx"),lastLevel(0)
{ 
	loadData();
	loadInterface(MainMenu);
}

FILE* data;
int sc = 0, apps = 0, he = 100, coins = 0; //баллы, яблоки, здоровье, монеты

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
			Text title("Вы действительно хотите выйти из игры?",tFont,30);
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
			Text title("Об игре",tFont,30);
			title.setColor(Color::White);
			title.setStyle(Text::Bold);
			title.setPosition(wind->getSize().x/2-80,5);
			Text t("",tFont2,30);
			t.setColor(Color::Black);
			t.setStyle(Text::Regular);
			t.setPosition(50,100);
			String about;
			about = "Apple Harvest v1.0\nАвтор игры: студент ПЗ-13-1 Плахотнюк Сергей Васильевич\n\n(с) Плахотнюк С.В. 2017\n\nБлагодарности:\n-автору графической библиотеки SFML;\n-автору библиотеки TinyXML;\n-сайту kychka-pc.ru и лично Павлу Букрееву - за простые и\nпонятные уроки по SFML, а также SFML-форумчанину под ником\n\"Бек\" за исходники кода для уровней и анимации;\n-FamTrinli, пользователю YouTube - за уроки по созданию движка\nдля платформера.";
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
			Text title("Правила",tFont,30);
			title.setColor(Color::White);
			title.setStyle(Text::Bold);
			title.setPosition(wind->getSize().x/2-100,5);
			Text t("",tFont2,27);
			t.setPosition(25,50);
			t.setColor(Color::Black);
			t.setStyle(Text::Regular);
			String rules;
			rules = "Вы играете за лиса по имени Домино, который мечтает найти золотое\nяблоко.\nПрыгайте по неподвижным            и подвижным           платформам, собирайте\nяблоки     и монеты     , чтобы заработать как можно больше баллов,\n\nи уничтожайте попадающихся на пути врагов (волков       и охотников       ).\n\nКонец уровня обозначен горкой с красным флажком     .\n\nУправление - клавиши-стрелки либо клавиши W, A, D.\nЧтобы победить волка, выстрелите в него яблоком, нажав клавишу SPACE.\nЧтобы победить охотника, прыгните ему на голову.\nНе тратьте яблоки зря - так вы быстрее пройдете уровень без потери\nздоровья. Получите подсказки, нажав клавишу H, и информацию об уровне,\nнажав I.\n\nВнимание!\nИзбегайте препятствий (воды          и веток          ) и не контактируйте с\nврагами - это отнимает здоровье. Чтобы его восстанавливать,\nподбирайте жареных цыплят       .";
			t.setString(rules);

			Texture* rul_tex = new Texture[10]; //вывод на экран образцов платформ, врагов и т.д.
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
			Text title("Настройки управления и режима игры",tFont,30);
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
				drawText("    Внимание! Автосохранение отключено.\nПри необходимости сохраняйте игру вручную.",Vector2f(910,440),wind);
			break;
		}
	case ChooseLevel:
		{
			Text title("Выберите уровень",tFont,30);
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
			if(ButtonList.getClick()==11) //щелчок на кнопке "Загрузить последнюю игру"
			{
				//загрузить значение переменной уровня из файла, а также баллов, здоровья, кол-ва яблок, монет
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
				else //если файл с данными не найден, то загружаем значения по умолчанию
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
				drawText("Поздравляем! Вы прошли уровень!",Vector2f(500,200),wind);
			}
			else
			{
				drawText("Ура! Вы прошли все уровни\n  и нашли золотое яблоко.\n  Теперь Домино счастлив!",Vector2f(980,30),wind);
				int _coins = coins, _apps = apps, _sc = sc;
				std::ostringstream os1, os2, os3;
				os1<<_coins, os2<<_apps, os3<<_sc;
				drawText("Ваши результаты:",Vector2f(520,200),wind);
				String str = "Яблок:  "+os2.str()+"\nМонет:  "+os1.str()+"\n\nИтого:  "+os3.str()+" баллов";
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
			case 1: //кнопка "След. уровень"
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
			drawText("К сожалению, Вы проиграли!",Vector2f(500,200),wind);
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
		ButtonList.addButton(FloatRect(0,0,250,75),Buttons::left,Buttons::top,"Об игре",3,true);
		ButtonList.addButton(FloatRect(0,0,300,75),Buttons::centerX,Buttons::top,"Настройки",4,true);
		ButtonList.addButton(FloatRect(0,0,250,75),Buttons::right,Buttons::top,"Правила",5,true);
		ButtonList.addButton(FloatRect(0,420,200,75),Buttons::centerX,Buttons::noneY,"Играть",0,true);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"Выход",2,true);
		break;
	case ExitYesNo:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(288,300,200,50),Buttons::noneX,Buttons::noneY,"Да",0,true);
		ButtonList.addButton(FloatRect(536,300,200,50),Buttons::noneX,Buttons::noneY,"Нет",1,true);
		break;
	case ChooseLevel:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"Назад",0,true);
		ButtonList.addButton(FloatRect(240,180,200,50),Buttons::noneX,Buttons::noneY,"Уровень 1",1,true);
		ButtonList.addButton(FloatRect(240,250,200,50),Buttons::noneX,Buttons::noneY,"Уровень 2",2,true);
		ButtonList.addButton(FloatRect(240,320,200,50),Buttons::noneX,Buttons::noneY,"Уровень 3",3,true);
		ButtonList.addButton(FloatRect(240,390,200,50),Buttons::noneX,Buttons::noneY,"Уровень 4",4,true);
		ButtonList.addButton(FloatRect(240,460,200,50),Buttons::noneX,Buttons::noneY,"Уровень 5",5,true);
		ButtonList.addButton(FloatRect(580,180,200,50),Buttons::noneX,Buttons::noneY,"Уровень 6",6,true);
		ButtonList.addButton(FloatRect(580,250,200,50),Buttons::noneX,Buttons::noneY,"Уровень 7",7,true);
		ButtonList.addButton(FloatRect(580,320,200,50),Buttons::noneX,Buttons::noneY,"Уровень 8",8,true);
		ButtonList.addButton(FloatRect(580,390,200,50),Buttons::noneX,Buttons::noneY,"Уровень 9",9,true);
		ButtonList.addButton(FloatRect(580,460,200,50),Buttons::noneX,Buttons::noneY,"Уровень 10",10,true);
		ButtonList.addButton(FloatRect(290,90,440,50),Buttons::noneX,Buttons::noneY,"Загрузить последнюю игру",11,true);
		break;
	case About:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"Назад",0,true);
		break;
	case Control:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"Назад",0,true);
		
		if(getFullScreenMode())
			ButtonList.addButton(FloatRect(0,230,470,50),Buttons::centerX,Buttons::top,"Экран: полный",1,true);
		else
			ButtonList.addButton(FloatRect(0,230,470,50),Buttons::centerX,Buttons::top,"Экран: оконный режим",1,true);
		if(getWASDcontrol())
			ButtonList.addButton(FloatRect(0,290,470,50),Buttons::centerX,Buttons::top,"Управление: WASD",2,true);
		else
			ButtonList.addButton(FloatRect(0,290,470,50),Buttons::centerX,Buttons::top,"Управление: традиционное",2,true);
		if(getAutoSave())
			ButtonList.addButton(FloatRect(0,350,470,50),Buttons::centerX,Buttons::top,"Автосохранение: вкл",3,true);
		else
			ButtonList.addButton(FloatRect(0,350,470,50),Buttons::centerX,Buttons::top,"Автосохранение: откл",3,true);
		break;
	case Rules:
		bgTexture.loadFromFile("img/empty.png");
		background.setTexture(bgTexture);
		ButtonList.addButton(FloatRect(0,0,200,50),Buttons::right,Buttons::bottom,"Назад",0,true);
		break;
	case Game:
		ButtonList.addButton(FloatRect(0,-38,300,50),Buttons::centerX,Buttons::centerY,"Продолжить",0,true);
		ButtonList.addButton(FloatRect(0,38,300,50),Buttons::centerX,Buttons::centerY,"Начать сначала",3,true);
		if(!getAutoSave())
			ButtonList.addButton(FloatRect(0,114,300,50),Buttons::centerX,Buttons::centerY,"Сохранить игру",2,true);
		else
			ButtonList.addButton(FloatRect(0,114,300,50),Buttons::centerX,Buttons::centerY,"Сохранить игру",2,false);
		ButtonList.addButton(FloatRect(0,190,300,50),Buttons::centerX,Buttons::centerY,"Главное меню",1,true);
		break;
	case GameWin:
		
		if(lastLevel!=10) //если не дошли до последнего (10) уровня
		{
			ButtonList.addButton(FloatRect(0,20,300,50),Buttons::centerX,Buttons::centerY,"Выбор уровня",0,true);
			ButtonList.addButton(FloatRect(0,90,300,50),Buttons::centerX,Buttons::centerY,"След. уровень",1,true); //идем на следующий
			ButtonList.addButton(FloatRect(0,160,300,50),Buttons::centerX,Buttons::centerY,"Главное меню",2,true);
		}
		else
			{
				ButtonList.addButton(FloatRect(0,120,300,50),Buttons::centerX,Buttons::centerY,"Выбор уровня",0,true);
				ButtonList.addButton(FloatRect(0,190,300,50),Buttons::centerX,Buttons::centerY,"Главное меню",2,true);
			}
		break;
	case GameLose:
		ButtonList.addButton(FloatRect(0,45,300,50),Buttons::centerX,Buttons::centerY,"Выбор уровня",0,true);
		ButtonList.addButton(FloatRect(0,115,300,50),Buttons::centerX,Buttons::centerY,"Главное меню",1,true);
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
