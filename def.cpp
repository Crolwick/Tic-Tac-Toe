#include "header.h"

using namespace sf;

// Private Functions

void Game::initVariables()
{
	this->window = nullptr;
	this->game = nullptr;
	this->line = nullptr;
	this->spot = nullptr;
	this->moves = 0;
	this->isMoving = 1;
	this->isWin = false;
	this->run = true;
	this->result = 0;
	size = 5;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->board[i][j] = 0;
		}
	}

	if (!this->crossT.loadFromFile("Resources/cross.png"))
	{
		std::cout << "Error!" << std::endl;
	}

	if (!this->circleT.loadFromFile("Resources/circle.png"))
	{
		std::cout << "Error!" << std::endl;
	}

	if (!this->font.loadFromFile("Resources/font2.ttf"))
	{
		std::cout << "Error!" << std::endl;
	}

	if (!this->bgT.loadFromFile("Resources/background.jpg"))
	{
		std::cout << "Error!" << std::endl;
	}
}

void Game::initWindow()
{
	this->vidMode.height = 850;
	this->vidMode.width = 711;

	this->window = new RenderWindow(this->vidMode, "Tic-Tac-Toe", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(144);
}

void Game::initGameStart()
{
	this->line = new RectangleShape[size];
	this->crossS = new Sprite[10];
	this->circleS = new Sprite[10];
	this->spot = new RectangleShape[10];

	// Cross
	for (int i = 0; i < 10; i++)
	{
		this->crossS[i].setTexture(crossT);
		this->crossS[i].setColor(Color::Transparent);
		this->crossS[i].setScale(1.6f, 1.6f);
	}

	for (int i = 0; i < 10; i++)
	{
		this->circleS[i].setTexture(circleT);
		this->circleS[i].setColor(Color::Transparent);
		this->circleS[i].setScale(1.6f, 1.6f);
	}

	// Lines Index 0 - 2 / Actual 1 - 3
	for (int i = 0; i < 2; i++)
	{
		float dx = 80.0f;
		float dy = 220.0f * (i + 1);
		this->line[i].setPosition(dx, dy);
		this->line[i].setSize(Vector2f(540.0f, 5.0f));
		this->line[i].setOutlineThickness(5.0f);
		this->line[i].setOutlineColor(Color::White);
	}
	
	// Line Index 3 / Actual 4
	this->line[3].setRotation(90);
	this->line[3].setPosition(242.5f, 60.0f);
	this->line[3].setSize(Vector2f(540.0f, 5.0f));
	this->line[3].setOutlineThickness(5.0f);
	this->line[3].setOutlineColor(Color::White);

	// Line Index 4 / Actual 5
	this->line[4].setRotation(90);
	this->line[4].setPosition(460.5f, 60.0f);
	this->line[4].setSize(Vector2f(540.0f, 5.0f));
	this->line[4].setOutlineThickness(5.0f);
	this->line[4].setOutlineColor(Color::White);

	// Spots Avaliable
	for (int i = 0; i < 3; i++)
	{
		float dx = 46.6f + (i * 220);
		float dy = 30.0f;
		this->spot[i].setFillColor(Color(0, 255, 0, 150));
		this->spot[i].setSize(Vector2f(165.0f, 165.0f));
		this->spot[i].setOutlineThickness(5.0f);
		this->spot[i].setOutlineColor(Color::Black);
		this->spot[i].setPosition(Vector2f(dx, dy));
	}

	for (int i = 3; i < 6; i++)
	{
		float dx = 46.6f + ((i - 3) * 220);
		float dy = 250.0f;
		this->spot[i].setFillColor(Color(0, 255, 0, 150));
		this->spot[i].setSize(Vector2f(165.0f, 165.0f));
		this->spot[i].setOutlineThickness(5.0f);
		this->spot[i].setOutlineColor(Color::Black);
		this->spot[i].setPosition(Vector2f(dx, dy));
	}

	for (int i = 6; i < 10; i++)
	{
		float dx = 46.6f + ((i - 6) * 220);
		float dy = 470.0f;
		this->spot[i].setFillColor(Color(0, 255, 0, 150));
		this->spot[i].setSize(Vector2f(165.0f, 165.0f));
		this->spot[i].setOutlineThickness(5.0f);
		this->spot[i].setOutlineColor(Color::Black);
		this->spot[i].setPosition(Vector2f(dx, dy));
	}
}

// Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initGameStart();
}

Game::~Game()
{
	delete this->window;
	delete this->game;
	delete [] this->line;
	delete [] this->spot;
	delete [] this->crossS;
	delete [] this->circleS;
}

// Accessors

const bool Game::running() const
{
	if (run == true)
	{
		return this->window->isOpen();
	}
	if (run == false)
	{
		return this->game->isOpen();
	}
}

