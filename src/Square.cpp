#include "Square.h"
#include <iostream>
#include <Player.h>

using namespace std;

Square::Square() {}

void Square::debug() const {
    cout << "Debugging Square" << endl;
}

int Square::action(Player* player) const {
    cout << "Performing action on Square" << endl;
    return 0;
}

void Square::howDoILook() const {
    cout << look;
}

char Square::getLook() const {
    return look;
}

int Square::encounter(Player* player, int rollResult) const {
    return 0;
}

void Square::setDescription(std::string newDescription) {};

////////////////////OBLIGATORY/////////////////////////////////////////////

Obligatory::Obligatory() : Square() {}

StartSquare::StartSquare() : Obligatory() { look = 'S'; }

DestinationSquare::DestinationSquare() : Obligatory()  { look = 'D'; }

RegenerationSquare::RegenerationSquare() : Obligatory()  { look = 'R'; }

void RegenerationSquare::debug() const{
    cout << "Debugging RegenerationSqare, codded by letter: " << look << endl;
}

int RegenerationSquare::action(Player* player) const{
    player->printName();
    cout << " arrived at regeneration square ";
    if(player->getIncarnationLevel() != 13){
        cout << "and started regeneration process.";
        player->regenerate();
        cout << "They reached " << player->getIncarnationLevel() << ". incarnation of doKTOr, and now they have to rest. " << endl;
    }
    else
        cout << " but they are 13. doKTOr." << endl;
    player->setTurnsToWait(2);
    return 0;
}

int RegenerationSquare::encounter(Player* player, int rollResult) const{
    if(rollResult == 6)
        if(player->doIStopOnRegenerationSquare())
            return 1;
    return 0;
}

int DestinationSquare::action(Player* player) const{

    return 0;
}

void DestinationSquare::debug() const{
    cout << "Debugging DestinationSqare, codded by letter: " << look << endl;
}

int DestinationSquare::encounter(Player* player, int rollResult) const{
    if(player->getIncarnationLevel() == 13)
        return 2;
    return 0;
}

int StartSquare::action(Player* player) const{
    return 0;
}

void StartSquare::debug() const{
    cout << "Debugging StartSqare, codded by letter: " << look << endl;
}

int StartSquare::encounter(Player* player, int rollResult) const{
    return 0;
}

///////////////////NONOBLIGATORY////////////////////////////////////////////

NonObligatory::NonObligatory() {}

PlainSquare::PlainSquare() : NonObligatory()  { look = '.'; }

int PlainSquare::action(Player* player) const{
    return 0;    //this does nothing
}

int PlainSquare::encounter(Player* player, int rollResult) const{
    return 0;
}

WaitingSquare::WaitingSquare() : NonObligatory() { look = 'O'; }

WaitingSquare::WaitingSquare(unsigned int n) : NonObligatory(), howLongYoullWait(n) { look = 'O'; }

void WaitingSquare::debug() const {
    cout << "Debugging WaitingSquare coded by letter: "<< look <<  ", howLongYoullWait = " << howLongYoullWait << endl;
}

int WaitingSquare::action(Player* player) const {
    cout << "Player ";
    player->printName();
    cout << " have to wait " << howLongYoullWait << " rounds." << endl;
    player->setTurnsToWait(howLongYoullWait);
    return 0;
}

int WaitingSquare::encounter(Player* player, int rollResult) const{
    return 0;
}

JumpSquare::JumpSquare() { look = 'P'; }

JumpSquare::JumpSquare(int n) : NonObligatory(), whereIKickYou(n), description("Attention!") { look = 'P'; }

void JumpSquare::setDescription(std::string newDescription) {
    description = newDescription;
}

void JumpSquare::printDescription() const {
    cout << description << endl;
}

void JumpSquare::debug() const {
    cout << "Debugging JumpSquare coded by letter: "<< look <<  ", whereIKickYou = " << whereIKickYou << endl;
}

int JumpSquare::action(Player* player) const {
    printDescription();
    cout << "Player ";
    player->printName();
    cout << " is kicked " << whereIKickYou << " squares" << endl;
    return whereIKickYou;
}

int JumpSquare::encounter(Player* player, int rollResult) const{
    return 0;
}
