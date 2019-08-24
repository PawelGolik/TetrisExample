#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>

#define WIDTH 1920
#define HEIGHT 1080


using namespace sf;

int main() {

	std::srand(NULL);
	int row = (rand() % 9)*8;
	std::srand(NULL);
	int col = (rand() % 3)*8;
	VideoMode vm(1920,1080);
	Texture texture;
	texture.loadFromFile("Tails.png");
	Sprite cube;
	cube.setTexture(texture);
	cube.setTextureRect(IntRect(col, row, 8, 8));
	cube.setPosition(WIDTH/2,HEIGHT/2);
	RenderWindow window(vm, "Tetris");
	View view;
	view.setSize(Vector2f(500, 500));
	view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2));
	window.setView(view);
	Event ev;
	Clock clock;
	clock.restart();
	float Framerate,timer = 0;
	while (window.isOpen())
	{
		Framerate = 1/ clock.getElapsedTime().asSeconds();
		timer += clock.getElapsedTime().asSeconds();
		std::cout << timer << std::endl;
		clock.restart();
		window.clear(Color::Black);
		window.pollEvent(ev);
		if (Event::Closed == ev.type) {
			window.close();
		}
		if (1 <= timer) {
			cube.move(Vector2f(0, 8));
			std::cout << "MOVED" << std::endl;
			timer=0;
		}
		window.draw(cube);
		window.display();
	}
	return 0;
}