#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //эта строка убирает консоль при работе игры
#include "main.h"
#include "GameMain.h"
#include <Windows.h>

enum Controls //перечислимый тип, описывает управление игрой (возможные действия)
{
	up,
	down,
	left,
	right,
	shoot
};

Uint32 windowWidth = 1024; //ширина окна
Uint32 windowHeight = 600; //высота окна
bool FullScreenMode[2]; //режим полного экрана (по умолчанию он оконный)

bool WASDcontrol; //переключение режима стрелочного управления и WASD

bool AutoSave; //режим автосохранения

Keyboard::Key HotKeys[5]; //массив, описывающий "горячие клавиши" - клавиши управления и стрельбы

void updateHotKeys() //функция, задающая клавиши управления
{
	if(WASDcontrol)
	{
		HotKeys[Controls::up]=Keyboard::W;
		HotKeys[Controls::down]=Keyboard::S;
		HotKeys[Controls::left]=Keyboard::A;
		HotKeys[Controls::right]=Keyboard::D;
	}
	else
	{
		HotKeys[Controls::up]=Keyboard::Up;
		HotKeys[Controls::down]=Keyboard::Down;
		HotKeys[Controls::left]=Keyboard::Left;
		HotKeys[Controls::right]=Keyboard::Right;
	}
	HotKeys[Controls::shoot]=Keyboard::Space;
}

Keyboard::Key getHotKey(Controls arg)
{
	return HotKeys[arg];
}

bool getWASDcontrol()
{
	return WASDcontrol;
}
void setWASDcontrol(bool arg) //функция установки режима управления
{
	WASDcontrol = arg;
	updateHotKeys();
}

bool getAutoSave()
{
	return AutoSave;
}

void setAutoSave(bool arg)
{
	AutoSave = arg;
}

void setFullScreenMode(bool arg) //функция установки полного экрана
{
	FullScreenMode[0] = arg;
}
bool getFullScreenMode()
{
	return FullScreenMode[0];
}

void drawText(String i_text,Vector2f Pos,RenderWindow *i_wind) //вывод текста
{
	Font SystemFont;
	SystemFont.loadFromFile("etc/EuropeB.otf");
	Text btnTitle(i_text,SystemFont,30);
	btnTitle.setStyle(Text::Regular);
	//формировка текста
	btnTitle.setString(i_text);
	btnTitle.setOrigin(Vector2f(9*i_text.getSize(),20));
	btnTitle.setPosition(Pos.x+3,Pos.y+3);
	btnTitle.setColor(Color::Black);
	i_wind->draw(btnTitle);
	//вывод текста
	btnTitle.setPosition(Pos.x,Pos.y);
	btnTitle.setColor(Color::White);
	i_wind->draw(btnTitle);
}

void drawText(String i_text,Vector2f coords,Font i_font,Text text,RenderWindow *i_wind)
{
	//формировка текста
	text.setString(i_text);
	text.setOrigin(Vector2f(9*i_text.getSize(),20));
	text.setPosition(coords.x+3,coords.y+3);
	text.setColor(Color::Black);
	i_wind->draw(text);
	//вывод текста
	text.setPosition(coords.x,coords.y);
	text.setColor(Color::White);
	i_wind->draw(text);
}

bool fileExists(const char* path)
{
	return std::ifstream(path); //возвращаем поток условия (если файл существует, true, иначе false)
}

bool checkFilesExistence()
{
	if(!fileExists("anims/wolf.xml")||!fileExists("anims/hunter.xml")||!fileExists("anims/fox.xml")
	||!fileExists("etc/rul_apple.png")||!fileExists("etc/rul_bran.png")||!fileExists("etc/rul_chic.png")
	||!fileExists("etc/rul_coin.png")||!fileExists("etc/rul_end.png")||!fileExists("etc/rul_hunt.png")
	||!fileExists("etc/rul_mPlat.png")||!fileExists("etc/rul_sPlat.png")||!fileExists("etc/rul_water.png")
	||!fileExists("etc/rul_wolf.png")||!fileExists("etc/EuropeB.otf")||!fileExists("etc/EuropeN.ttf")
	||!fileExists("img/apple.png")||!fileExists("img/apple_icon.png")||!fileExists("img/apple_shot.png")
	||!fileExists("img/bg.png")||!fileExists("img/chicken.png")||!fileExists("img/coin.png")
	||!fileExists("img/coin_icon.png")||!fileExists("img/empty.png")||!fileExists("img/fox.png")
	||!fileExists("img/green-btn-200x50.png")||!fileExists("img/health_icon.png")||!fileExists("img/hunter.png")
	||!fileExists("img/inactive-btn-200x50.png")||!fileExists("img/left.png")||!fileExists("img/logo.png")
	||!fileExists("img/movingPlatform.png")||!fileExists("img/right.png")||!fileExists("img/score.png")
	||!fileExists("img/screensaver.png")||!fileExists("img/up.png")||!fileExists("img/wolf.png")
	||!fileExists("img/yellow-btn-200x50.png")||!fileExists("levels/tilemap.png")||!fileExists("levels/Level1.tmx")
	||!fileExists("levels/Level2.tmx")||!fileExists("levels/Level3.tmx")||!fileExists("levels/Level4.tmx")
	||!fileExists("levels/Level5.tmx")||!fileExists("levels/Level6.tmx")||!fileExists("levels/Level7.tmx")
	||!fileExists("levels/Level8.tmx")||!fileExists("levels/Level9.tmx")||!fileExists("levels/Level10.tmx"))
		return false;
	return true;
}

