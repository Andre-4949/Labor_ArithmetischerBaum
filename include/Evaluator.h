#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stack>

#include "Token.h"
#include "Tokenizer.h"
#include "Vis.h"
#include "Num.h"
#include "../src/Util.h"

using namespace std;

class Evaluator {

public:

    /**
     * Takes a given string exp and parses it with:
     *      "<": Prefix
     *      ">": Postfix
     *      "|": Infix
     * Notation. It will print out the different notations, the amount of nodes of the tree, its depth and an ascii
     * representation with the root of the arithmetic tree lying on the right
     * @param exp mathematical expression
     * @param mode prefix("<") / postfix(">") / infix("|")
     * */
    void evaluate(string exp, char mode) {

        Tokenizer *t = new Tokenizer(exp);

        Token *e = parse(t->tokenize(), mode);

        // Testbaum, falls Tokenizer und/oder Parser noch nicht fertig:
        /*
        e = new Operator('+',
                   new Operator('*',
                          new Num(2),
                          new Num(3)),
                   new Operator('-',
                          new Operator('/',
                                 new Num(6),
                                 new Num(2)),
                          new Num(1)));
       */
        // Prefix:  + * 2 3 - / 6 2 1 = 8
        // Infix:   ((2 * 3) + ((6 / 2) - 1)) = 8
        // Postfix: 2 3 * 6 2 / 1 - + = 8
        // #Knoten: 9
        // Tiefe:   4

        cout << "Prefix:  " << e->prefix() << " = " << e->eval() << endl;
        cout << "Infix:   " << e->infix() << " = " << e->eval() << endl;
        cout << "Postfix: " << e->postfix() << " = " << e->eval() << endl;
        cout << "#Knoten: " << e->nodes() << endl;
        cout << "Tiefe:   " << e->depth() << endl;
        ((Operator*)e)->print(e,2);
        Vis *v = new Vis(e, Vis::REGULAR); // Layout 1: gleiche Abstände zwischen Knoten

    }

private:
    /**
     * parses tokenized expression from tok with given mode
     * @param tok vector of tokenized expression
     * @param mode prefix("<") / postfix(">") / infix("|")
     * */
    Token *parse(vector<Token *> *tok, char mode) {
        vector<Token *> i = *tok;
        switch (mode) {
            case '<':
                return parsePrefix(i);
            case '>':
                return parsePostfix(i);
            default :
                return parseInfix(i);
        }
    }

    /**
     * Parses in prefix order.
     * Inserting prefix is just in order of the given tokens.
     * @param tokens parsed tokens
     * */
    Token *parsePrefix(vector<Token *> tokens) {
        Token * root = tokens[0];
        tokens.erase(tokens.begin());
        while(tokens.size()>=1){
            root->insertPrefix(tokens[0]);
            tokens.erase(tokens.begin());
        }
        return root;
    }


    /**
     * Parses in postfix order.
     * Inserting postfix is like inserting in prefix,
     * but starting from the back of the vector and changing
     * the preferred side on which the new element should be inserted.
     * @param tokens parsed tokens
     * */
    Token *parsePostfix(vector<Token *> tokens) {
        Token * root = tokens[tokens.size()-1];
        tokens.erase(tokens.end());
        while(tokens.size()>=1){
            root->insertPostfix(tokens[tokens.size()-1]);
            tokens.erase(tokens.end());
        }
        return root;
    }


    /**
     * Parses in Infix order.
     * Infix is special as the operator is in the middle of the expression,
     * therefore we have to split the expression at "+" or "-" and "*" or "/" if there
     * is no "+" or "-". For this splitting there is Util::splitVectorAtOperator
     * The then returned list contains [operator, expressionLeft, expressionRight].
     * This list is partially in preorder, which means the operator can be inserted.
     * If the expression on the left or right is just a single character,
     * the character is inserted into the tree. Otherwise these characters will also be
     * split and the cycle repeats.
     *
     * @param tokens tokens in infix notation
     * */
    Token *parseInfix(vector<Token *> tokens) {
        deque<vector<Token *>> tokensToInsert = Util::splitVectorAtOperator(tokens);
        Token *start = tokensToInsert[0][0];
        tokensToInsert.erase(tokensToInsert.begin());
        while (!tokensToInsert.empty()) {
            if(tokensToInsert[0].size()>1){
                deque<vector<Token*>> newTokensToInsert = Util::splitVectorAtOperator(tokensToInsert[0]);
                tokensToInsert.erase(tokensToInsert.begin());
                std::reverse(newTokensToInsert.begin(), newTokensToInsert.end());

                for (const auto &item: newTokensToInsert){
                    tokensToInsert.insert(tokensToInsert.begin(),item);
                }
            } else {
                start->insertPrefix(tokensToInsert[0][0]);
//                std::cout << tokensToInsert[0][0]->value << std::endl;
                tokensToInsert.erase(tokensToInsert.begin());
            }
        }


        return start; // remove this line
    }

};