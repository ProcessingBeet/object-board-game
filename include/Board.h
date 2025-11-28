#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <Square.h> //for vector of pointers to Squares.
#include <Player.h>
#include <memory>


class Board{
protected:
    std::vector<Square*> Map;
    int numberOfPlayers;
    int sizeOfTheBoard;
    std::vector<Player*> Players;
    std::vector<Player*> Winners;
    bool gameEnds;
public:
    Board(int howBigTheBoard, int howManyPlayers, char* squareTypes, int* squareAttributes, std::string* squareDescriptions, char* arrrayOfPlayerTypes, std::string* playerNames);
    Board();
    ~Board() = default;
    Board& operator=(const Board&) = delete;    //i do not really need it
    Board& operator==(const Board&) = delete;
    void printBoard() const;
    void executeRound();
    int findSquareOnMap(Square* searchedPosition) const;
    bool getGameEnds()const;
    int getWinnersNumber();
    void giveInsight(Player* player);
    void checkGiveInsight();
};

#endif // BOARD_H