// Functions
void Game::pollEvents()
{
	// Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
		{
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			if (this->ev.key.code == Keyboard::U)
				std::cout << "Mouse pos: " << Mouse::getPosition(*this->window).x << " " << Mouse::getPosition(*this->window).y << "\n";
		}
		break;
		case Event::MouseButtonPressed:
		{
			if (this->ev.key.code == Mouse::Left)
			{
				if (this->play.getGlobalBounds().contains(this->window->mapPixelToCoords(Mouse::getPosition(*this->window))))
				{
					this->window->close();
					this->game = new RenderWindow(this->vidMode, "Game", Style::Titlebar | Style::Close);
					this->game->setFramerateLimit(144);
					run = false;
				}
			}
		}
		break;
		}
	}
}

void Game::gamePollEvents()
{

	while (this->game->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->game->close();
			break;
		case Event::KeyPressed:
		{
			if (this->ev.key.code == Keyboard::Escape)
				this->game->close();
			if (this->ev.key.code == Keyboard::U)
				std::cout << "Mouse pos: " << Mouse::getPosition(*this->game).x << " " << Mouse::getPosition(*this->game).y << "\n";
		}
		break;
		}
	}

}

void Game::updateMousePositions()
{
	/*
		@ return void

		Updates mouse positions:
		- Mouse position relative to window (Vector2i)
		- Mouse position relative to view (Vector2f)
	*/

	if (run == true)
	{
		this->mousePosWindow = Mouse::getPosition(*this->window);
		this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	}
	else
	{
		this->mousePosWindow = Mouse::getPosition(*this->game);
		this->mousePosView = this->game->mapPixelToCoords(this->mousePosWindow);
	}

}

/*

	Updates Main Menu States

*/
void Game::updateMainMenu()
{
	/*
		
		@ return void

		Updates Main Menu:
		- Background
		- Title
		- Play Button
		- Quit Button

	*/

	// Background
	this->bgS.setTexture(bgT);
	this->bgS.setColor(Color(200, 200, 200, 215));
	this->bgS.setScale(Vector2f(1.2f, 1.4f));

	// Title
	this->title.setPosition(Vector2f(130.0f, 60.0f));
	this->title.setFont(font);
	this->title.setString("Tic-Tac-Toe");
	this->title.setCharacterSize(90);
	this->title.setFillColor(Color::Yellow);
	this->title.setStyle(Text::Bold | Text::Underlined);
	this->title.setOutlineThickness(5);
	this->title.setOutlineColor(Color(100, 100, 100, 200));

	// Play
	this->play.setPosition(Vector2f(283.0f, 318.75f));
	this->play.setFont(font);
	this->play.setString("Play");
	this->play.setCharacterSize(69);
	this->play.setFillColor(Color::Yellow);
	this->play.setStyle(Text::Bold | Text::Underlined);
	this->play.setOutlineThickness(5);
	this->play.setOutlineColor(Color(100, 100, 100, 200));

	// Ouit Game
	this->quit.setPosition(Vector2f(290.0f, 425.0f));
	this->quit.setFont(font);
	this->quit.setString("Quit");
	this->quit.setCharacterSize(69);
	this->quit.setFillColor(Color::Yellow);
	this->quit.setStyle(Text::Bold | Text::Underlined);
	this->quit.setOutlineThickness(5);
	this->quit.setOutlineColor(Color(100, 100, 100, 200));
}

/*

	Updates board states as game goes on

*/
void Game::updateBoard()
{
	if (this->moves >= 5)
	{
		this->checkWin();
	}
	for (int i = 0; i < 10; i++)
	{
		if (isWin == true)
		{
			break;
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->spot[i].getGlobalBounds().contains(this->game->mapPixelToCoords(Mouse::getPosition(*this->game))))
			{
				this->spot[i].setFillColor(Color::Transparent);
				moves++;
				if (moves == 0 || moves == 2 || moves == 4 || moves == 6 || moves == 8)
				{
					isMoving = 1;
				}
				else
				{
					isMoving = 2;
				}
				if (isMoving == 1)
				{
					this->crossS[i].setPosition(this->spot[i].getPosition().x, this->spot[i].getPosition().y);
					this->crossS[i].setColor(Color::Red);
					if (i % 3 == 0)
					{
						this->x = 0;
					}
					if (i % 3 == 2)
					{
						this->x = 2;
					}
					if (i % 3 == 1)
					{
						this->x = 1;
					}
					if (i == 6 || i == 7 || i == 8)
					{
						this->y = 2;
					}
					if (i == 3 || i == 4 || i == 5)
					{
						this->y = 1;
					}
					if (i == 0 || i == 1 || i == 2)
					{
						this->y = 0;
					}
					if (board[y][x] == 0)
					{
						board[y][x] = 1;
					}
				}
				else
				{
					this->circleS[i].setPosition(this->spot[i].getPosition().x, this->spot[i].getPosition().y);
					this->circleS[i].setColor(Color::Blue);
					if (i % 3 == 0)
					{
						this->x = 0;
					}
					if (i % 3 == 2)
					{
						this->x = 2;
					}
					if (i % 3 == 1)
					{
						this->x = 1;
					}
					if (i == 6 || i == 7 || i == 8)
					{
						this->y = 2;
					}
					if (i == 3 || i == 4 || i == 5)
					{
						this->y = 1;
					}
					if (i == 0 || i == 1 || i == 2)
					{
						this->y = 0;
					}
					if (board[y][x] == 0)
					{
						board[y][x] = 2;
					}
				}
				this->spot[i].setPosition(Vector2f(-100.0f, -100.0f));
				break;
			}
		}
	}

	// Turn
	switch (this->moves)
	{
	case 0:
			this->moveCount = "Turn One";
			break;
	case 1:
		this->moveCount = "Turn Two";
			break;
	case 2:
		this->moveCount = "Turn Three";
		break;
	case 3:
		this->moveCount = "Turn Four";
		break;
	case 4:
		this->moveCount = "Turn Five";
		break;
	case 5:
		this->moveCount = "Turn Six";
		break;
	case 6:
		this->moveCount = "Turn Seven";
		break;
	case 7:
		this->moveCount = "Turn Eight";
		break;
	case 8:
		this->moveCount = "Turn Nine";
		break;
	}
	this->turn.setPosition(Vector2f(80.0f, 650.0f));
	this->turn.setFont(font);
	this->turn.setString(moveCount);
	this->turn.setCharacterSize(50);
	this->turn.setFillColor(Color::Yellow);
	this->turn.setStyle(Text::Bold | Text::Underlined);
	this->turn.setOutlineThickness(5);
	this->turn.setOutlineColor(Color(100, 100, 100, 200));
}

