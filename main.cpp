#include <SFML/Graphics.hpp>
#include <iostream>
#include "buttons.h"

using namespace std;

int main()
{
	// Create window
	sf::RenderWindow window;
	window.create(sf::VideoMode(600, 800), "Test", sf::Style::Titlebar | sf::Style::Close); // Unresizable window with titlebar
	window.setFramerateLimit(60);
	/// window.setVerticalSyncEnabled(true); // Switch animation might not work if this is used

	// Create elements
	Button btn1;
	btn1.setLabel("Import"); // Has to run before button is creaated
	btn1.Create();
	btn1.setPosition(300.f - (btn1.width() + 10), 100.f);
	Button btn2;
	btn2.setLabel("Export"); // Has to run before button is creaated
	btn2.Create();
	btn2.setPosition(300.f + 10, 100.f);
	/// btn1.setPosition(20.f, 780.f - btn1.height()); // Bottom left
	Switch switch1;
	switch1.Create();
	switch1.setPosition(20.f, 20.f);

	// Main loop
	while (window.isOpen())
	{
		// Take event
		sf::Event event;
		// Loop to handle event
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { // When close button is pressed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // When mouse button 1 is pressed
				// Handle elements
				if (btn1.isPressed() == true) {}
				if (btn2.isPressed() == true) {}
				if (switch1.isPressed() == true) {}

				cout << "Event: Mouse Button Pressed" << endl;
				cout << "X: " << event.mouseButton.x << "\t";
				cout << "Y: " << event.mouseButton.y << endl;
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { // When mouse button 1 is released
				// Handle elements
				if (btn1.isPressed(2) == true) {
					// Code executed when this button has been pressed
				}
				if (btn2.isPressed(2) == true) {
					// Code executed when this button has been pressed
				}
				if (switch1.isPressed(2) == true) {}

				cout << "Event: Mouse Button Released" << endl;
				cout << "X: " << event.mouseButton.x << "\t";
				cout << "Y: " << event.mouseButton.y << endl;
			}
			if (event.type == sf::Event::MouseMoved) { // When mouse is moved
				// Handle elements
				if (btn1.withinBounds(event.mouseMove.x, event.mouseMove.y) == true) {}
				if (btn2.withinBounds(event.mouseMove.x, event.mouseMove.y) == true) {}
				if (switch1.withinBounds(event.mouseMove.x, event.mouseMove.y) == true) {}
			}

		}

		// Draw everything
		window.clear(sf::Color::White);
		window.draw(btn1.Sprite);
		window.draw(btn1.Label);
		window.draw(btn2.Sprite);
		window.draw(btn2.Label);
		switch1.animate(); // Has to run before switch is drawn
		window.draw(switch1.Outline);
		window.draw(switch1.Circle);
		window.draw(switch1.Label);
		window.display();
	}

	return 0;
}

