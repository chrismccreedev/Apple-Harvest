#pragma once
#include "main.h"

class ButtonsBase
{
protected:
	struct ButtonNode
	{
		Vector2f position;
		String title;
		int index;
		bool isHover;
		bool isActive;
	};
	vector<ButtonNode> btnList; //������ ������
	Font btnFont; //����� ������ ��� ��������
	Text btnTitle;//��������� ������ ��� ��������
	Sprite btnSprite;//������ ������
	Texture btnTexture;//�������� ������
	int clickedBtn;//������ ������� ������ (�� ��������� -1)
	bool isButtonHold[2];//������������ ������� ����� ������� ���� (�� ������, ������, ������)

	void loadBaseData();//�������� ������� ������
	void checkMouse();//�������� ����� ������ ���� � ��������� ������� ������
	void drawText(unsigned int i_num,Vector2f btnPos,RenderWindow *i_wind);//����� ������ ��� �������
public:
	int getClick();//�������� ������� ������
	virtual void update(RenderWindow *i_wind) = 0;//���������� ������
	virtual void draw(RenderWindow *i_wind) = 0;//����� ������ �� �����
	ButtonsBase(void);
	virtual ~ButtonsBase(void);
};

