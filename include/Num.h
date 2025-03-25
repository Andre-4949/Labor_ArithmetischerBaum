#pragma once

#include <iostream>
#include <string>
#include "Token.h"

class Num : public Token {

public:
    int number{};

    Num() = default; // DIESEN LEEREN STANDARDKONSTRUKTOR NICHT LOESCHEN
    explicit Num(int i) {
        this->type = 'n';
        number = i;
        value = i;
    }

    // returns number
    int eval() {
        return number;
    }

    // returns number as a string with space at the end
    string prefix() {
        return std::to_string(number)+" ";
    }

    // returns number
    string infix() {
        return std::to_string(number);
    }

    // returns number as a string with space at the end
    string postfix() {
        return std::to_string(number)+" ";
    }

    // returns false as inserting will not work
    bool insertPrefix(Token *t) override {
        return false;
    }

    // returns false as inserting will not work
    bool insertPostfix(Token *t) override {
        return false;
    }

    // returns number as a string
    string toString() override {
        return std::to_string(number);
    }

};