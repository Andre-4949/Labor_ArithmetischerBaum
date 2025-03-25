#pragma once

#include <string>
#include "Order.h"
#include "Num.h"

using namespace std;

class Token {
public:
    char type;                        // Typ des Tokens / Knotens
    char value;                        // Typ des Tokens / Knotens
    int ord;                        // Reihenfolge fuer die Visualisierung

    char getType() { return type; } // Typ des Knotens
    virtual int eval() = 0;            // Auswertung
    virtual string prefix() = 0;    // Prefix-Darstellung
    virtual string infix() = 0;        // Infix-Darstellung
    virtual string postfix() = 0;    // Postfix-Darstellung
    virtual Token *getLeft() { return nullptr; }    // Linker Unterbaum
    virtual Token *getRight() { return nullptr; } // Rechter Unterbaum
    virtual int nodes() { return 1; }        // Anzahl der Knoten des Baums
    virtual int depth() { return 1; }


    // Gibt die Reihenfolge des Knotens in der Infix-Darstellung zurueck (wichtig fuer die Visualisierung).
    int getOrd() { return ord; }


    //Setzt die Nummer des Knotens in der Infix-Darstellung (wichtig fuer die Visualisierung).
    void setOrd(int o) { ord = o; }

    //Nummeriert den Baum ausgehend vom aktuellen Knoten unter Verwendung eines Zaehlers

    void order(Order *o);


    /**
     * This method is implemented in the individual classes, that derive from Token
     *
     * see Operator for more, implementation in Num is minimal
     **/
    virtual bool insertPrefix(Token *t) {
        return this->insertPrefix(t);
    }

    /**
     * This method is implemented in the individual classes, that derive from Token
     *
     * used for visualization
     * **/
    virtual string toString(){
        return "";
    }

    /**
     * This method is implemented in the individual classes, that derive from Token
     *
     * see Operator for more, implementation in Num is minimal
     **/
    virtual bool insertPostfix(Token *t) {
        return this->insertPostfix(t);
    }

    /**
     * reverse inorder ( right, root, left)
     * print root, spacing gets bigger the deeper the tree is traversed
     **/
    void print(Token *root, int space) {
        if (root == NULL)
            return;
        int count = 10;
        space += count;
    //        space*=2;
        print(root->getRight(), space);
        cout << endl;
        for (int i = 10; i < space; i++)
            cout << " ";
        cout << root->toString() << "\n";
        print(root->getLeft(), space);
    }
};