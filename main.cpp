#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //��� ������ ������� ������� ��� ������ ����
#include "main.h"
#include "GameMain.h"
#include <Windows.h>

enum Controls //������������ ���, ��������� ���������� ����� (��������� ��������)
{
	up,
	down,
	left,
	right,
	shoot
};

Uint32 windowWidth = 1024; //������ ����
Uint32 windowHeight = 600; //������ ����
bool FullScreenMode[2]; //����� ������� ������ (�� ��������� �� �������)

bool WASDcontrol; //������������ ������ ����������� ���������� � WASD

bool AutoSave; //����� ��������������

Keyboard::Key HotKeys[5]; //������, ����������� "������� �������" - ������� ���������� � ��������

void updateHotKeys() //�������, �������� ������� ����������
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
void setWASDcontrol(bool arg) //������� ��������� ������ ����������
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

void setFullScreenMode(bool arg) //������� ��������� ������� ������
{
	FullScreenMode[0] = arg;
}
bool getFullScreenMode()
{
	return FullScreenMode[0];
}

void drawText(String i_text,Vector2f Pos,RenderWindow *i_wind) //����� ������
{
	Font SystemFont;
	SystemFont.loadFromFile("etc/EuropeB.otf");
	Text btnTitle(i_text,SystemFont,30);
	btnTitle.setStyle(Text::Regular);
	//���������� ������
	btnTitle.setString(i_text);
	btnTitle.setOrigin(Vector2f(9*i_text.getSize(),20));
	btnTitle.setPosition(Pos.x+3,Pos.y+3);
	btnTitle.setColor(Color::Black);
	i_wind->draw(btnTitle);
	//����� ������
	btnTitle.setPosition(Pos.x,Pos.y);
	btnTitle.setColor(Color::White);
	i_wind->draw(btnTitle);
}

void drawText(String i_text,Vector2f coords,Font i_font,Text text,RenderWindow *i_wind)
{
	//���������� ������
	text.setString(i_text);
	text.setOrigin(Vector2f(9*i_text.getSize(),20));
	text.setPosition(coords.x+3,coords.y+3);
	text.setColor(Color::Black);
	i_wind->draw(text);
	//����� ������
	text.setPosition(coords.x,coords.y);
	text.setColor(Color::White);
	i_wind->draw(text);
}

bool fileExists(const char* path)
{
	return std::ifstream(path); //���������� ����� ������� (���� ���� ����������, true, ����� false)
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
		MessageBox(NULL, (LPCSTR)"�� ������� ��������� ����. ����������� ����������� ����� �/��� �����.", (LPCSTR)"Apple Harvest", MB_ICONERROR | MB_OK);
		return 0;
	}
	GameMain gameObj; //������ "����"
	FILE* set; //���� � ����������� ����
	if((set = fopen("settings.ini","rb"))!=NULL)
	{
		fscanf(set,"%*s %d %*s %d %*s %d",&FullScreenMode[0],&WASDcontrol,&AutoSave); //������ �������� �� �����
		FullScreenMode[1] = false;
	}
	else
	{
		MessageBox(NULL, (LPCSTR)"����� ����������! ��������� ��������� ���� �� ���������:\n�����: �������\n����������: �������-�������\n��������������: ��������", (LPCSTR)"Apple Harvest", MB_ICONASTERISK | MB_OK);
		FullScreenMode[0] = false;
		FullScreenMode[1] = false;
		WASDcontrol = false;
		AutoSave = true;
	}
	RenderWindow window;
	if(!getFullScreenMode())
	{
		window.create(VideoMode(windowWidth,windowHeight),"Apple Harvest",Style::Close); //������� ���� ����,
		//����� Close, �.�. �������
	}
	else
		{
			window.create(VideoMode(windowWidth,windowHeight),"Apple Harvest",Style::Fullscreen);
		}
	Clock gameTimer; //������, ������������� ������� �����
	updateHotKeys(); //������������� ������� ����������
	bool wind_active = true; //������� ���� ���� ��� ���
	while(window.isOpen()) //���� ������� ����
	{
		Event event; //�������, ������������ � �����
		while(window.pollEvent(event))
		{
			if(event.type==Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) //���� ������� "�������" ���� ������� Esc,
			{
				//����������, ����� �� ������������ ������������� �����
				gameObj.getBtnList().removeAllButtons();
				gameObj.loadInterface(ExitYesNo);
				gameObj.setState(ExitYesNo);
			}
			if(event.type == sf::Event::GainedFocus) //���� ������� "������������� ����"
			{
				wind_active = true; //������ ���� ��������
			}
			if(event.type == sf::Event::LostFocus) //���� ������� "��������������� ����"
			{
				wind_active = false; //�� ��������
			}
		}
		if(FullScreenMode[0]!=FullScreenMode[1])
		{
			FullScreenMode[1] = FullScreenMode[0];
			window.close();
			if(FullScreenMode[1])
				window.create(VideoMode(windowWidth,windowHeight),"Apple Harvest",Style::Fullscreen); //������������� �� ������ �����
			else
			{
				window.create(VideoMode(windowWidth,windowHeight),"Apple Harvest",Style::Close); //����� ������ ������� �����
				//window.setIcon(16,16,game_icon.pixel_data);
			}
		}
		float time = gameTimer.getElapsedTime().asMilliseconds(); //������ �������� ������� � ����������,
		//��� ����� ��� ���������� ���� ������� ���� (�������� ��������, ��������� ����������� ����� ������������, ���)
		time = time/600;
		gameTimer.restart(); //������ ���������� ��� ����� �������������
		if((!wind_active)||(time>0.5)) //���� ���� ���������, ���� �������� ������� ����� �������, �� �� ���� �� ��������� �������� �����
			continue;	//"���� ������� ����"
		window.setView(View(FloatRect(0, 0, windowWidth, windowHeight))); //������������� ������� "������" � ���� � ������ �������� ����
		gameObj.update(&window,time);
		//��������� ������ "����", ������� ��� ������ �� ����, ���� ������ � �����
		window.display(); //������������ ���� ������
		window.clear(); //�������� ����
	}

	set = fopen("settings.ini", "wb");
	fprintf(set, "fullscreen= %d wasd= %d autosave= %d", FullScreenMode[0], WASDcontrol, AutoSave); //�������������� ���������� �������� ����
	fclose(set);

	return 0;
}