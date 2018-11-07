#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include<conio.h>
#include <math.h>

using namespace sf;
using namespace std;

class paddle
{
public:
	// Texture tex_pad;

	RectangleShape pad;
	paddle(Vector2f position, Vector2f size, Texture tex_pad)
	{
		pad.setPosition(position);
		pad.setSize(size);
		pad.setTexture(&tex_pad);
	}


};


