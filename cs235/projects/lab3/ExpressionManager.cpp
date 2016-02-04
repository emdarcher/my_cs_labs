
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
    while( 1 ){
        //get the index of the matching char to the symbols "{}[]()"
        int index = strcspn(exp_ptr, symbols);
        //when the returned index is equal to the length of the string
        //then there are no more valid tokens, so break
        if(index == (strlen(exp_ptr)-0)){
            break;
        }
        //increment the pointer to the location of the match
        //thus making exp_ptr point to the matching character token
        //and shortening the string
        exp_ptr += index;
        //add the char token to the stack
        tokens.push( *exp_ptr);
        //debugging
        cout << "adding " << *exp_ptr << " to the stack\n";
        //make sure to increment the pointer so it's one char ahead
        //of the recent match, so the loop can continue to get the 
        //next match, in the now reduced string
        exp_ptr++;

    }
    //check if the amount of symbols is not even, 
    //if it is not, then it must not be balanced
    if(tokens.size() % 2 != 0){
        return false;
    }

    return true;    
}
string ExpressionManager::postfixToInfix(string postfixExpression){
    return "";
}
string ExpressionManager::infixToPostfix(string infixExpression){
    return "";
}
string ExpressionManager::postfixEvaluate(string postfixExpression){
    return "";
}
