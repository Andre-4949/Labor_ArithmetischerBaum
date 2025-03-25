#include <iostream>
#include <queue>
#include "../include/Tokenizer.h"
#include "Util.h"
#include "../include/Evaluator.h"

int main(int argc, const char *argv[]) {
    std::string expression;
    char mode;

    if (argc < 3) {
        std::cout << "As no defaults args were provided, please enter them now or cancel the input with ctrl+c."
                  << std::endl;
        std::cout << "In which mode do you want your string to be parsed:\n\t< Prefix\n\t> Postfix\n\t| Infix\n\n"
                  << std::endl;
        std::cin >> mode;
        std::cin.ignore();
        std::cout << "Insert your expression:" << std::endl;
        std::getline(std::cin, expression);
    } else {
        mode = argv[1][0];
        if (!(mode == '>' | mode == '<' | mode == '|')) {
            std::cout
                    << "Mode has been parsed wrong. if this keeps happening try to use this programm without parameters and use the input process that will be proposed."
                    << std::endl;
            return -1;
        }
        for (int i = 2; i < argc; ++i) {
            expression.append(argv[i]).append(" ");
        }
    }
    Evaluator evaluator = Evaluator();
    //((2+3)*(5+(4*4)))+(7*8-(9/3)+(10/10))
    evaluator.evaluate(expression, mode);
    cout << endl;
    return 0;
}
