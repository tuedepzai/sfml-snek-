// sfml.cpp : Defines the entry point for the application.
//

#include "sfml.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "vector"
#include <chrono>
#include <ctime>
#include <thread>
#include <random>
using namespace std;

const int WIDTH = 800, HEIGHT = 600, OFFSET = 50;

void drawingGrid(sf::RenderWindow& window) {
	int x_start = 0, y_start = 0, x_end = WIDTH, y_end = 0;

	//int horizontal_lines = WIDTH / OFFSET, vertical_lines = HEIGHT / OFFSET;
	int horizontal_lines = 100, vertical_lines = 100;

	while (horizontal_lines-- > 0) {

		sf::Vertex vertices[] = {
			sf::Vertex(sf::Vector2f(x_start, y_start), sf::Color::White),
			sf::Vertex(sf::Vector2f(x_end, y_end), sf::Color::White)
		};
		y_start += OFFSET;
		y_end += OFFSET;

		window.draw(vertices, 2, sf::Lines);
		
	}
	x_start = 0, y_start = 0, x_end = 0, y_end = HEIGHT;

	while (vertical_lines-- > 0) {
		sf::Vertex vertices[] = {
			sf::Vertex(sf::Vector2f(x_start, y_start), sf::Color::White),
			sf::Vertex(sf::Vector2f(x_end, y_end), sf::Color::White)
		};
		x_start += OFFSET;
		x_end += OFFSET;

		window.draw(vertices, 2, sf::Lines);
	}
}

class treat {
public:
	sf::RectangleShape sf_treat;
	sf::Vector2f pos;

	treat(sf::Vector2f size, sf::Color color) {
		sf_treat.setSize(size);
		sf_treat.setFillColor(color);
		randomize_position();
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sf_treat);
	}

	void randomize_position() {
		int max_x = WIDTH / OFFSET;
		int max_y = HEIGHT / OFFSET;
		pos.x = (rand() % max_x) * OFFSET;
		pos.y = (rand() % max_y) * OFFSET;
		sf_treat.setPosition(pos);
	}
};

class snek {
public:
	sf::RectangleShape sf_snek;
	sf::Vector2f pos;
	sf::Vector2f dir;
	snek(sf::Vector2f pos, sf::Vector2f size, sf::Color color) {
		this->pos = pos;
		sf_snek.setPosition(pos);
		sf_snek.setSize(size);
		sf_snek.setFillColor(color);
		dir.x = 0;
		dir.y = 0;
	}

	void draw(sf::RenderWindow &window) {
		window.draw(sf_snek);
	}

	void move_though_direction() {
		sf::Vector2f speed(OFFSET * dir.x, OFFSET * dir.y);
		sf_snek.setPosition(sf_snek.getPosition() + speed);
		std::cout << " moving" << speed.x << " " << speed.y << '\n';
	}


	void up() {
		if (dir.y == 1) return;

		dir.x = 0;

		dir.y = -1;
	}

	void down() {
		if (dir.y == -1) return;
		dir.x = 0;
		dir.y = 1;
	}

	void left() {
		if (dir.x == 1) return;
	
		dir.y = 0;

		dir.x = -1;
	}

	void right() {
		if (dir.x == -1) return;
	
		dir.y = 0;
		dir.x = 1;
	}


};



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "untiled window");

	float x = WIDTH / 2, y = HEIGHT / 2;

	snek snake(sf::Vector2f(x, y), sf::Vector2f(50.0f, 50.0f), sf::Color::Cyan);





	sf::Clock clock;
	float elapsedSeconds = 0.0f;
	float treat_elapse = 0.0f;
	bool up_press = false;

	while (window.isOpen()) {
		sf::Time deltaTime = clock.restart();
		treat_elapse += deltaTime.asSeconds();
		elapsedSeconds += deltaTime.asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up)
					snake.up();
				if (event.key.code == sf::Keyboard::Down)
					snake.down();
				if (event.key.code == sf::Keyboard::Left)
					snake.left();
				if (event.key.code == sf::Keyboard::Right)
					snake.right();
			}
		}

		window.clear();
	
		drawingGrid(window);
		snake.draw(window);

	
	if (elapsedSeconds >= 0.6f) {
            snake.move_though_direction(); 
            elapsedSeconds = 0.0f; 
      }

	if (treat_elapse>= 0.6f) {
		snake.move_though_direction();
		elapsedSeconds = 0.0f;
	}

		window.display();
	}

	return 0;
}