void Game::checkWin()
{
	// Checks rows and columns for win
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			result = board[i][0];
			isWin = true;
			break;
		}
		if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			result = board[0][i];
			isWin = true;
			break;
		}
	}

	// Checks diagonals for win
	if (board[1][1] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		result = board[1][1];
		isWin = true;
	}

	if (board[1][1] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
		result = board[1][1];
		isWin = true;
	}

	// Win Message
	if (this->isWin == true)
	{
		if (result == 1)
		{
				this->winner.setPosition(Vector2f(80.0f, 740.0f));
				this->winner.setFont(font);
				this->winner.setString("Cross Wins!");
				this->winner.setCharacterSize(50);
				this->winner.setFillColor(Color::Yellow);
				this->winner.setStyle(Text::Bold | Text::Underlined);
				this->winner.setOutlineThickness(5);
				this->winner.setOutlineColor(Color(100, 100, 100, 200));
			
		}
		if (result == 2)
		{
			this->winner.setPosition(Vector2f(80.0f, 740.0f));
			this->winner.setFont(font);
			this->winner.setString("Circle Wins!");
			this->winner.setCharacterSize(50);
			this->winner.setFillColor(Color::Yellow);
			this->winner.setStyle(Text::Bold | Text::Underlined);
			this->winner.setOutlineThickness(5);
			this->winner.setOutlineColor(Color(100, 100, 100, 200));
		}
	}
	if (moves == 9 && this->isWin != true)
	{
		this->winner.setPosition(Vector2f(80.0f, 740.0f));
		this->winner.setFont(font);
		this->winner.setString("Draw!");
		this->winner.setCharacterSize(50);
		this->winner.setFillColor(Color::Yellow);
		this->winner.setStyle(Text::Bold | Text::Underlined);
		this->winner.setOutlineThickness(5);
		this->winner.setOutlineColor(Color(100, 100, 100, 200));
	}
}

/*
	
	Renders Main Menu

*/
void Game::renderMainMenu()
{
	this->window->draw(bgS);
	this->window->draw(title);
	this->window->draw(play);
	this->window->draw(quit);

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->play.getGlobalBounds().contains(this->window->mapPixelToCoords(Mouse::getPosition(*this->window))))
		{
			this->window->clear();
		}
	}

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->quit.getGlobalBounds().contains(this->window->mapPixelToCoords(Mouse::getPosition(*this->window))))
		{
			this->window->close();
		}
	}

}

/*
	@ return void

	Renders Board

*/
void Game::renderBoard()
{
	this->game->draw(turn);
	this->game->draw(winner);
	// Board / Avaliable Spots
	for (int i = 0; i < 3; i++)
	{
		this->game->draw(line[i]);
		this->game->draw(spot[i]);
	}
	for (int i = 3; i < 5; i++)
	{
		this->game->draw(line[i]);
		this->game->draw(spot[i]);
		this->game->draw(spot[5]);
	}
	for (int i = 6; i < 10; i++)
	{
		this->game->draw(spot[i]);
	}

	// Cross / Circle
	for (int i = 0; i < 10; i++)
	{
		this->game->draw(crossS[i]);
		this->game->draw(circleS[i]);
	}
}

/*
	@ return void

	Updates all code

*/
void Game::update()
{
	if (run == true)
	{
		this->pollEvents();

		this->updateMousePositions();

		this->updateMainMenu();
	}

	if (run == false)
	{
		this->gamePollEvents();
		this->updateMousePositions();
		this->updateBoard();
	}

}

void Game::render()
{
	/*
		@ return void

		- Clears
		- Renders
		- Displays

		Renders the game objects.
	*/

	// Draw //
	
	// Main Menu
	if (run == true)
	{
		this->window->clear();
		this->renderMainMenu();
		this->window->display();
	}

	// Game Board
	if (run == false)
	{
		this->game->clear();
		this->renderBoard();
		this->game->display();
	}

	// Display //


}
