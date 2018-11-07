
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
#include "Paddle.h"
#include "Ball.h"



using namespace sf;
using namespace std;

void update_state(float dt);
void render_frame();

RenderWindow window;
RectangleShape shape;
RectangleShape backGround;
//RectangleShape pad1;
//RectangleShape pad2;
//RectangleShape ball;

Texture tex_pad;
Texture tex_ball;
Texture tex_bg;

SoundBuffer buf_hit;
Sound hit;

Font font;

Text text;
Text text1;

int pad2_vel = 0;
int pad1_score = 0;
int pad2_score = 0;

Vector2f vel(-200, 100);

paddle p1(paddle(Vector2f(0, 200), Vector2f(5, 128), Texture(tex_pad)));

paddle p2(paddle(Vector2f(797, 200), Vector2f(5, 128), Texture(tex_pad)));
Ball b (Ball (Vector2f(350, 200), Vector2f(10, 10)));

int main()
{
	window.create (VideoMode(800, 600), "Pong!");

	
	//tex.loadFromFile()

	/*CircleShape shape(100.f);
	shape.setFillColor(Color::Green);*/
	//shape.setTexture(&tex);

	buf_hit.loadFromFile("Data/hit.wav");
	hit.setBuffer(buf_hit);

	font.loadFromFile("Data/comic.ttf");

	tex_pad.loadFromFile("Data/Pad1.png");

	
	tex_ball.loadFromFile("Data/Ball.png");
	Texture * tex_ball_1 = &tex_ball;
	b.ball.setTexture(tex_ball_1);


	tex_bg.loadFromFile("Data/sky.jpg");

	p1.pad.setTexture(&tex_pad);
	
	//background
	backGround.setSize(Vector2f(800, 600));
	backGround.setPosition(0, 0);
	backGround.setTexture(&tex_bg);

	//paddle p1(paddle(Vector2f(30, 200), Vector2f(41, 128), Texture(tex_pad)));
	//pad1
	
	/*pad1.size(Vector2f(41, 128));
	pad1.setPosition(30, 200);
	pad1.setTexture(&tex_pad);*/

	// pad2
	//pad2.setSize(Vector2f(41, 128));
	//pad2.setPosition(729, 200);
	//pad2.setTexture(&tex_pad);

	//ball
	//ball.setSize(Vector2f(50, 50));
	//ball.setPosition(400, 200);
	//ball.setTexture(&tex_ball);

	text.setFont(font);
	text.setCharacterSize(100);

	text.setFillColor(Color::White);
	text.setPosition(150, 250);


	text1.setFont(font);
	text1.setCharacterSize(100);

	text1.setFillColor(Color::White);
	text1.setPosition(150, 250);

	Clock clock;

	void update_state(float dt);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();


		update_state(dt);
		render_frame();
		window.display();
	}

	return 0;
}



bool contains_point(FloatRect r, Vector2f p)
{
	return p.x >= r.left &&
		p.x < r.left + r.width &&
		p.y >= r.top &&
		p.y < r.top + r.height;

}


