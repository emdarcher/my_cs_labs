
#ifndef EXP_MNG_H
#define EXP_MNG_H

#include "ExpressionManagerInterface.h"


class ExpressionManager : public ExpressionManagerInterface {

    public:
        ExpressionManager();
        virtual ~ExpressionManager();
        virtual bool isBalanced(string expression);
        virtual string postfixToInfix(string postfixExpression);
        virtual string infixToPostfix(string infixExpression);
        virtual string postfixEvaluate(string postfixExpression);
};

#endif
