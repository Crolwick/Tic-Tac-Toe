#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#ifndef HEADER_H
#define HEADER_H
#define CROSS 1
#define CIRCLE 2

using namespace sf;

/*
	Class that acts as the game engine.
	Wrapper Class.
*/

class Game
{
private:
	/*
	* 
		Variables

	*/

	// Window
	RenderWindow *window;
	RenderWindow *game;
	VideoMode vidMode;
	Event ev;

	// Mouse Positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	// Game Logic

	// Game Objects
	RectangleShape *line;
	RectangleShape *spot;
	Texture bgT;
	Sprite bgS;
	Texture crossT;
	Texture circleT;
	Sprite *crossS;
	Sprite *circleS;

	// Other Variables
	int size;
	int moves;
	int isMoving;
	int x, y;
	bool isWin;

	// Game Text
	Font font;
	Text play;
	Text quit;
	Text title;
	Text turn;
	Text current;
	Text winner;
	std::string moveCount;

	// Private Functions
	void initVariables();
	void initWindow();
	void initGameStart();

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;
	bool run;
	int board[3][3];
	int result;

	// Functions
	void pollEvents();
	void gamePollEvents();
	void updateMousePositions();
	void updateMainMenu();
	void updateBoard();
	void checkWin();
	void update();
	void renderMainMenu();
	void renderBoard();
	void render();


protected:


};

#endif
