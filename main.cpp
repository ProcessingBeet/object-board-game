#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Dice.h>
#include <Square.h> //jeszcze nie skonczylem, ale już jest szkielet
#include <Board.h>
#include <Player.h>
#include <fstream>
#include <unistd.h>

using namespace std;

int main(){

    int sizeOfTheBoard; //wczytywanie pliku
    int numberOfPlayers;

    ifstream fileIn;
    fileIn.open("dane.txt");

    fileIn >> numberOfPlayers;

    char typesOfPlayers[numberOfPlayers];
    string namesOfPlayers[numberOfPlayers];

    for(int i=0;i<numberOfPlayers;i++){
        fileIn >> typesOfPlayers[i];
        getline(fileIn, namesOfPlayers[i]);
        namesOfPlayers[i] = namesOfPlayers[i].substr(1);    //troche leniwe, coz.
    }

    fileIn >> sizeOfTheBoard;

    char typeOfSquares[sizeOfTheBoard];
    string squareDescriptions[sizeOfTheBoard];
    int squareAttributes[sizeOfTheBoard];

    for(int i=0;i<sizeOfTheBoard;i++){
        fileIn >> typeOfSquares[i];
        if(typeOfSquares[i] == 'P'){                //i hate managing strings, and input from myself, but now i can shove as much spaces and tabs after JumpSquare attribute as I want.
            fileIn >> squareAttributes[i];
            getline(fileIn, squareDescriptions[i]);
            if(squareDescriptions[i] == "")
                squareDescriptions[i] = "none";
            else{
                bool isEmpty;
                isEmpty = true;
                for(char letter : squareDescriptions[i])
                    isEmpty = isEmpty&&isspace(letter);
                if(isEmpty)
                    squareDescriptions[i] = "none";
                else
                    squareDescriptions[i] = squareDescriptions[i].substr(1);
            }
        }
        else if(typeOfSquares[i] == 'O'){
            fileIn >> squareAttributes[i];
            squareDescriptions[i] = "none";
        }
        else{
            squareAttributes[i] = 0;
            squareDescriptions[i] = "none";
        }

    }

    fileIn.close();

    Board mojaGra(sizeOfTheBoard, numberOfPlayers, typeOfSquares, squareAttributes, squareDescriptions, typesOfPlayers, namesOfPlayers);
    mojaGra.printBoard();
    while(mojaGra.getGameEnds() == false){
        mojaGra.executeRound();
    }

    return 0;
}
