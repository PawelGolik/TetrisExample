#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	VideoMode vm(1920,1080);
	RenderWindow window(vm, "test");
	Event ev;
	while (window.isOpen())
	{
		window.pollEvent(ev);
		if (Event::Closed == ev.type) {
			window.close();
		}
	}
	return 0;
}