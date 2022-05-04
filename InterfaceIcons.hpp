#ifndef _INTERFACEICONS_H_
#define _INTERFACEICONS_H_

#include <SFML\Graphics.hpp>
#include <sstream>

using namespace sf;

class InterfaceIcon
{
private:
	int x, y, w, h;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Text data;
	InterfaceIcon(String filename, int x, int y, int w, int h, int numericData)
	{
		image.loadFromFile(filename);
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		std::ostringstream dataString;
		dataString<<numericData;
		data.setString(dataString.str());

		data.setColor(Color::White);
		data.setStyle(Text::Bold);
		data.setPosition(sprite.getPosition().x+20, sprite.getPosition().y);
	}
	void DrawIcon(RenderWindow &win)
	{
		Vector2f center = win.getView().getCenter();
		Vector2f size = win.getView().getSize();
		sprite.setPosition(center.x - size.x/2 + x, center.y - size.y/2 + y);
		win.draw(sprite);
	}
	void update(int dataToUpdate)
	{
		if(dataToUpdate>0)
		{
			std::ostringstream upd;
			upd<<dataToUpdate;
			data.setString(upd.str());
		}
	}
};
#endif