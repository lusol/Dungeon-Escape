#include "controller.h"
#include <fstream>

using namespace std;

//constructor when user has a map input
Controller::Controller(string filename){
	fileName = filename;
	game = NULL;
  view = NULL;
  ifs = NULL;
  quit = false;
  skip = false;
}

//default constructor used
Controller::Controller(){
  fileName = "";
  game = NULL;
  view = NULL;
  ifs = NULL;
  quit = false;
  skip = false;
}


//calls view function to update cell in view
void Controller::updateCell(int row, int col, char ch){
	view->updateCell(row, col, ch);	
}

void Controller::init(){ 
  if (fileName != "") cout << "Loaded map " << fileName << endl;

  cout << "Select your race: ";
  char c;
  cin >> c;
  
  view = new View(ROWS, COLS, c);
  if (fileName != "") { //initalizes game either with or without a file
  	this->ifs = new ifstream(fileName.c_str());
    game = new Game(ifs, c, this);
  }
  else game = new Game(c, this);
}

//displays different messages based on status of the game;
//offers player chance to play again
void Controller::gameOver(bool won, int gold){
  //tells you whether you won or lost and whether you
  //would like to play the game again
  while (1){
    if (won) cout << "You won!";
    else cout << "You Lose!";

    cout << endl << "Your score was " << gold << "." << endl;
    cout << "Play Again?(y/n) ";

    string output;
    cin >> output;
    if (output == "y"){
      delete game;
      delete view;
      delete ifs;
      init();
      return;
    } else if (output == "n") {
      quit = true;
      return;
    }
  }
}

//starts the game and responds based on user input
void Controller::play(){  
  init();
  

	while(1){ //main command loop
    string s;
    if (!quit){
        view->printout();
        cin >> s;
    }

    //if user wants to quit the game
    if (s == "q" || quit || cin.eof()){
      break;
    } else if (s == "r"){
    	delete game;
      delete view;
      delete ifs;
      init();
    } else if (s == "p"){
    	view->printout();
    }
    //input for player turn
    else {
    	game->playerTurn(s);
      if (skip) skip = false;
      else game->enemyTurn();
    }
  }

  if (game != NULL) delete game;
  if (view != NULL) delete view;
  if (ifs != NULL) delete ifs;
}

//updates view's status
void Controller::updateStatus(int hp, int gold, int atk, int def, int floor){
  view->updateStatus(hp, gold, atk, def, floor);
}

//updates view's action output
void Controller::updateAction(std::string s){
  view->updateAction(s);
}

//set skip to true
void Controller::skipEnemyTurn(){
  skip = true;
}

//destructor
Controller::~Controller(){}
