#include "Player.h"
#include <Square.h>
#include <iostream>
#include <Dice.h>

using namespace std;

StandardDice StedfordTheDice; //well, it works, złe zarządzanie pamięcią
FaultyDice FlintTheDice; // :oooo

Player::Player() : playerStandingSquare(nullptr), turnsToWait(0), myWearingOutDice(new WearingOutDice()) {}

Player::Player(int sizeOfTheBoard, int numberOfPlayers) :  playerStandingSquare(nullptr), turnsToWait(0), myWearingOutDice(new WearingOutDice(sizeOfTheBoard, numberOfPlayers)) {}

Player::~Player(){  //to do!
    delete playerStandingSquare;
    delete myWearingOutDice;
}

void Player::printName() const{
    cout << name;
}

int Player::play(){
    return 0 ;
}

void Player::debug() const{
    cout << "current lvl is: " << incarnationLevel << " name: " << name << " and that's their player type: " << look << endl;
}

int Player::getIncarnationLevel() const{
    return incarnationLevel;
}

bool Player::doIStopOnRegenerationSquare() const{
    cout << "without stopping ";
    return false;
}

void Player::regenerate(){
    incarnationLevel++;
}

void Player::setTurnsToWait(int i) {
    turnsToWait = i;
}

int Player::getTurnsToWait() {
    return turnsToWait;
}

void Player::waitTurn(){
    turnsToWait--;
    cout << "Player " << name << " waits this turn.";
    if(turnsToWait == 0)
        cout << " But they get to move next turn." << endl;
    else if(turnsToWait == 1)
        cout << " And has still " << turnsToWait << " turn to wait." << endl;
    else
        cout << " And has still " << turnsToWait << " turns to wait." << endl;
}

Square* Player::giveStandingSquare() const{     //getter
    return playerStandingSquare;
}

void Player::setStandingSquare(Square* youStandHereNow){    //setter
    playerStandingSquare = youStandHereNow;
}

void Player::printLook() const{
    cout << look;
}

void Player::printStatus() const{
    cout << name << "'s"<< " incarnation lvl is " << incarnationLevel;
}

void Player::setSquareInsight(char nextSixSquaresLook[6]) {}

//////////////////////Unresponsive Player Class////////////////////////////

UnresponsivePlayer::UnresponsivePlayer() : Player() {}

void UnresponsivePlayer::setSquareInsight(char nextSixSquaresLook[6]){
    //this does nothing
};

//////////////////////Traditional Player///////////////////////////////////

TraditionalPlayer::TraditionalPlayer(std::string _name, int sizeOfTheBoard, int numberOfPlayers) : UnresponsivePlayer() {
    name = _name;
    look = 'T';
}

int TraditionalPlayer::play() {
    int result = StedfordTheDice.roll();
    return result;
}

///////////////////////Random Player////////////////////////////////////////

RandomPlayer::RandomPlayer(std::string _name, int sizeOfTheBoard, int numberOfPlayers) : UnresponsivePlayer() {
    name = _name;
    look = 'L';
}

int RandomPlayer::play() { return StedfordTheDice.roll(); }
////////////////////Adaptive Player Class/////////////////////////////////////

AdaptivePlayer::AdaptivePlayer(int sizeOfTheBoard, int numberOfPlayers) : Player(sizeOfTheBoard, numberOfPlayers) {}

void AdaptivePlayer::setSquareInsight(char nextSixSquaresLook[6]){
    for(int i=0;i<6;i++)
        squareInsight[i] = nextSixSquaresLook[i];
};

void AdaptivePlayer::debug() const {
    cout << "current lvl is: " << incarnationLevel << " name: " << name << " that's their player type: " << look << " and that's what they see: ";
    printInsight();
    cout << endl;
}

void AdaptivePlayer::printInsight() const {
    for(int i=0; i<6; i++)
        cout << squareInsight[i];
}

bool AdaptivePlayer::doIStopOnRegenerationSquare() const{
    if(incarnationLevel != 13){
        cout << "stopping in the middle ";
        return true;
    }
    return false;
}

/////////////////////Prudent Player/////////////////////////////////////////////

PrudentPlayer::PrudentPlayer(std::string _name, int sizeOfTheBoard, int numberOfPlayers) : AdaptivePlayer(sizeOfTheBoard, numberOfPlayers) {
    name = _name;
    look = 'R';
}

int PrudentPlayer::play(){

    if(incarnationLevel != 13){                 //only when it is benefitial to stand on regeneration square
        bool isRegenerationInSight = false;
        for(char i : squareInsight){            //loop for finding regeneration square.
            if(i == 'R'){
                isRegenerationInSight = true;
                break;
            }
        }

        if(isRegenerationInSight)
            return FlintTheDice.roll();         //if is within reach, prudent player will use faulty dice.
    }



    if(numberOfExperimentalRolls<10&&3*numberOfOnes<numberOfExperimentalRolls){     //a/b < 1/3 <=> 3a < b
        int result = myWearingOutDice->roll();                                       //Prudent throws wearingOutDice until they feel
        numberOfExperimentalRolls++;                                                //like they're not doing well. (to much 1's)
        if(result == 1)
            numberOfOnes++;
        return result;
    }

    return StedfordTheDice.roll();              //otherwise they use standard dice.
}


//////////////////////Experimenter Player////////////////////////////////////////

ExperimenterPlayer::ExperimenterPlayer(std::string _name, int sizeOfTheBoard, int numberOfPlayers) : AdaptivePlayer(sizeOfTheBoard, numberOfPlayers) {
    name = _name;
    look = 'E';
}

int ExperimenterPlayer::play() {
    return myWearingOutDice->roll();
}
