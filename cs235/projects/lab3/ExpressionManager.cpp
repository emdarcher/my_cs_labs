
#include "ExpressionManager.h"

ExpressionManager::ExpressionManager(){

}
ExpressionManager::~ExpressionManager(){

}

bool ExpressionManager::balance_check_rec(stack<char>& in_tokens, char prev_char){
//recursive function which checks a stack of symbols for balance
    char top_char = '\0';

    if(prev_char == '\0'){
        //if this is the first time running

        //first check to make sure there is an even amount of tokens
        if(in_tokens.size() % 2 == 0){
            top_char = in_tokens.top();
            in_tokens.pop();
            return balance_check_rec(in_tokens, top_char);
        } else {
            return false;
        }
    }
    
    char check_prev_str[] = " ";
    check_prev_str[0] = prev_char;
    top_char = in_tokens.top(); 
    char check_top_str[] = " ";
    check_top_str[0] = top_char;

    in_tokens.pop();

    //check if the prev_char is a back character "}])"
    if(strcspn(check_prev_str, back_symbols) == 0){
        //check if the top_char is a back character
        if(strcspn(check_top_str, back_symbols) == 0){
            //if it is a back character as well
            //then pass further for recursive processing
            
            
            if(in_tokens.size() > 0){ 
                bool balanced = balance_check_rec(in_tokens, top_char); 
                if(balanced){
                    if(in_tokens.size() > 0){
                        return balance_check_rec(in_tokens, prev_char);    
                    } else {
                        //also a base case
                        return true;
                    }
                } else {
                    return false;
                }
            } else {
                //base case
                return false;
            }
        } else{
            //if it is a front character, does it pair?
            //get the indexes of the character matches
            //in the back_symbols and front_symbols arrays
            //to see if they match 
            //NOTE: this depends on the ordering of the symbols in the arrays
            //back_symbols and front_symbols in ExpressionManager.h
            //so don't change them!
            //
            if(strcspn(front_symbols, check_top_str) ==
                    strcspn(back_symbols, check_prev_str)){
                return true;
            } else {
                return false;
            }
        }
    } else {
        return false;
    }


}


bool ExpressionManager::isBalanced(string expression){
    stack<char> tokens;
    char exp_c_str[STR_BUFF_SIZE];
    exp_c_str[0] = '\0';
    strcpy(exp_c_str, expression.c_str());
    char * exp_ptr = exp_c_str;
    
    cout << "Called isBalanced( \"" << expression << "\" )\n";

    //increment the exp_ptr to the locations of symbols
    //and load them into the stack
    while( 1 ){
        //get the index of the matching char to the symbols "{}[]()"
        int index = strcspn(exp_ptr, symbols);
        //when the returned index is equal to the length of the string
        //then there are no more valid tokens, so break
        if(index == strlen(exp_ptr)){
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
    //if(tokens.size() % 2 != 0){
    //    return false;
    //}

    //checks for balance in the equation
    //set prev_symbol to NULL '\0' so the recursive function knows it's starting
    char prev_symbol = '\0';
    return balance_check_rec(tokens, prev_symbol);

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
