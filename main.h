#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <cmath>

using namespace sf;
using namespace std;

enum Controls;

void drawText(String i_text,Vector2f btnPos,RenderWindow *i_wind);
void drawText(String i_text,Vector2f btnPos,Font i_font,Text btnTitle,RenderWindow *i_wind);
void setFullScreenMode(bool);
bool getFullScreenMode();
void updateHotKeys();
Keyboard::Key getHotKey(Controls);
bool getWASDcontrol();
void setWASDcontrol(bool);
bool getAutoSave();
void setAutoSave(bool);
bool fileExists(const char* path);
bool checkFilesExistence();