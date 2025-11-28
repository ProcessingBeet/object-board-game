#include "Board.h"
#include <Square.h>
#include <iostream>
#include <Dice.h>
#include <Player.h>

using namespace std;
using std::vector;  //

/////////////////////////////////////////////ESTABILISHING OF TYPE BOARD///////////////////////////////////////////////////////////////////////////

Board::Board(){
    numberOfPlayers = 0;
    sizeOfTheBoard = 0;
    gameEnds = false;
    cout << "An empty board has arrived." << endl;
}

/*
Board::~Board(){
    for(auto square : Map)
        delete square;
    for(auto player : Players)
        delete player;
    for(auto winner : Winners)
        delete winner;

}
*/

void Board::giveInsight(Player* player){
    int whereYouStand = findSquareOnMap(player->giveStandingSquare());
    char whatYouSee[6];
    int indexIterator = whereYouStand;
    for(int i=0;i<6;i++){
        indexIterator = (indexIterator+1)%sizeOfTheBoard;
        whatYouSee[i] = Map[indexIterator]->getLook();
    }
    player->setSquareInsight(whatYouSee);
}

void Board::checkGiveInsight(){                         //////////////////////////to delete///////////////////////
    giveInsight(Players[0]);
    Players[0]->debug();
}

Board::Board(int howBigTheBoard, int howManyPlayers, char* squareTypes, int* squareAttributes, std::string* squareDescriptions, char* arrayOfPlayerTypes, std::string* playerNames) : numberOfPlayers(howManyPlayers), sizeOfTheBoard(howBigTheBoard), gameEnds(false) {
    cout << "Setting up a board..." << endl;
    try {
        bool isStartOnBoard = false;
        bool isDestinationOnBoard = false;
        bool isRegenerationOnBoard = false;
        if(squareTypes[0] != 'S'){               //start should be first square
            throw std::runtime_error("First square must be StartSquare!");
        }
        else{
            Map.push_back(new StartSquare);
            isStartOnBoard = true;
        }

        for(int i=1;i<sizeOfTheBoard;i++){          //initializing and setting Squares in order.
            if(squareTypes[i] == '.'){
                Map.push_back(new PlainSquare);     //looks stupid, but it's kind of flexible
            }
            else if(squareTypes[i] == 'S'){
                cout << "Error, StartSquare placed wrong, check " << i+numberOfPlayers+3 << ". line of input." << endl; //first we have number of players. then players, then number of squares + i-th place from up.
                throw std::runtime_error("To many start squares!");
            }
            else if(squareTypes[i] == 'D'){
                Map.push_back(new DestinationSquare);
                isDestinationOnBoard = true;
            }
            else if(squareTypes[i] == 'R'){
                Map.push_back(new RegenerationSquare);
                isRegenerationOnBoard = true;
            }
            else if(squareTypes[i] == 'O'){
                Map.push_back(new WaitingSquare(squareAttributes[i]));
            }
            else if(squareTypes[i] == 'P'){
                Map.push_back(new JumpSquare(squareAttributes[i]));
                if(squareDescriptions[i] != "none")
                    Map[i]->setDescription(squareDescriptions[i]);
            }
            else{
                cout << "On " << i+1 << ". place in squareTypes is invalid type of Square: " << squareTypes[i] << " Check your input, please." << endl; //we count 1,2,3..
                Map[i] = nullptr;
            }
        }

        for(int j=0;j<numberOfPlayers;j++){                                          //initializing and setting-up Players (in order) on start.
            if(arrayOfPlayerTypes[j] == 'T'){
                Players.push_back(new TraditionalPlayer(playerNames[j], sizeOfTheBoard, numberOfPlayers));     //looks stupid, but it's kind of flexible
                Players[j]->setStandingSquare(Map[0]);
            }
            else if(arrayOfPlayerTypes[j] == 'L'){
                Players.push_back(new RandomPlayer(playerNames[j], sizeOfTheBoard, numberOfPlayers));
                Players[j]->setStandingSquare(Map[0]);
            }
            else if(arrayOfPlayerTypes[j] == 'E'){
                Players.push_back(new ExperimenterPlayer(playerNames[j], sizeOfTheBoard, numberOfPlayers));
                Players[j]->setStandingSquare(Map[0]);
            }
            else if(arrayOfPlayerTypes[j] == 'R'){
                Players.push_back(new PrudentPlayer(playerNames[j], sizeOfTheBoard, numberOfPlayers));
                Players[j]->setStandingSquare(Map[0]);
            }
            else{
                cout << "On " << j+1 << ". place in arrayOfPlayerTypes is invalid type of Player: " << arrayOfPlayerTypes[j] << " Check your input, please." << endl;
                throw std::runtime_error("Wrong player type!");
                Players.push_back(nullptr);
            }
        }




        cout << "start presence: " << isStartOnBoard << " destination presence: " << isDestinationOnBoard << " regeneration presence: " << isRegenerationOnBoard << endl;
        if(isStartOnBoard&&isDestinationOnBoard&&isRegenerationOnBoard)
            cout << "Everything's fine, have a good time playing :)" << endl;
        else{
            throw std::runtime_error("You miss some crucial squares!");
        }
    } catch (const std::exception &error) {
        std::cerr << "Board constructor error: " << error.what() << endl;
        for(Square* square : Map)                              //destructor actually
            delete square;
        for(Player* player : Players)
            delete player;
        for(Player* winner : Winners)
            delete winner;
        throw;                                                 //to terminate constructor
    }


}

