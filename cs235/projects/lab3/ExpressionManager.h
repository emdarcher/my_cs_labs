
#ifndef EXP_MNG_H
#define EXP_MNG_H

#include "ExpressionManagerInterface.h"
#include <string.h>

#define STR_BUFF_SIZE 256

const char symbols[] = "{}()[]";

class ExpressionManager : public ExpressionManagerInterface {
    private:
        //stack<char> tokens;
    public:
        ExpressionManager();
        virtual ~ExpressionManager();
        virtual bool isBalanced(string expression);
        virtual string postfixToInfix(string postfixExpression);
        virtual string infixToPostfix(string infixExpression);
        virtual string postfixEvaluate(string postfixExpression);
};

#endif