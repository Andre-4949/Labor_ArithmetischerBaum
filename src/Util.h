//
// Created by andre on 27.06.2024.
//

#ifndef LABORRECHENBAUM_UTIL_H
#define LABORRECHENBAUM_UTIL_H


#include <vector>
#include <deque>
#include "../include/Token.h"

class Util {
public:
    /**
     * infix to prefix converter basically:
     * works by following these rules:
     * -skips brackets
     * -if can split at + or -, then do this, as multiplying or dividing is a stronger bond (this is the best description i can think of)
     * -if can't split at + or -, split at * or /
     * -if index(the index at which the tokens are split), is -1 recursively parse deeper into the bracket structure until a number is found
     * -if index is not -1, split at -1, put operator in the beginning, the left part in the second spot and the right part at the end. ([operator], [infix expression on the left], [infix expression on the right])
     *
     * Note:
     * - this will be applied by the parseInfix method until there is no more of the infix expressions left
     * */
    static std::deque<std::vector<Token *>> splitVectorAtOperator(std::vector<Token *> tokens) {
        int openBrackets = 0;
        int index = -1;
        bool splitAtAdditionSubtraction = false;
        for (int i = 0; i < tokens.size() - 1; i++) {
            Token *item = tokens[i];
            if (item->type == 'b') {
                if (item->value == '(')openBrackets++;
                if (item->value == ')')openBrackets--;
                continue;
            }
            if (openBrackets >= 1)continue;
            if (item->type == 'o') {
                if ((item->value == '+' || item->value == '-')) {
                    index = i;
                    splitAtAdditionSubtraction = true;
                }
                if ((item->value == '*' || item->value == '/') && !splitAtAdditionSubtraction) {
                    index = i;

                }
            }
        }
        if (index == -1) {
            auto first = ++tokens.begin();
            auto last = --tokens.end();
            vector<Token *> newVec(first, last);
            return splitVectorAtOperator(newVec);
        }
        auto first = tokens.begin();
        auto mid = tokens.begin() + index;
        auto last = tokens.end();
        vector<Token *> firstHalf(first, mid);
        vector<Token *> secondHalf(mid + 1, last);
        vector<Token *> middle = {tokens[index]};
        deque <vector<Token *>> result = {middle, firstHalf, secondHalf};
        result.shrink_to_fit();
        return result;

    }

};


#endif //LABORRECHENBAUM_UTIL_H
