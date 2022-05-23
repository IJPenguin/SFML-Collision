#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>

class Game {
private:
	sf::RenderWindow win;
	sf::RectangleShape rec;
	sf::RectangleShape recRun;

public:
	Game();
	void run();
	void initRect();

private:
	void processEvents();
	void update();
	void render();
};

Game::Game()
	:win(sf::VideoMode(2560, 1440), "Main Window", sf::Style::Default)
	,rec(sf::Vector2f(50, 50))
	,recRun(sf::Vector2f(50,50)) {
	win.setFramerateLimit(60);
	recRun.setFillColor(sf::Color::Red);
	recRun.setOrigin(recRun.getSize() * 0.5f);
	recRun.setPosition(1230, 720);
	recRun.setOutlineColor(sf::Color::Transparent);
	recRun.setOutlineThickness(10);
	rec.setFillColor(sf::Color::Green);
	rec.setOrigin(rec.getSize() * 0.5f);
	rec.setPosition(200, 200);
	rec.setOutlineColor(sf::Color::Transparent);
	rec.setOutlineThickness(10);
}

void Game::initRect() {

}

void Game::run() {
	while (win.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
		bool right = false;
		bool left = false;
		bool up = false;
		bool down = false;
		sf::Event ev;
		while (win.pollEvent(ev)) {
			if (ev.type == sf::Event::EventType::Closed)
				win.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				right = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				left = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				up = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				down = true;
		}
		if (right) {
			rec.move(sf::Vector2f(50, 0));
		}
		if (left) {
			rec.move(sf::Vector2f(-50, 0));
		}
		if (up) {
			rec.move(sf::Vector2f(0, -50));
		}
		if (down) {
			rec.move(sf::Vector2f(0, 50));
		}
		if (rec.getGlobalBounds().intersects(recRun.getGlobalBounds())&& right) {
			recRun.move(sf::Vector2f(50, 0));
		}
		if (rec.getGlobalBounds().intersects(recRun.getGlobalBounds()) && left) {
			recRun.move(sf::Vector2f(-50, 0));
		}
		if (rec.getGlobalBounds().intersects(recRun.getGlobalBounds()) && up) {
			recRun.move(sf::Vector2f(0, -50));
		}
		if (rec.getGlobalBounds().intersects(recRun.getGlobalBounds()) && down) {
			recRun.move(sf::Vector2f(0, 50));
		}
		if (rec.getGlobalBounds().intersects(recRun.getGlobalBounds())) {
			recRun.setPosition(win.getSize().x *0.5f, win.getSize().y * 0.5f);
		}
}

void Game::update() {
	if (rec.getPosition().x > win.getSize().x) {
		rec.setPosition(0, rec.getPosition().y);
	} //Right Side wrap
	if (rec.getPosition().y > win.getSize().y) {
		rec.setPosition(rec.getPosition().x, 0);
	} // Bottom Side wrap
	if (rec.getPosition().x < 0) {
		rec.setPosition(win.getSize().x, rec.getPosition().y);
	} // Left Side Wrap
	if (rec.getPosition().y < 0) {
		rec.setPosition(rec.getPosition().x, win.getSize().y);
	} // Top Side Wrap
	if (recRun.getPosition().x > win.getSize().x) {
		recRun.setPosition(0, recRun.getPosition().y);
	} // Right Side Wrap
	if (recRun.getPosition().y > win.getSize().y) {
		recRun.setPosition(recRun.getPosition().x, 0);
	} // Bottom Side Wrap
	if (recRun.getPosition().x < 0) {
		recRun.setPosition(win.getSize().x, rec.getPosition().y);
	} // Left Side Wrap
	if (recRun.getPosition().y < 0) {
		recRun.setPosition(recRun.getPosition().x, win.getSize().y);
	} // Top Side Wrap
}

void Game::render() {
	win.clear(sf::Color::Black);
	win.draw(rec);
	win.draw(recRun);
	win.display();
}

int main() {
	Game game;
	game.run();
	return 0;
}
