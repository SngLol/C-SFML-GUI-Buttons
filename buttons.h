#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

// USAGE: BUTTON
/// Setup
/*
Button button;
button.setLabel("Idle");
button.hoverLabel = "Hover"; // Optional
button.clickLabel = "Click"; // Optional
button.Create();
button.setPosition(float x, float y);
*/
/// Events
/*
if (button.withinBounds(x,y) == true) {} // Use when mouse is moved. Will return true if given coordinates are within the bounds of the button
if (button.isPressed(x) == true) {} // Use when mouse button 1 is pressed (x=1), and again when it's released (x=2). Will return true if button.withinBounds(x,y) is true
*/
/// Values
/*
button.height() // Returns the height of the button sprite
button.width() // Returns the width of the button sprite
button.setState(string state) // Manually changes the button state/appearance to Idle/Hover/Click. button.isPressed() and button.withinBounds(x,y) does this automatically
*/

// USAGE: SWITCH
/// Setup
/*
Switch switch1;
switch1.Create();
switch1.setPosition(float x, float y);
*/
/// Events
/*
if (switch1.withinBounds(x,y) == true) {} // Use when mouse is moved. Will return true if given coordinates are within the bounds of the switch
if (switch1.isPressed(x) == true) {} // Use when mouse button 1 is pressed (x=1), and again when it's released (x=2). Will return true if switch1.withinBounds(x,y) is true
*/
/// Values
/*
switch1.height() // Returns the height of the button sprite
switch1.width() // Returns the width of the button sprite
switch1.setState(int state) // Manually changes the switch state/appearance to 1/2/3/4/5/6. switch1.isPressed() and switch1.withinBounds(x,y) does this automatically
switch1.isOn // Bool variable. Is true if the switch is on
*/

class Button {
	sf::Texture Idle;
	sf::Texture Hover;
	sf::Texture Click;
	sf::Font Font;
	float x = 0;
	float y = 0;
	float x2 = 0;
	float y2 = 0;
	int fineAdjust = 0;
public:
	sf::Sprite Sprite;
	sf::Text Label;
	bool hover = false;
	bool press = false;
	bool click = false;
	string label = "Button";
	string clickLabel = label;
	string hoverLabel = label;
	void Create() {
		Idle.loadFromFile("res/button/btn_idle.png");
		Hover.loadFromFile("res/button/btn_hover.png");
		Click.loadFromFile("res/button/btn_click.png");
		Font.loadFromFile("res/arial.ttf");
		Label.setFont(Font);
		Label.setCharacterSize(24);
		Label.setFillColor(sf::Color::Black);
		setLabel(label);
		Sprite.setTexture(Idle);
		if (Label.getLocalBounds().height <= 18) { fineAdjust = 0; }
		if (Label.getLocalBounds().height >= 23) { fineAdjust = 5; }
		Label.setOrigin(sf::Vector2f(((Sprite.getLocalBounds().width - Label.getLocalBounds().width) / 2) * (-1), ((Sprite.getLocalBounds().height - (Label.getLocalBounds().height - fineAdjust) * 1.7) / 2) * (-1)));
	}
	void setState(string type) {
		if (type == "Idle") {
			Sprite.setTexture(Idle);
		}
		else if (type == "Hover") {
			Sprite.setTexture(Hover);
		}
		else if (type == "Click") {
			Sprite.setTexture(Click);
		}
	}
	void setPosition(float newX, float newY) {
		x = newX;
		y = newY;
		x2 = newX + Sprite.getLocalBounds().width;
		y2 = newY + Sprite.getLocalBounds().height;
		Sprite.setPosition(sf::Vector2f(newX, newY));
		Label.setPosition(sf::Vector2f(newX, newY));
	}
	void setLabel(string x) {
		string oldLabel = label;
		string oldClickLabel = clickLabel;
		if (x != clickLabel && x != hoverLabel) {
			label = x;
		}
		if (clickLabel == oldLabel && x != hoverLabel) {
			clickLabel = x;
		}
		if (hoverLabel == oldLabel && x != oldClickLabel) {
			hoverLabel = x;
		}
		Label.setString(x);
		if (Label.getLocalBounds().height <= 18) { fineAdjust = 0; }
		if (Label.getLocalBounds().height >= 23) { fineAdjust = 5; }
		Label.setOrigin(sf::Vector2f(((Sprite.getLocalBounds().width - Label.getLocalBounds().width) / 2) * (-1), ((Sprite.getLocalBounds().height - (Label.getLocalBounds().height - fineAdjust) * 1.7) / 2) * (-1)));
	}
	int height() { return Sprite.getLocalBounds().height; }
	int width() { return Sprite.getLocalBounds().width; }
	bool withinBounds(int coorX, int coorY) {
		if (coorX > x && coorX < x2 && coorY > y && coorY < y2) {
			if (press != true) {
				Sprite.setTexture(Hover);
				setLabel(hoverLabel);
			}
			hover = true;
			return true;
		}
		else {
			if (press != true) {
				Sprite.setTexture(Idle);
				setLabel(label);
			}
			hover = false;
			return false;
		}
	}
	bool isPressed(int x = 1) {
		if (hover == true && press == false && x == 1) {
			Sprite.setTexture(Click);
			setLabel(clickLabel);
			press = true;
			return true;
		}
		else if (hover == true && x == 2) {
			Sprite.setTexture(Hover);
			setLabel(hoverLabel);
			press = false;
			return true;
		}
		else if (hover == false && press == true && x == 2) {
			Sprite.setTexture(Idle);
			setLabel(label);
			press = false;
			return false;
		}
		else {
			return false;
		}
	}
	void draw(sf::RenderWindow window) {
		window.draw(Sprite);
		window.draw(Label);
	}
};

