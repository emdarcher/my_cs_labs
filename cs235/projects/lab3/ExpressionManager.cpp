
#include "ExpressionManager.h"

ExpressionManager::ExpressionManager(){

}
ExpressionManager::~ExpressionManager(){

}
bool ExpressionManager::isBalanced(string expression){
    stack<char> tokens;
    char exp_c_str[STR_BUFF_SIZE];
    exp_c_str[0] = '\0';
    strcpy(exp_c_str, expression.c_str());
    char * exp_ptr = exp_c_str;

    //increment the exp_ptr to the locations of symbols
    //and load them into the stack
    while(exp_ptr != NULL){
        int index = strcspn(exp_ptr, symbols);
        exp_ptr += index;
        tokens.push(exp_ptr);
    }
    //check if the amount of symbols is not even, 
    //if it is not, then it must not be balanced
    if(tokens.size() % 2 != 0){
        return false;
    }

    
}
string ExpressionManager::postfixToInfix(string postfixExpression){

}
string ExpressionManager::infixToPostfix(string infixExpression){

}
string ExpressionManager::postfixEvaluate(string postfixExpression){

}
