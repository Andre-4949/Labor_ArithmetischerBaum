#ifndef BracketDef
#define BracketDef

#include <iostream>
#include <string>
#include "Token.h"

class Bracket : public Token {

public:

    Bracket(char t, char value) { type = t, this->value = value; /* cout << "Bracket added: " << t << endl; */}
    Bracket(char value) { type = 'b', this->value = value; /* cout << "Bracket added: " << t << endl; */}


    int eval() { return 0; }


    string prefix() { return ""; }


    string infix() { return ""; }


    string postfix() { return ""; }

    void order(Order o) {}

    bool insertPrefix(Token *t) override {
        return false;
    }
};

#endif