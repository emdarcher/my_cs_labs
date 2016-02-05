
#ifndef EXP_MNG_H
#define EXP_MNG_H

#include "ExpressionManagerInterface.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include <ctype.h>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#define STR_BUFF_SIZE 512

const char symbols[] = "{}()[]";

//DO NOT CHANGE THE ORDER OF CHARACTERS IN THE FOLLOWING TWO ARRAYS!
const char back_symbols[] = "}])";
const char front_symbols[] = "{[(";

const string invalid = "invalid";

#define OPEN_PAREN 0
#define CLOSE_PAREN 3
#define NOT_A_PAREN -1

//DO NOT change the order of these arrays either!
const char operators[] = "+-/%*";
const int op_precedence[] = {1,1,2,2,2};

class ExpressionManager : public ExpressionManagerInterface {
    private:
        int is_paren(char ch);
        int get_precedence(char op);
        bool is_int_num(string str);
        bool is_op(char ch);
        bool op_num_ratio_check(string expression);
        bool is_valid(string expression);
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
