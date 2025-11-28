#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <Player.h>

class Square {
protected:
    char look;
public:
    Square();
    virtual ~Square() = default;
    Square& operator==(const Square&) = delete;
    Square& operator=(const Square&) = default; //jeszcze nie pamiętam czemu tak
    char getLook() const;
    void howDoILook() const;
    virtual void debug() const;
    virtual int action(Player* player) const;
    virtual int encounter(Player* player, int rollResult) const;
    virtual void setDescription(std::string newDescription);

};

//////////////////////OBLIGATORY/////////////////////////////////////////////////

class Obligatory : public Square {

public:
    Obligatory();
};

class StartSquare : public Obligatory {
public:
    StartSquare();
    void debug() const override;
    int action(Player* player) const override;
    int encounter(Player* player, int rollResult) const override;
};

class DestinationSquare : public Obligatory{
public:
    DestinationSquare();             //people end here, but that's still Board class's problem?
    int action(Player* player) const override;
    void debug() const override;
    int encounter(Player* player, int rollResult) const override;
};

class RegenerationSquare : public Obligatory{
public:
    RegenerationSquare();
    int action(Player* player) const override;
    void debug() const override;
    int encounter(Player* player, int rollResult) const override;
};

//////////////////NONOBLIGATORY//////////////////////////////////////////////////////

class NonObligatory : public Square {
public:
    NonObligatory();
};

class PlainSquare : public NonObligatory {
public:
    PlainSquare();
    int action(Player* player) const override;
    int encounter(Player* player, int rollResult) const override;
};

class WaitingSquare : public NonObligatory{
protected:
    unsigned int howLongYoullWait; //wait >0 time
public:
    WaitingSquare();
    WaitingSquare(unsigned int n);
    void debug() const override;
    int action(Player* player) const override;
    int encounter(Player* player, int rollResult) const override;
    void printDescription() const;
};

class JumpSquare : public NonObligatory{ //it has predefined jump lenght
protected:
    int whereIKickYou;
    std::string description;
public:
    JumpSquare();
    JumpSquare(int n);
    void debug() const override;
    int action(Player* player) const override;
    int encounter(Player* player, int rollResult) const override;
    void setDescription(std::string newDescription);
    void printDescription() const;
};
#endif // SQUARE_H
