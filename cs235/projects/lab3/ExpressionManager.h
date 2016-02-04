
#ifndef EXP_MNG_H
#define EXP_MNG_H

#include "ExpressionManagerInterface.h"
#include <string.h>
#include <iostream>

#define STR_BUFF_SIZE 256

const char symbols[] = "{}()[]";
const char back_symbols[] = "}])";
const char front_symbols[] = "{[(";

class ExpressionManager : public ExpressionManagerInterface {
    private:
        //stack<char> tokens;
        bool balance_check_rec(stack<char>& in_tokens, char prev_char);
    public:
        ExpressionManager();
        virtual ~ExpressionManager();
        virtual bool isBalanced(string expression);
        virtual string postfixToInfix(string postfixExpression);
        virtual string infixToPostfix(string infixExpression);
        virtual string postfixEvaluate(string postfixExpression);
};

#endif
