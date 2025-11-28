#include "Dice.h"

using namespace std;

Dice::Dice() {
    srand(time(0));
}

void Dice::debug() const {
    cout << "Debugging Dice" << endl;
}

int Dice::roll() {
    return (rand() % 6) + 1;
}

StandardDice::StandardDice() : Dice() {}
    // Konstruktor klasy StandardDice korzysta z konstruktora klasy bazowej Dice


FaultyDice::FaultyDice() : Dice() {}
    // Konstruktor klasy FaultyDice korzysta z konstruktora klasy bazowej Dice


WearingOutDice::WearingOutDice(int numberOfPlayers, int numberOfSquares) : Dice(), highlightedNumber((std::rand() % 2 == 0) ? 1 : 6), numberOfUses(0), MaxBiasFactor(numberOfPlayers*numberOfSquares) {
    srand(time(0));
}           // The tempo of biasing is related to possible lenght of the game.

WearingOutDice::WearingOutDice() : Dice(), highlightedNumber((std::rand() % 2 == 0) ? 1 : 6), numberOfUses(0), MaxBiasFactor(0){ srand(time(0)); }

int FaultyDice::roll() {
    if (rand() % 3 == 0)
        return 6;
    else
        return 1;
}

int WearingOutDice::roll() {

    int result = rand() % (2*MaxBiasFactor); //a number from [0 to 2*MaxBiasFactor), everything is settled here
    result = result- 2*MaxBiasFactor/6 - numberOfUses;
    if(result < 1) //if <= 0, then result is <= rangeOfRand/6 + numberOfUses, else
        result = highlightedNumber;
    else{
        result = result % 5 + 1; //get from remaining propability what number you get, notice its in 1 to 5, so..
        if(highlightedNumber == 1 && result == 1)
            result = 6;          //it checks it highlightedNumber is 1 to avoid counting propability for 1 twice.
        }
    if(numberOfUses<MaxBiasFactor)
    ++numberOfUses;     //Dice wears out to certain point :b
    return result;
}

void WearingOutDice::debug() const {
    cout << "Debugging WearingOutDice" << endl;
    cout << "Highlighted Number: " << highlightedNumber << endl;
    cout << "Number of Uses: " << numberOfUses << endl;
    cout << "Maximal bias number: " << MaxBiasFactor << endl;
}