class Switch {
	sf::Texture outline_type_1;
	sf::Texture outline_type_2;
	sf::Texture outline_type_3;
	sf::Texture outline_type_4;
	sf::Texture outline_type_5;
	sf::Texture circle_type_1;
	sf::Texture circle_type_2;
	sf::Texture circle_type_3;
	sf::Font Font;
	float x = 0;
	float y = 0;
	float x2 = 0;
	float y2 = 0;
	int anim = 2;
	float cPos = 0.f;
public:
	sf::Sprite Outline;
	sf::Sprite Circle;
	sf::Text Label;
	bool hover = false;
	bool press = false;
	bool isOn = false;
	int Type = 1;
	void Create() {
		outline_type_1.loadFromFile("res/switch/outline_type_1.png");
		outline_type_2.loadFromFile("res/switch/outline_type_2.png");
		outline_type_3.loadFromFile("res/switch/outline_type_3.png");
		outline_type_4.loadFromFile("res/switch/outline_type_4.png");
		outline_type_5.loadFromFile("res/switch/outline_type_5.png");
		circle_type_1.loadFromFile("res/switch/circle_type_1.png");
		circle_type_2.loadFromFile("res/switch/circle_type_2.png");
		circle_type_3.loadFromFile("res/switch/circle_type_3.png");
		Font.loadFromFile("res/arial.ttf");
		Label.setFont(Font);
		Label.setString("Off");
		Label.setCharacterSize(24);
		Label.setFillColor(sf::Color::Black);
		Outline.setTexture(outline_type_1);
		Circle.setTexture(circle_type_1);
		Circle.setOrigin(sf::Vector2f(0.f, 0.f));
		Label.setOrigin(sf::Vector2f(((Outline.getLocalBounds().width - Label.getLocalBounds().width + 50)) * (-1), ((Outline.getLocalBounds().height - Label.getLocalBounds().height * 1.7) / 2) * (-1)));
	}
	void animate() {
		if (anim == 0) {
			//Off
			if (cPos > -36.f) {
				cPos -= 6;
				Circle.setOrigin(sf::Vector2f(cPos, 0.f));
				Circle.setPosition(sf::Vector2f(x,y));
				cout << "animate: " << cPos << endl;
			}
			else {
				anim = 2;
			}
		}
		else if (anim == 1) {
			//On
			if (cPos < 0.f) {
				cPos += 6;
				Circle.setOrigin(sf::Vector2f(cPos, 0.f));
				Circle.setPosition(sf::Vector2f(x,y));
				cout << "animate: " << cPos << endl;
			}
			else {
				anim = 2;
			}
		}
	}
	void setState(int type, int pre = 0) {
		if (type == 1) {
			Outline.setTexture(outline_type_1);
			Circle.setTexture(circle_type_1);
			Label.setString("Off");
			isOn = false;
			Circle.setOrigin(sf::Vector2f(0.f, 0.f));
			Type = 1;
		}
		else if (type == 2) {
			Outline.setTexture(outline_type_2);
			Circle.setTexture(circle_type_2);
			Label.setString("Off");
			isOn = false;
			if (pre == 6) { anim = 1; }
			else {
				Circle.setOrigin(sf::Vector2f(0.f, 0.f));
			}
			Type = 2;
		}
		else if (type == 3) {
			Outline.setTexture(outline_type_3);
			Circle.setTexture(circle_type_3);
			Label.setString("Off");
			isOn = false;
			Circle.setOrigin(sf::Vector2f(0.f, 0.f));
			Type = 3;
		}
		else if (type == 4) {
			Outline.setTexture(outline_type_4);
			Circle.setTexture(circle_type_3);
			Label.setString("On");
			isOn = true;
			Circle.setOrigin(sf::Vector2f(-36.f, 0.f));
			Type = 4;
		}
		else if (type == 5) {
			Outline.setTexture(outline_type_5);
			Circle.setTexture(circle_type_3);
			Label.setString("On");
			isOn = true;
			if (pre == 3) { anim = 0; }
			else {
				Circle.setOrigin(sf::Vector2f(-36.f, 0.f));
			}
			Type = 5;
		}
		else if (type == 6) {
			Outline.setTexture(outline_type_3);
			Circle.setTexture(circle_type_3);
			Label.setString("On");
			isOn = true;
			Circle.setOrigin(sf::Vector2f(-36.f, 0.f));
			Type = 6;
		}
		Circle.setPosition(sf::Vector2f(x, y));
	}
	void setPosition(float newX, float newY) {
		x = newX;
		y = newY;
		x2 = newX + Outline.getLocalBounds().width;
		y2 = newY + Outline.getLocalBounds().height;
		Outline.setPosition(sf::Vector2f(newX, newY));
		Circle.setPosition(sf::Vector2f(newX, newY));
		Label.setPosition(sf::Vector2f(newX, newY));
	}
	void setScale(float newX, float newY) {
		Outline.setScale(sf::Vector2f(newX, newY));
		Circle.setScale(sf::Vector2f(newX, newY));
		Label.setOrigin(sf::Vector2f(((Outline.getLocalBounds().width - Label.getLocalBounds().width + 50 * newX)) * (-1), ((Outline.getLocalBounds().height - Label.getLocalBounds().height * 1.7) / 2) * (-1)));
	}
	int height() { return Outline.getLocalBounds().height; }
	int width() { return Outline.getLocalBounds().width; }
	bool withinBounds(int coorX, int coorY) {
		if (coorX > x && coorX < x2 && coorY > y && coorY < y2) {
			if (press != true) {
				if (Type == 1) {
					setState(2);
				}
				else if (Type == 4) {
					setState(5);
				}
			}
			hover = true;
			return true;
		}
		else {
			if (press != true) {
				if (Type == 2) {
					setState(1);
				}
				else if (Type == 5) {
					setState(4);
				}
			}
			hover = false;
			return false;
		}
	}
	bool isPressed(int x = 1) {
		if (hover == true && press == false && x == 1) {
			if (Type == 2) {
				setState(3);
			}
			else if (Type == 5) {
				setState(6);
			}
			press = true;
			return true;
		}
		else if (hover == true && x == 2) {
			if (Type == 3) {
				setState(5, 3);
			}
			else if (Type == 6) {
				setState(2, 6);
			}
			press = false;
			return true;
		}
		else if (hover == false && press == true && x == 2) {
			if (Type == 3) {
				setState(1);
			}
			else if (Type == 6) {
				setState(4);
			}
			press = false;
			return false;
		}
		else {
			return false;
		}
	}
};
