#ifndef OpDef
#define OpDef

#include <iostream>
#include <string>
#include "Token.h"
// previous name: Op
class Operator : public Token {
private:
    Token *left, *right;

public:
    Operator(char type, char t, Token *l, Token *r) {
        left = l;
        right = r;
    }

    explicit Operator(char value) {
        type = 'o';
        this->value = value;
        left = nullptr;
        right = nullptr;
    }


    Token *getLeft() { return left; }

    Token *getRight() { return right; }

    // evaluates tree based on value of operator
    int eval() {
        int result = this->left->eval();
        switch (this->value) {
            case '*':
                result *= this->right->eval();
                break;
            case '/':
                result /= this->right->eval();
                break;
            case '+':
                result += +this->right->eval();
                break;
            case '-':
                result -= this->right->eval();
                break;
        }
        return result;
    }

    // returns tree in prefix order
    string prefix() {
        return value + this->left->prefix() + this->right->prefix();
    }

    // returns tree in infix order
    string infix() {
        return "(" + this->left->infix() + value + this->right->infix() + ")";

    }

    // returns tree in postfix order
    string postfix() {
        return this->left->postfix() + this->right->postfix() + value;
    }

    int nodes() {
        int nodesLeft = left->type == 'n' ? 1 : left->nodes();
        int nodesRight = right->type == 'n' ? 1 : right->nodes();
        return nodesLeft + 1 + nodesRight;//+1 fuer Elternknoten
    }

    int depth() {
        return max(left->depth() + 1, right->depth() + 1);
    }


    /**
     * Inserts Token with these rules:
     *      try left
     *      if left is nothing insert on the left
     *      if left is something but it is an operator try inserting on the left of that operator
     *      if token has been inserted, return true
     *      if the left hasn't worked try right
     *      start over and apply rules from the top again until Token is inserted or tree has been traversed and the function returns false
     *      if returned false, arithmetic tree if full.
     * */
    bool insertPrefix(Token *t) {
        bool hasBeenInserted = false;
        if (left == nullptr) {
            left = t;
            return true;
        } else if (left->type == 'o') {
            hasBeenInserted = left->insertPrefix(t);
        }

        if (hasBeenInserted)return true;

        if (right == nullptr) {
            right = t;
            return true;
        } else if (right->type == 'o') {
            return right->insertPrefix(t);
        }
        return hasBeenInserted;
    }


    /**
     * Inserts Token with these rules:
     *      try right
     *      if right is nothing insert on the left
     *      if right is something but it is an operator try inserting on the right of that operator
     *      if token has been inserted, return true
     *      if the right hasn't worked try left
     *      start over and apply rules from the top again until Token is inserted or tree has been traversed and the function returns false
     *      if returned false, arithmetic tree if full.
     * */
    bool insertPostfix(Token *t) override {
        bool hasBeenInserted = false;
        if (right == nullptr) {
            right = t;
            return true;
        } else if (right->type == 'o') {
            hasBeenInserted = right->insertPostfix(t);
        }

        if (hasBeenInserted)return true;

        if (left == nullptr) {
            left = t;
            return true;
        } else if (left->type == 'o') {
            return left->insertPostfix(t);
        }
        return hasBeenInserted;
    }

    string toString() override {
        return string(1,value);
    }

};

#endif //OpDef