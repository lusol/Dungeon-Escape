#include "view.h"
#include <string>

using namespace std;

//constructor
View::View(int rowSize, int colSize, char race){
    this->colSize = colSize;
    this->rowSize = rowSize;

    grid = new char*[rowSize];

    //intialize an array of chars for each row
    for (int i = 0; i < rowSize; i++){
        grid[i] = new char[colSize];
    }

    //loop through rows
    for (int i = 0; i < rowSize; i++){
        //loop through columsn and set each element to 0
        for (int j = 0; j < colSize; j++){
            grid[i][j] = '0';
        }
    }

    hp = 0;
    gold = 0;
    atk = 0;
    def = 0;
    floor = 0;

    //set race based on input
    switch (race){
    case 's':
        this->race = "Shade";
        break;
    case 'd':
        this->race = "Drow";
        break;
    case 'v':
        this->race = "Vampire";
        break;
    case 'g':
        this->race = "Goblin";
        break;
    case 't':
        this->race = "Troll";
        break;
    default:
        this->race = "Shade";
        break;
    }
    action = "Player has spawned.";
}

//destructor
View::~View(){
    //destroy every array in every row
    for (int i = 0; i < rowSize; i++){
        delete[] grid[i];
    }
    //destroy every row
    delete[] grid;
}

//set element at row col to ch
void View::updateCell(int row, int col, char ch){
    grid[row][col] = ch;
}

//print out entire map
void View::printout(){
    //loop through rows
    for (int i = 0; i < rowSize; i++){
        //loop throuhg columns and print element
        for (int j = 0; j < colSize; j++){
            cout<<grid[i][j];
        }
        cout << endl;
    }
    cout << "Race: " << race;
    cout << " Gold: " << gold;
    cout << "\t\t\t\t\t\t";
    cout << "Floor " << floor << endl;
    cout << "HP: " << hp << endl;
    cout << "Atk: " << atk << endl;
    cout << "Def: " << def << endl;
    cout << "Action: " << action << endl;
    cout << "Command: ";

    action = "";
}

//update player status
void View::updateStatus(int hp, int gold, int atk, int def, int floor){
    this->hp = hp;
    this->gold = gold;
    this->atk = atk;
    this->def = def;
    this->floor = floor + 1;
}

//update action output
void View::updateAction(string s){
    action += " " + s; 
}
