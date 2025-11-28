#ifndef DICE_H
#define DICE_H

#include <cstdlib>
#include <ctime>
#include <iostream>

class Dice {
    public:
        Dice();
        virtual ~Dice() = default;
        Dice& operator=(const Dice&) = delete;
        Dice& operator==(const Dice&) = delete;
        virtual int roll();
        virtual void debug() const;
    private:

};

class StandardDice : public Dice {
public:
    StandardDice();  // Konstruktor
    // Metoda roll nie jest ponownie zadeklarowana, ponieważ dziedziczymy ją po klasie Dice
};

class FaultyDice : public Dice {
public:
    FaultyDice();  // Konstruktor
    int roll() override;  // Przesłaniamy metodę roll, aby zmienić sposób losowania dla klasy FaultyDice
};

class WearingOutDice : public Dice {
private:
    int const highlightedNumber;
    int numberOfUses;
    int MaxBiasFactor;
public:
    WearingOutDice();
    ~WearingOutDice() = default;
    WearingOutDice(int numberOfPlayers, int numberOfSquares);
    int roll() override;
    void debug() const override;

};

#endif // DICE_H