void update_state(float dt)
{

	bool is_ball_out = false;

	//pad2
	if (b.ball.getPosition().y < p2.pad.getPosition().y)
	{
		pad2_vel = -150;
	}
	if (b.ball.getPosition().y > p2.pad.getPosition().y)
	{
		pad2_vel = 150 ;
	}


	//ball
	Vector2f ball_pos = b.ball.getPosition();
    ball_pos += vel * dt;
	
	//b.ball.move(vel.x*dt, vel.y*dt);

	
	

	Vector2f ball_pos_1 (b.ball.getPosition().x+10 , b.ball.getPosition().y);
	Vector2f ball_pos_2(b.ball.getPosition().x + 10, b.ball.getPosition().y+10);
	Vector2f ball_pos_3(b.ball.getPosition().x, b.ball.getPosition().y + 10);

	Vector2f pad_pos_1 (0, p1.pad.getPosition().y+64);
	Vector2f pad_pos = p1.pad.getPosition();
	Vector2f pad2_pos = p2.pad.getPosition();

	b.ball.setPosition(ball_pos);

	FloatRect paddle1;
	paddle1.left = pad_pos.x;
	paddle1.top = pad_pos.y;
	paddle1.width = p1.pad.getSize().x;
	paddle1.height = p1.pad.getSize().y;

	FloatRect paddle2;
	paddle2.left = pad2_pos.x;
	paddle2.top = pad2_pos.y;
	paddle2.width = p2.pad.getSize().x;
	paddle2.height = p2.pad.getSize().y;


	//if (b.ball.getPosition().x < 2 || b.ball.getPosition().x + 10 < 11)
	//{
	//	pad2_score++;
	//		b.ball.setPosition(350, 200);
	//	
	//	float x = vel.x;
	//	float y = vel.y;
	//	float ref1 = x * x + y * y;

	//	vel.x = sqrt(ref1 / 2);
	//	vel.y = sqrt(ref1 / 2);
	//
	//}
	//else if (b.ball.getPosition().x > 788 || b.ball.getPosition().x + 10 > 798)
	//{
	//	pad1_score++;
	//	b.ball.setPosition(350, 200);

	//	float x = vel.x;
	//	float y = vel.y;
	//	float ref1 = x * x + y * y;

	//	vel.x = -sqrt(ref1 / 2);
	//	vel.y = sqrt(ref1 / 2);
	//}


	//pad1 if (b.ball.getGlobalBounds().intersects(p1.pad.getGlobalBounds()) == true ) 
	if (b.ball.getGlobalBounds().intersects(p1.pad.getGlobalBounds()) == true) {

		b.ball.setPosition(ball_pos.x + 5, ball_pos.y);


		/*if (!contains_point(paddle1, ball_pos_1) && !contains_point(paddle1, ball_pos_2)) */
		
			hit.play();
			float x = 1.05*vel.x;
			//float y1 = 1.05*vel.y;
			//vel.y = 1.05*vel.y;
			//float ref1 = x * x + y * y;

			if (ball_pos.y <= pad_pos.y + 64) {
				float hit_ratio = (pad_pos.y + 64 - ball_pos.y) / 64;
				float y1 = sqrt(vel.y*vel.y);
				float y = (0.5* y1 + hit_ratio * 180);
				vel.y = -1.05*sqrt(y*y);
				/*float ref = (ref1 - vel.y*vel.y);*/
				vel.x = sqrt(x*x);
				//pad1_move = true;

			}
			else if (ball_pos.y > pad_pos.y + 64) {
				float hit_ratio = (ball_pos.y - (pad_pos.y + 64)) / 64;
				float y1 = sqrt(vel.y*vel.y);
				float y = (0.5* y1  + hit_ratio * 180);

				vel.y = 1.05* sqrt(y*y);
				/*float ref = (ref1 - vel.y*vel.y);*/
				vel.x = sqrt(x*x);
				//pad1_move = true;
			}
		
		/*else {
			b.ball.setPosition(-15, ball_pos.y);
		}*/
	}

	//pad2 b.ball.getGlobalBounds().intersects(p2.pad.getGlobalBounds()) == true 
	//contains_point(paddle2, ball_pos_1) && !contains_point(paddle2, ball_pos) && !contains_point(paddle2, ball_pos_3)
	if (b.ball.getGlobalBounds().intersects(p2.pad.getGlobalBounds()) == true) {

		b.ball.setPosition(ball_pos.x - 5, ball_pos.y);
		
		//if (!contains_point(paddle2, ball_pos) && !contains_point(paddle2, ball_pos_3)) {
			
				hit.play();
				float x = 1.05*vel.x;
				//float y = 1.05*vel.y;
				//float ref1 = x * x + y * y;

				if (ball_pos.y <= pad2_pos.y + 64) {
					float hit_ratio = (pad2_pos.y + 64 - ball_pos.y) / 64;
					float y1 = sqrt(vel.y*vel.y);
					float y = (0.5* y1 + hit_ratio * 180);
					vel.y = -1.05*sqrt(y*y);
					vel.x = -sqrt(x*x);

				}
				else if (ball_pos.y > pad2_pos.y + 64) {
					float hit_ratio = (ball_pos.y - (pad2_pos.y + 64)) / 64;
					float y1 = sqrt(vel.y*vel.y);
					float y = (0.5*y1 + hit_ratio * 180);
					vel.y = 1.05*sqrt(y*y);
					
					vel.x = -sqrt(x*x);

				}
		
	/*	else {
			b.ball.setPosition(810, ball_pos.y);
		}*/
	} 
	
	//|| contains_point(paddle1, ball_pos_1) || contains_point(paddle1, ball_pos_2)

	if (b.ball.getPosition().x < -10) {
		pad2_score++;
		b.ball.setPosition(350, 200);
		
		float x = vel.x;
		float y = vel.y;
		float ref1 = x * x + y * y;

		vel.x = sqrt(ref1 / 2);
		vel.y = sqrt(ref1 / 2);

		
	}
	if (ball_pos.x > 800) {
		pad1_score++;
		b.ball.setPosition(350, 200);
		
		float x = vel.x;
		float y = vel.y;
		float ref1 = x * x + y * y;

		vel.x = -sqrt(ref1 / 2);
		vel.y = sqrt(ref1 / 2);
	
	}

		p2.pad.move(0, pad2_vel*dt);
	

	//pad2 test
	//if (b.ball.getGlobalBounds().intersects(p2.pad.getGlobalBounds()) == true) {
	//	hit.play();
	//		vel.x = -vel.x;	
	//}
	if (ball_pos.y +10>= window.getSize().y)
		vel.y = -vel.y;
	if (ball_pos.y <= 0)
		vel.y = -vel.y;


	// pad1
	

		if (Keyboard::isKeyPressed(Keyboard::Up))
			pad_pos.y -= 680 * dt;
		if (Keyboard::isKeyPressed(Keyboard::Down))
			pad_pos.y += 680 * dt;
	


	
	p1.pad.setPosition(pad_pos);
	// Boundary
	if (p1.pad.getPosition().y < 0)
	{
		p1.pad.setPosition(0, 0);
	}

	if (p1.pad.getPosition().y > 472)
	{
		p1.pad.setPosition(0, 472);
	}
	

	if (p2.pad.getPosition().y < 0)
	{
		p2.pad.setPosition(797, 0);
	}

	if (p2.pad.getPosition().y > 472)
	{
		p2.pad.setPosition(797, 472);
	}


	Vector2f text_pos = text.getPosition();

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		text_pos.x += 350;

	}

	text1.setPosition(text_pos);


	Vector2f text1_pos = text1.getPosition();

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		text1_pos.x += 350;

	}

	text1.setPosition(text1_pos);

}