/*
Board::~Board(){
    for(Square* square : Map)
        delete square;
    for(Player* player : Players)
        delete player;
    for(Player* winner : Winners)
        delete winner;
}
*/

bool Board::getGameEnds() const{
    return gameEnds;
}

int Board::getWinnersNumber() {
    return Winners.size();
}

////////////////////////////////////////////////////////////ACTUAL  METHODS//////////////////////////////////////////////////////////////////////

void Board::printBoard() const {
    cout << endl;
    cout << "The board has " << sizeOfTheBoard << " squares and looks like this: " << endl;
    for(int i=0; i<sizeOfTheBoard; i++)
        Map[i]->howDoILook();
    cout << endl << endl;
    cout << "Has " << numberOfPlayers << " players: " << endl;
    for(int j=0; j<numberOfPlayers; j++){
        Players[j]->printName();
        cout << " an ";
        Players[j]->printLook();
        cout << " type of player." << endl;
    }
    cout << endl;
}

int Board::findSquareOnMap(Square* searchedPosition) const{
    for(int i=0;i<sizeOfTheBoard;i++)
        if(searchedPosition == Map[i])
            return i;
    return -1;
}

void Board::executeRound(){
    int didTheyStop = 0;        //0 stands for not stopping, 1 for stopping, and 2 for one player finishing the game
    int playerRollResult;
    int movingIterator;
    int squareEffect;
    for(int currentPlayerIndex=0;currentPlayerIndex<numberOfPlayers;currentPlayerIndex++){ //players take turns in order

        if(Players[currentPlayerIndex]->getTurnsToWait())             //if has to wait, waits.
            Players[currentPlayerIndex]->waitTurn();

        else{
            giveInsight(Players[currentPlayerIndex]);
            playerRollResult = Players[currentPlayerIndex]->play();   //Player decides on their tactic, and chooses dice to roll, then passes result to Board.
            movingIterator = playerRollResult;

            cout << "Player ";
            Players[currentPlayerIndex]->printName();                                                        //notification about roll result
            cout << " threw " << playerRollResult << endl;
            int standingPosition = findSquareOnMap(Players[currentPlayerIndex]->giveStandingSquare());       //player gives their Square* atribiute
            cout << "Was standing on " << standingPosition+1 << ". square, and moved ";     //and we get to know where he was standing.

            while(movingIterator>0){
                standingPosition++;
                standingPosition = standingPosition%sizeOfTheBoard;
                didTheyStop = Map[standingPosition]->encounter(Players[currentPlayerIndex], playerRollResult);
                if(didTheyStop)                                                             //there are some Squares which stop player,
                    break;                                                                  //like DestinationSquare when player reaches 13. doKTOr incarnation.
                movingIterator--;
            }

            cout << "to " << standingPosition+1 << ". square." << endl;                 //end of move notification.
            Players[currentPlayerIndex]->setStandingSquare(Map[standingPosition]);      //and setting player new position

            if(didTheyStop == 2){                                       //this player stopped on destination because they have 13. incarnation of doKTOr.
                cout << "That was final move of ";
                Players[currentPlayerIndex]->printName();
                cout << " as they were 13. incarnation of doKTOr, and ended on destination square. " << endl;
                Winners.push_back(Players[currentPlayerIndex]);         //see in Square.cpp in int DestinationSquare::encounter().
                gameEnds = true;                                        //this could have been done by returning specified value of DestinationSquare::action()
            }                                                           //and make if statement for declaring a winner.



            squareEffect = Map[standingPosition]->action(Players[currentPlayerIndex]);  //performing an action of square

            if(Map[standingPosition]->getLook() == 'P'){
                standingPosition = (squareEffect+standingPosition)%sizeOfTheBoard;                          //kicking player if on JumsSquare, can extend this if for diffrent types of square.
                Players[currentPlayerIndex]->setStandingSquare(Map[standingPosition]);                      //except for waiting square since waiting square can differ
                cout << "And now their current square is " << standingPosition+1 << "." << endl;
            }

        }
    }

    cout << endl;

    for(int currentPlayerIndex=0;currentPlayerIndex<numberOfPlayers;currentPlayerIndex++){
        Players[currentPlayerIndex]->printStatus();
        cout << " and they stand on ";
        cout << findSquareOnMap(Players[currentPlayerIndex]->giveStandingSquare()) << ". square." << endl;
    }

    cout << endl;

    if(gameEnds){
        cout << "Game ends. Congrats: " << endl;
        for (Player* i: Winners){           //C++11 range-based for-loop
            i->printName();
            cout << endl;
        }
    }
}

