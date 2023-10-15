#include "Game.h"
#include <cmath>
#include <iostream>
#include <ctime>

void Game::initVariables()
{
	this->window = nullptr;

    this->N = 4;
    this->hexSize = 43.0f;

    //Game logic
    this->mouseHeld = false;
    this->selected = false;
    this->isGameEnd = false;
    this->onePlayerMode = false;
    selectedHex = nullptr;
    this->teamTurn = 0;
    this->pointsTeamOne = 3;
    this->pointsTeamTwo = 3;

}

void Game::initWindow()
{
    this->videoMode.width = 1280;
	this->videoMode.height = 720;

	this->window = new sf::RenderWindow(this->videoMode, "Hexagon game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144);
}



void Game::initGUI()
{

    if (!this->font.loadFromFile("Fonts/Rubik.ttf"))
        std::cout << "ERROR::GAME::Failed to load font" << "\n";

    this->pointTextTeamOne.setPosition(1200.f, 660.f);
    this->initText(pointTextTeamOne);

    this->pointTextTeamTwo.setPosition(1200.f, 630.f);
    this->initText(pointTextTeamTwo);


    //Init point bars
    this->pointsBarTeamOne.setSize(sf::Vector2f(20.f, 25.f));
    this->pointsBarTeamOne.setFillColor(sf::Color::Green);
    this->pointsBarTeamOne.setPosition(sf::Vector2f(1175.f, 630.f));

    this->pointsBarTeamTwo.setSize(sf::Vector2f(20.f, 25.f));
    this->pointsBarTeamTwo.setFillColor(sf::Color::Blue);
    this->pointsBarTeamTwo.setPosition(sf::Vector2f(1175.f, 660.f));

    //Game over
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setString("Game over!\nTeam one won!");
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setPosition(
            this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
            this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    //background
    if (!this->worldBackgroundTexture.loadFromFile("Textures/Background.jpg"))
    {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
    }

    this->worldBackground.setTexture(this->worldBackgroundTexture);

}

void Game::initText(sf::Text &text)
{
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
}

void Game::initHexes()
{
    for (int q = -N; q <= N; q++)
    {
        int r1 = std::max(-N, -q - N);
        int r2 = std::min(N, -q + N);
        for (int r = r1; r <= r2; r++)
        {
            Hex* hex;
            int s = -q - r;
            hex = new Hex(q, r, s);

            float xPos = window->getSize().x / 2.0f - 25.f + hexSize * 1.5f * hex->getRCord();
            float yPos = window->getSize().y / 2.0f - 30.f + hexSize * std::sqrt(3.0f) * (hex->getQCord() + hex->getRCord() * 0.5f);
            hex->setDefault();
            hex->move(xPos, yPos);
            
            if ((q == -N && r == 0 && s == N) || (q == 0 && r == N && s == -N) || (q == N && r == -N && s == 0)) {
                hex->setPiece(1);
            }
            else if ((q == -N && r == N && s == 0) || (q == 0 && r == -N && s == N) || (q == N && r == 0 && s == -N)) {
                hex->setPiece(0);
            }

            if ((q == -1 && r == 1 && s == 0) || (q == 0 && r == -1 && s == 1) || (q == 1 && r == 0 && s == -1)) {
                delete hex;
            }
            else {
                hexagons.insert(hex);
            }

        }
    }
}



//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initHexes();
    this->initGUI();

}

Game::~Game()
{
	delete this->window;

    for (auto* i : this->hexagons)
    {
        delete i;
    }

    delete selectedHex;
}




//Accessors
bool Game::running()
{
	return this->window->isOpen();
}


void Game::pollEvents()
{
    //Event polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::updateMousePosition()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateHexes()
{   
    //this->onePlayerMode
    if (onePlayerMode && teamTurn == 1) makeBestMove();

    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {   
        if (!this->mouseHeld)
        {
            mouseHeld = true;
            if (!selected) {
                
                
                selectPiece();
            }
            else {
                movePiece();
            }
 
        }
    }
    else {
        mouseHeld = false;
    }
}

Hex* Game::findHexByCords(const HexCoord& hexCoord)
{
    int q = hexCoord.getQ();
    int r = hexCoord.getR();
    int s = hexCoord.getS();
  
    for (auto &hex : hexagons) {
     
        if (hex->getQCord() == q && hex->getRCord() == r && hex->getSCord() == s) {

            return hex;
        }
    }
    return nullptr;
}

std::vector<Hex *> Game::getNeighbors(Hex *hex, int range)
{
    std::vector<Hex*> hexesInLocalRange;
    for (int q = -range; q <= range; q++)
    {
        for (int r = std::max(-range, -q - range); r <= std::min(range, -q + range); r++)
        {
            int s = -q - r;
            Hex* hexInRange = findHexByCords(HexCoord::hexAdd(*hex->hexCords, HexCoord(q, r, s)));
            if (hexInRange != nullptr) {
                hexesInLocalRange.push_back(hexInRange);
            }
        }
    }
    return hexesInLocalRange;
}


void Game::selectPiece()
{   
    for (auto& hex : hexagons) {
        if (hex->getShape().getGlobalBounds().contains(this->mousePosView) 
            && hex->isOccupied() && hex->getCurrentTeam() == this->teamTurn && this->canMove(hex)) {
            for (auto& hexNeighbor : getNeighbors(hex, 2)) {
                if (!hexNeighbor->isOccupied()) {
                    hexNeighbor->setSelected();
                }
                this->hexesInRange.push_back(hexNeighbor);
            }
            this->selectedHex = hex;
            selected = true;
        }
    }
}

void Game::movePiece()
{   
    for (auto& hex : hexesInRange) {
        if (hex->getShape().getGlobalBounds().contains(this->mousePosView) && !hex->isOccupied()) {
           int jumpDistance = HexCoord::hexDistance(*selectedHex->hexCords, *hex->hexCords);
           if (jumpDistance == 1) {
                hex->setPiece(this->teamTurn);
           }
           else {
               selectedHex->removePiece();
               hex->setPiece(this->teamTurn);
           }
           occupyNeighbors(hex);

           
           calcPoints();
           changeTeam();
           checkForGameEnd();
           break;
        }
    }
    for (auto& hex : hexagons) {
        hex->setDefault();
    }


    hexesInRange.clear();
    selected = false;
    selectedHex = nullptr;
}

void Game::occupyNeighbors(Hex* hex)
{
  
    for (auto& hexNeighbor : this->getNeighbors(hex, 1)) {
        if (hexNeighbor->isOccupied()) {
            hexNeighbor->setPieceTeam(teamTurn);
        }
    }
}

bool Game::canMove(Hex* hex)
{   
    bool hexCanMove = false;
    for (auto& hexNeighbor : getNeighbors(hex, 2)) {
        if (!hexNeighbor->isOccupied()) {
            hexCanMove = true;
        }
    }
    return hexCanMove;
}

void Game::calcPoints()
{
    resetPoints();
    for (auto& hex : hexagons) {
        if (hex->isOccupied()){
            hex->getCurrentTeam() == 0 ? this->pointsTeamOne++ : this->pointsTeamTwo++;
        }
    }
}


int Game::calcFreeHexes()
{
    int freeHexes = 0;
    for (auto& hex : hexagons)
    {
        if (!hex->isOccupied()) freeHexes++;
    }
    return freeHexes;
}

void Game::resetPoints()
{
    this->pointsTeamOne = 0;
    this->pointsTeamTwo = 0;
}

void Game::makeBestMove()
{
    //wait
    sf::sleep(sf::seconds(1.f));

    std::vector<Hex*> teamHexes = this->getTeamByColor(1);
    std::map<int, std::pair<Hex*, Hex*>> directionRate;

    for (auto& hex : teamHexes) {
        for (auto& getNeighbor : this->getNeighbors(hex, 2)) {
            int numOfPoints = 0; //rate of current neighbor
            for (auto& targetHex : this->getNeighbors(getNeighbor, 1)) { //target hexes that can be captured
                if (targetHex->isOccupied() && targetHex->getCurrentTeam() == 0) numOfPoints++;
            }
            if (!getNeighbor->isOccupied()) {
                int extraPoint = HexCoord::hexDistance(*hex->hexCords, *getNeighbor->hexCords) == 1 ? 1 : 0;
                directionRate[numOfPoints + extraPoint] = {hex, getNeighbor };
            }
        }
    }
    Hex* startHex = directionRate.rbegin()->second.first;
    Hex* endHex = directionRate.rbegin()->second.second;
    
    int jumpDistance = HexCoord::hexDistance(*startHex->hexCords, *endHex->hexCords);
    if (jumpDistance == 1) {
        endHex->setPiece(this->teamTurn);
    }
    else {
        startHex->removePiece();
        endHex->setPiece(this->teamTurn);
    }
    
    occupyNeighbors(endHex);


    calcPoints();
    changeTeam();
    checkForGameEnd();
}


void Game::checkForGameEnd()
{  
    for (size_t i = 0; i < 2; i++)
    {
        bool moveIsPossible = false;
        for (auto& hexTeamMember : getTeamByColor(i)) {
            for (auto& hex : getNeighbors(hexTeamMember, 2)) {
                if (!hex->isOccupied())
                {
                    moveIsPossible = true;
                }
            }
        }
        if (!moveIsPossible) {
            int freeHexes = calcFreeHexes();
            int leadingTeamPoints = (1 - i == 0 ? this->pointsTeamOne : this->pointsTeamTwo) + freeHexes;
            int teamPoints = leadingTeamPoints == this->pointsTeamOne ? this->pointsTeamTwo : this->pointsTeamOne;

            this->winnerTeam = leadingTeamPoints > teamPoints ? i : 1 - i;

            this->isGameEnd = true;
            return;
        }
    }
}

void Game::changeTeam()
{
    this->teamTurn = 1 - teamTurn;
}

void Game::enableSoloMode()
{
    this->onePlayerMode = true;
}



std::vector<Hex*> Game::getTeamByColor(int currentTurn)
{
    std::vector<Hex*> team;
    for (auto& hex : hexagons) {
        if (hex->isOccupied() && hex->getCurrentTeam() == currentTurn) {
            team.push_back(hex);
        }
    }
    return team;
}




void Game::updateGUI()
{
    this->pointTextTeamOne.setString(std::to_string(pointsTeamOne));
    this->pointTextTeamTwo.setString(std::to_string(pointsTeamTwo));
}



void Game::update()
{

    this->pollEvents();

    this->updateMousePosition();

    this->updateHexes();

    this->updateGUI();


}


void Game::renderGUI()
{
    this->window->draw(this->pointTextTeamOne);
    this->window->draw(this->pointTextTeamTwo);
    this->window->draw(this->pointsBarTeamOne);
    this->window->draw(this->pointsBarTeamTwo);

}

void Game::renderGameEnd()
{

    this->window->clear();
    this->window->draw(this->worldBackground);
    std::string endText = this->winnerTeam == 0 ? "GREEN TEAM WON!" : "BLUE TEAM WON!";
    this->gameOverText.setString("    GAME OVER!\n" + endText);

    this->window->draw(this->gameOverText);
}


void Game::render()
{

    this->window->clear();



    //Render background
    this->window->draw(this->worldBackground);



    //Drawing game objects
    for (auto hex : this->hexagons) {
        hex->render(*this->window);
    }


    this->renderGUI();

    //GAME OVER
    if (this->isGameEnd) {
        this->renderGameEnd();
    }

    this->window->display();
    
}


