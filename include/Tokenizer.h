#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "Num.h"
#include "Bracket.h"
#include "Operator.h"


using namespace std;

class Tokenizer {
    static inline std::vector<char> operators = {'+', '-', '*', '/'};
    string src;

public:
    Tokenizer(string s) {
        src = s + " ";
    }

    vector<Token *> *tokenize() {
        vector<Token *> *tokens = new std::vector<Token *>();

        for (int j = 0; j < this->src.length(); ++j) {
            char currentChar = src[j];
            int numStartIndex = j;// remembers the first index of a number if the number is greater than 9
            bool isNum = false;

            // if is bracket, insert bracket
            if (currentChar == '(' || currentChar == ')') {
                tokens->push_back(new Bracket(currentChar));
            }

            //if number, repeat until currentChar is no longer a number
            //all digits are between ascii '0' (or 48) and ('9' or 57)
            while (currentChar >= '0' && currentChar <= '9') {
                isNum = true;
                currentChar = src[j++];
            }

            if (isNum) {// Number parsing
                j--;
                std::string numAsStr = this->src.substr(numStartIndex, j-- - numStartIndex);
                Num* num = new Num(std::stoi(numAsStr));
                tokens->push_back(num);
            } else if (std::any_of(operators.begin(), operators.end(),
                                   [currentChar](char c) { return currentChar == c; })) {// if any of the specified operators from above
                tokens->push_back(new Operator(currentChar));
            }
        }

        return tokens;
    }

};