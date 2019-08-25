#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>

#define WIDTH 1000
#define HEIGHT 600

using namespace sf;

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
	std::srand(10);
	int row = (rand() % 9) * 8;
	std::srand(10000);
	int col = (rand() % 3) * 8;
	for (size_t i = 0; i < 4; i++)
	{
		Sprite cube;
		cube.setTexture(tiles);
		cube.setTextureRect({ col,row,8,8 });
		cube.setPosition(WIDTH / 2, HEIGHT / 2);
		outputVector.push_back(cube);
	}
	if (piece == PIECE::RANDOM) {
		piece = PIECE(rand() % 3);
	}
	switch (piece)
	{
	case PIECE::CUBE:
		outputVector[0].setOrigin(8,8);
		outputVector[1].setOrigin(0, 8);
		outputVector[2].setOrigin(8, 0);
		outputVector[3].setOrigin(0, 0);
		break;
	case PIECE::LONG:
		outputVector[0].setOrigin(4, 16);
		outputVector[1].setOrigin(4, 8);
		outputVector[2].setOrigin(4, 0);
		outputVector[3].setOrigin(4, -8);
		break;
	case PIECE::SLIKE:
		outputVector[0].setOrigin(12, 8);
		outputVector[1].setOrigin(4, 8);
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

	std::srand(NULL);
	int row = (rand() % 9) * 8;
	std::srand(NULL);
	int col = (rand() % 3) * 8;
	VideoMode vm(WIDTH, HEIGHT);
	Texture texture;
	texture.loadFromFile("Tails.png");
	std::vector<std::pair<std::vector<Sprite>, bool>> Draw;
	Sprite cube;
	cube.setTexture(texture);
	cube.setTextureRect(IntRect(col, row, 8, 8));
	cube.setPosition(WIDTH / 2, HEIGHT / 2);
	Draw.push_back({ReturnPiece(PIECE::CUBE, texture), true});
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