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

class Ball
{
public:
	
	// Texture tex_pad;

	RectangleShape ball;
	Ball(Vector2f position, Vector2f size)
	{
		ball.setPosition(position);
		ball.setSize(size);
		//ball.setTexture(&tex_pad);
	}

	void setTexure(Texture*tex_ball_1) {
		ball.setTexture(tex_ball_1);

	}

};