int main()
{
	if(!checkFilesExistence())
	{
		MessageBox(NULL, (LPCSTR)"Не удалось запустить игру. Отсутствуют необходимые папки и/или файлы.", (LPCSTR)"Apple Harvest", MB_ICONERROR | MB_OK);
		return 0;
	}
	GameMain gameObj; //объект "Игра"
	FILE* set; //файл с настройками игры
	if((set = fopen("settings.ini","rb"))!=NULL)
	{
		fscanf(set,"%*s %d %*s %d %*s %d",&FullScreenMode[0],&WASDcontrol,&AutoSave); //чтение настроек из файла
		FullScreenMode[1] = false;
	}
	else
	{
		MessageBox(NULL, (LPCSTR)"Добро пожаловать! Применены настройки игры по умолчанию:\nЭкран: оконный\nУправление: клавиши-стрелки\nАвтосохранение: включено", (LPCSTR)"Apple Harvest", MB_ICONASTERISK | MB_OK);
		FullScreenMode[0] = false;
		FullScreenMode[1] = false;
		WASDcontrol = false;
		AutoSave = true;
	}
	RenderWindow window;
	if(!getFullScreenMode())
	{
		window.create(VideoMode(windowWidth,windowHeight),"Apple Harvest",Style::Close); //создали окно игры,
		//режим Close, т.е. оконный
	}
	else
		{
			window.create(VideoMode(windowWidth,windowHeight),"Apple Harvest",Style::Fullscreen);
		}
	Clock gameTimer; //таймер, отсчитывающий игровое время
	updateHotKeys(); //устанавливаем клавиши управления
	bool wind_active = true; //активно окно игры или нет
	while(window.isOpen()) //пока открыто окно
	{
		Event event; //событие, происходящее с окном
		while(window.pollEvent(event))
		{
			if(event.type==Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) //если событие "Закрыть" либо клавиша Esc,
			{
				//спрашиваем, хочет ли пользователь действительно выйти
				gameObj.getBtnList().removeAllButtons();
				gameObj.loadInterface(ExitYesNo);
				gameObj.setState(ExitYesNo);
			}
			if(event.type == sf::Event::GainedFocus) //если событие "Сфокусировать окно"
			{
				wind_active = true; //делаем окно активным
			}
			if(event.type == sf::Event::LostFocus) //если событие "Расфокусировать окно"
			{
				wind_active = false; //то наоборот
			}
		}
		if(FullScreenMode[0]!=FullScreenMode[1])
		{
			FullScreenMode[1] = FullScreenMode[0];
			window.close();
			if(FullScreenMode[1])
				window.create(VideoMode(windowWidth,windowHeight),"Apple Harvest",Style::Fullscreen); //разворачиваем на полный экран
			else
			{
				window.create(VideoMode(windowWidth,windowHeight),"Apple Harvest",Style::Close); //иначе делаем оконный режим
				//window.setIcon(16,16,game_icon.pixel_data);
			}
		}
		float time = gameTimer.getElapsedTime().asMilliseconds(); //запись значения таймера в переменную,
		//она нужна для вычислений всех событий игры (движения объектов, изменения направления после столкновений, итд)
		time = time/600;
		gameTimer.restart(); //таймер необходимо все время перезапускать
		if((!wind_active)||(time>0.5)) //если окно неактивно, либо проходит слишком много времени, то мы идем на следующую итерацию цикла
			continue;	//"пока открыто окно"
		window.setView(View(FloatRect(0, 0, windowWidth, windowHeight))); //устанавливаем игровую "камеру" в окне с левого верхнего угла
		gameObj.update(&window,time);
		//обновляем объект "Игра", передав ему ссылку на окно, файл данных и время
		window.display(); //отрисовываем окно заново
		window.clear(); //очистили окно
	}

	set = fopen("settings.ini", "wb");
	fprintf(set, "fullscreen= %d wasd= %d autosave= %d", FullScreenMode[0], WASDcontrol, AutoSave); //автоматическое сохранение настроек игры
	fclose(set);

	return 0;
}