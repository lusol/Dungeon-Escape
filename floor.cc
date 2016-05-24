#include "floor.h"
#include "game.h"
#include "enemy.h"
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "item.h"
#include "potion.h"
#include "rhpot.h"
#include "phpot.h"
#include "bapot.h"
#include "wapot.h"
#include "bdpot.h"
#include "wdpot.h"
using namespace std;

//returns a vector of all enemys still alive
//from top right of map to bottom left
vector<Enemy *> Floor::getEnemyList(){
    vector<Enemy *> list;
    //loop through all rows
    for(int i = 0; i < rowSize; i++){
        //loop through all columns
        for( int j = 0; j < colSize; j++){
            if(grid[i][j].isEnemy()){
                list.push_back(dynamic_cast <Enemy*> (grid[i][j].getObject()));
            }   
        }
    }
    return list;
}

//updates the neighbour list of cell i j with all neighbours around it
void Floor::addNeighbours(int i, int j){
    if (i - 1 >= 0 && j - 1 >= 0) grid[i][j].addNeighbour(&grid[i - 1][j - 1]);
    if (i - 1 >= 0) grid[i][j].addNeighbour(&grid[i - 1][j]);
    if (i - 1 >= 0 && j + 1 < colSize) grid[i][j].addNeighbour(&grid[i - 1][j + 1]);
    if (j + 1 < colSize) grid[i][j].addNeighbour(&grid[i][j + 1]);
    if (i + 1 < rowSize && j + 1 < colSize) grid[i][j].addNeighbour(&grid[i + 1][j + 1]);
    if (i + 1 < rowSize) grid[i][j].addNeighbour(&grid[i + 1][j]);
    if (i + 1 < rowSize && j - 1 >= 0) grid[i][j].addNeighbour(&grid[i + 1][j - 1]);
    if (j - 1 >= 0) grid[i][j].addNeighbour(&grid[i][j - 1]);
}

//constructor if passed a file to read from
Floor::Floor(Game* game, int rowSize, int colSize, ifstream &ifs){
    this->game = game;
    this->rowSize = rowSize;
    this->colSize = colSize;

    grid = new Cell*[rowSize];

    //creates a new array of cells of size colSize at every row
    for (int i = 0; i < rowSize; i++){
        grid[i]= new Cell[colSize];
    }
    
    char ch;
    //loop through all rows
    for(int i = 0; i < rowSize; i++){
        //loop through all columns and read chars from the filestream
        //one by one and place them into a cell
        for(int j = 0; j < colSize; j++){
            ifs >> noskipws >> ch;
            if (ch == '\n') ifs >> noskipws >> ch;
            grid[i][j].init(this, i, j, ch);
            game->updateView(i, j, ch);
            addNeighbours(i, j);
        }
    }

    //loop through all rows
    for(int i = 0; i < rowSize; i++){
        //loop through all columns and read chars from the grid
        //one by one and process them.
        for(int j = 0; j < colSize; j++){
            ch = grid[i][j].getBaseType();
            if (ch != '.' && ch != ' ' && ch != '-' && ch != '|' && ch != '+' && ch != '#' && ch != '\\'){
                grid[i][j].setBaseType('.');
                if (ch == '@'){
                    grid[i][j].setObject(game->getPlayer());
                } else if (ch == 'H') {
                    grid[i][j].setObject(new Human(game));
                } else if (ch == 'W') {
                    grid[i][j].setObject(new Dwarf(game));
                } else if (ch == 'E') {
                    grid[i][j].setObject(new Elf(game));
                } else if (ch == 'O') {
                    grid[i][j].setObject(new Orc(game));
                } else if (ch == 'M') {
                    grid[i][j].setObject(new Merchant(game));
                } else if (ch == 'L') {
                    grid[i][j].setObject(new Halfling(game));
                } else if (ch == '0') {
                    grid[i][j].setObject(new RHPot(game));
                } else if (ch == '1') {
                    grid[i][j].setObject(new BAPot(game));
                } else if (ch == '2') {
                    grid[i][j].setObject(new BDPot(game));
                } else if (ch == '3') {
                    grid[i][j].setObject(new PHPot(game));
                } else if (ch == '4') {
                    grid[i][j].setObject(new WAPot(game));
                } else if (ch == '5') {
                    grid[i][j].setObject(new WDPot(game));
                } else if (ch == '6') {
                    grid[i][j].setObject(new Treasure(game, 2));
                } else if (ch == '7') {
                    grid[i][j].setObject(new Treasure(game, 1));
                } else if (ch == '8') {
                    grid[i][j].setObject(new Treasure(game, 4));
                } else if (ch == '9') {
                    DragonTreasure* dragonTreasure = new DragonTreasure(game, 4);
                    grid[i][j].setObject(dragonTreasure);
                    for (int k = 0; k < 8 ; k++){
                        Cell* cell = grid[i][j].getNeighbours()[k];
                        if (cell->getBaseType() == 'D'){
                            cell->setBaseType('.');
                            cell->setObject(new Dragon(game, dragonTreasure));
                        }
                    }
                }
            }   
        }
    }    
}


//default constructor
Floor::Floor(Game* game, int rowSize, int colSize){
	this->game = game;
    this->rowSize = rowSize;
    this->colSize = colSize;

    ifstream ifs(MAPFILE.c_str());

    grid = new Cell*[rowSize];
    
    //creates an array of cells at every row
    for (int i = 0; i < rowSize; i++){
        grid[i]= new Cell[colSize];
    }
    
    char ch;

    //loop through all rows
    for(int i = 0; i < rowSize; i++){
        //loop through column and initialize cell at i j
        //with a char read from the file
        for(int j = 0; j < colSize; j++){
            ifs >> noskipws >> ch;
            if (ch == '\n') ifs >> noskipws >> ch;
            grid[i][j].init(this, i, j, ch);
            game->updateView(i, j, ch);
            addNeighbours(i, j);
        }
    }

    //loop through all rows
    for (int i = 0; i < rowSize; i++){
        //loops through all columns
    	for (int j = 0; j < colSize; j++){
    		if (grid[i][j].getBaseType() == '.'){
                //initialize all 5 chambers
            	for (int k = 0; k < 5; k++){
            		if (chambers[k].isMember(&grid[i][j])) {
            			break;
            		} else if (chambers[k].isEmpty()) {
            			chambers[k].setCells(&grid[i][j]);
            			break;
            		}
            	}
            }
    	}
    }
}

//calls game update view with row col and ch parameters
void Floor::updateView(int row, int col, char ch){
	game->updateView(row, col, ch);
}

//return list of chambers
Chamber* Floor::getChambers(){
	return chambers;
}

//destructor
Floor::~Floor(){
    for (int i = 0; i < rowSize; i++){
        delete[] grid[i];
    }
    delete[] grid;
}