void render_frame() {
	
	bool is_playing = true;
	bool is_ball_out = false;

	//check if ball is out
	//if (b.ball.getPosition().x < 1   )
	//{
	//	pad2_score++;
	//	is_ball_out = true;

	//		float x = vel.x;
	//		float y = vel.y;
	//		float ref1 = x * x + y * y;

	//		vel.x = sqrt(ref1 / 2);
	//		vel.y = sqrt(ref1 / 2);
	//}
	//else if (b.ball.getPosition().x > 789 )
	//{
	//	pad1_score++;
	//	is_ball_out = true;

	//	float x = vel.x;
	//	float y = vel.y;
	//	float ref1 = x * x + y * y;

	//	vel.x = -sqrt(ref1 / 2);
	//	vel.y = sqrt(ref1 / 2);
	//}


	//if (is_ball_out)
	//{
	//	window.clear();
	//	window.draw(backGround);
	//	window.draw(p1.pad);
	//	window.draw(p2.pad);
	//	b.ball.setPosition(350, 200);
	//	window.draw(b.ball);

	//}

	if (pad1_score >= 5) {

		vel.x = -180;
		vel.y = 180;


		is_playing = false;
		window.clear();
		window.draw(backGround);
		
		
		text.setString("You win!");
		window.draw(text);

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{

			pad1_score = 0;
			pad2_score = 0;
			is_playing = true;
		}
	}
	else if (pad2_score >= 5) {
		vel.x = -180;
		vel.y = 180;

		is_playing = false;

		window.clear();
		window.draw(backGround);
		//Text text1;
		/*text1.setFont(font);
		text1.setCharacterSize(100);

		text1.setFillColor(Color::White);
		text1.setPosition(150, 250);*/
		text1.setString("You lost!");
		window.draw(text1);


		//bool is_playing = false;

		if (text1.getPosition().x >= 800)
		{
			pad1_score = 0;
			pad2_score = 0;
			is_playing = true;
		}

	}


	if (is_playing) {
	
		window.clear();
		window.draw(backGround);
		window.draw(p1.pad);
		window.draw(p2.pad);
		window.draw(b.ball);
		//window.draw(shape);

		Text score;
		score.setFont(font);
		score.setCharacterSize(50);

		score.setFillColor(Color::Red);
		score.setPosition(350, 10);
		score.setString("0 : 0");

		stringstream text;
		text << pad1_score << " : " << pad2_score;
		score.setString(text.str());

		window.draw(score);
	}
	


	}


