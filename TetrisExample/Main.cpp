#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <vector>
#include <chrono>

#define CUBE_SIZE 8
#define WIDTH 1000
#define HEIGHT 600

using namespace sf;

auto randF = [](int min_val, int max_val){
			std::mt19937_64 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
			return std::uniform_int_distribution<int>(min_val,max_val)(gen);
		};

enum MOVMENT
{
	LEFT, RIGHT, ROTATE_LEFT, ROTATE_RIGHT, DO_NOTHING
};

enum PIECE
{
	LONG = 0, CUBE = 1, TLIKE = 3, SLIKE = 4, RANDOM = 5
};

std::vector<Sprite> ReturnPiece(PIECE piece,Texture &tiles) {
	std::vector<Sprite> outputVector;
	int row = randF(0,9) * CUBE_SIZE;
	int col = randF(0,3) * CUBE_SIZE;
	for (size_t i = 0; i < 4; i++)
	{
		Sprite cube;
		cube.setTexture(tiles);
		cube.setTextureRect({ col,row,CUBE_SIZE,CUBE_SIZE });
		cube.setPosition(WIDTH / 2, HEIGHT / 2);
		outputVector.push_back(cube);
	}
	if (piece == PIECE::RANDOM) {
		piece = PIECE(randF(0,3));
	}
	switch (piece)
	{
	case PIECE::CUBE:
		outputVector[0].setOrigin(CUBE_SIZE,CUBE_SIZE);
		outputVector[1].setOrigin(0, CUBE_SIZE);
		outputVector[2].setOrigin(CUBE_SIZE, 0);
		outputVector[3].setOrigin(0, 0);
		break;
	case PIECE::LONG:
		outputVector[0].setOrigin(4, 16);
		outputVector[1].setOrigin(4, CUBE_SIZE);
		outputVector[2].setOrigin(4, 0);
		outputVector[3].setOrigin(4, -CUBE_SIZE);
		break;
	case PIECE::SLIKE:
		outputVector[0].setOrigin(12, CUBE_SIZE);
		outputVector[1].setOrigin(4, CUBE_SIZE);
		outputVector[2].setOrigin(4, 0);
		outputVector[3].setOrigin(-4, 0);
		break;
	case PIECE::TLIKE:
		outputVector[0].setOrigin(4,4);
		outputVector[1].setOrigin(12, 4);
		outputVector[2].setOrigin(-4, 4);
		outputVector[3].setOrigin(4,-4);
		break;
	default:
		break;
	}
	return outputVector;
}

void Movement(MOVMENT move, std::vector<Sprite> &draw) {
	float rotate = 0;
	float slide = 0;
	switch (move)
	{
	case LEFT:
		slide = -8;
		break;
	case RIGHT:
		slide = 8;
		break;
	case ROTATE_LEFT:
		rotate = -90;
		break;
	case ROTATE_RIGHT:
		rotate = 90;
		break;
	case DO_NOTHING:
		break;
	default:
		break;
	}
	for (auto &piece : draw) {
		piece.move(Vector2f(slide, 8));
		piece.rotate(rotate);
	}
}

int main() {

	int row = randF(0,9) * 8;
	int col = randF(0,3) * 8;
	VideoMode vm(WIDTH, HEIGHT);
	Texture texture;
	texture.loadFromFile("Tails.png");
	std::vector<std::pair<std::vector<Sprite>, bool>> Draw;
	Sprite cube;
	cube.setTexture(texture);
	cube.setTextureRect(IntRect(col, row, 8, 8));
	cube.setPosition(WIDTH / 2, HEIGHT / 2);
	Draw.push_back({ReturnPiece(PIECE::RANDOM, texture), true});
	RenderWindow window(vm, "Tetris");
	View view;
	view.setSize(Vector2f(500, 500));
	view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2));
	window.setView(view);
	Event ev;
	Clock clock;
	MOVMENT move = DO_NOTHING;
	clock.restart();
	float Framerate,timer = 0;
	while (window.isOpen())
	{
		Framerate = 1/ clock.getElapsedTime().asSeconds();
		timer += clock.getElapsedTime().asSeconds();
		clock.restart();
		window.clear(Color::Black);
		window.pollEvent(ev);
		if (Event::Closed == ev.type) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
			move = LEFT;
		}
		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
			move = ROTATE_RIGHT;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
			move = RIGHT;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
			move = ROTATE_LEFT;
		}
		if (1 <= timer) {
			for (auto &vec : Draw) {
				if (vec.second) {
					Movement(move, vec.first);
					move = MOVMENT::DO_NOTHING;
				}
			}
			timer=0;
		}
		for (auto &vec : Draw) {

			for (auto &piece : vec.first)
			{
				window.draw(piece);
			}
		}
		window.display();
	}
	return 0;
}