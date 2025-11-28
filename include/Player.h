#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <Dice.h>

class Square;

class Player{
protected:
    int incarnationLevel = 9; //up to 13.
    char look;
    std::string name;
    Square* playerStandingSquare;
    int turnsToWait;
    Dice* myWearingOutDice;
public:
    Player();
    Player(int sizeOfTheBoard, int numberOfPlayers);
    virtual ~Player();
    Player& operator=(const Player&) = delete;  //i dont use it
    Player& operator==(const Player&) = delete;
    virtual int play();
    virtual void debug() const;
    int getIncarnationLevel() const;
    void regenerate();
    void printName() const;
    Square* giveStandingSquare() const;
    void setStandingSquare(Square* youStandHereNow);
    void printLook() const;
    virtual bool doIStopOnRegenerationSquare() const;
    void setTurnsToWait(int i);
    int getTurnsToWait();
    void waitTurn();
    virtual void setSquareInsight(char nextSixSquaresLook[6]);
    void printStatus() const;
};

class UnresponsivePlayer : public Player {
public:
    UnresponsivePlayer();
    void setSquareInsight(char nextSixSquaresLook[6]) override;
};

class AdaptivePlayer : public Player {
protected:
    char squareInsight[6] = {' ', ' ', ' ', ' ', ' ', ' '};
public:
    void debug() const override;
    AdaptivePlayer(int sizeOfTheBoard, int numberOfPlayers);
    void setSquareInsight(char nextSixSquaresLook[6]) override;
    void printInsight() const;
    bool doIStopOnRegenerationSquare() const override;
};

class RandomPlayer : public UnresponsivePlayer {
public:
    RandomPlayer(std::string _name, int sizeOfTheBoard, int numberOfPlayers);
    int play() override;
};

class TraditionalPlayer : public UnresponsivePlayer {
public:
    TraditionalPlayer(std::string _name, int sizeOfTheBoard, int numberOfPlayers);
    int play() override;
};

class ExperimenterPlayer : public AdaptivePlayer {
public:
    ExperimenterPlayer(std::string _name, int sizeOfTheBoard, int numberOfPlayers);
    int play() override;
};

class PrudentPlayer : public AdaptivePlayer {
private:
    int numberOfOnes = 0;
    int numberOfExperimentalRolls = 0;
public:
    PrudentPlayer(std::string _name, int sizeOfTheBoard, int numberOfPlayers);
    int play() override;
};



#endif // PLAYER_H
