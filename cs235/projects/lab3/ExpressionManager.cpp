
#include "ExpressionManager.h"

ExpressionManager::ExpressionManager(){

}
ExpressionManager::~ExpressionManager(){

}

bool ExpressionManager::balance_check_rec(stack<char>& in_tokens, char prev_char){
//recursive function which checks a stack of symbols for balance
    char top_char = '\0';
    
    if(in_tokens.empty()){
        return true;
    }

    if(prev_char == '\0'){
        //if this is the first time running
        //first check to make sure there is an even amount of tokens
        //if the amount of tokens is not even then the function must
        //not be balanced
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
                } else { return false; }
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
            } else { return false; }
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

    //checks for balance in the equation
    //set prev_symbol to NULL '\0' so the recursive function knows it's starting
    char prev_symbol = '\0';
    return balance_check_rec(tokens, prev_symbol);
}
        
int ExpressionManager::get_precedence(char op){
    int paren_type = is_paren(op);
    if(paren_type != NOT_A_PAREN){
        //then it is a paren
        return paren_type; 
    }
    //otherwise it is an op
    char op_str[1];
    op_str[0] = op;
    op_str[1] = '\0';
    int index = strcspn(operators, op_str);
    return op_precedence[index];

}
    
bool ExpressionManager::is_op(char ch){
    return (strchr(operators, ch) != NULL);
}

int ExpressionManager::is_paren(char ch){
    if(strchr(front_symbols, ch) != NULL){
        return OPEN_PAREN;
    } else if(strchr(front_symbols, ch) != NULL){
        return CLOSE_PAREN;
    } else {
        return NOT_A_PAREN;
    }
}

bool ExpressionManager::is_int_num(string str){
    for(int i=0;i<str.length();i++){
        //cout << "check isdigit(\'" << str[i] << "\')\n";
        if(!isdigit(str[i])){
            return false;
        }
    }
    return true;
}

bool ExpressionManager::op_num_ratio_check(string expression){
    int op_cnt = 0;
    int num_cnt = 0;
    
    char exp_str[STR_BUFF_SIZE];
    exp_str[0] = '\0';
    //create a C string from the expression string
    //for use in strtok
    strcat(exp_str, expression.c_str());

    char * token;

    //use strtok to tokenize the string
    //separating by spaces

    token = strtok(exp_str, " ");
    while(token != NULL){
        //cout << "token: " << token << "\n";
        if(is_int_num(string(token))){
            num_cnt++;
        } else if(is_op( *token)){
            op_cnt++;
        } else if(strchr(symbols, *token) != NULL){
            //it's fine
        }  else {
            //it's not fine
            return false;
        }
        //increment to the next token
        token = strtok(NULL, " ");
    }
    return ((num_cnt - 1) == op_cnt);
}

bool ExpressionManager::is_valid(string expression){
    return false;
}

string ExpressionManager::postfixToInfix(string postfixExpression){
    if(!op_num_ratio_check(postfixExpression)){
        return invalid;
    }
    if(strcspn(postfixExpression.c_str(), symbols) 
            != postfixExpression.length()){
        //a postfix expression shouldn't have any paren symbols
        return invalid;
    }
    return "";
}
string ExpressionManager::infixToPostfix(string infixExpression){
    stack<char> symbols;
    string out_str = "";
    //do tests for the validity of the infix expression
    if(!isBalanced(infixExpression)){
        return invalid;
    }
    if(!op_num_ratio_check(infixExpression)){
        return invalid;
    }

    char exp_str[STR_BUFF_SIZE];
    exp_str[0] = '\0';
    //create a C string from the expression string
    //for use in strtok
    strcat(exp_str, infixExpression.c_str());

    char * token;

    //use strtok to tokenize the string
    //separating by spaces

    token = strtok(exp_str, " ");
    while(token != NULL){
        cout << "token: " << token << "\n";
        if(is_int_num(string(token))){
                out_str += string(token);
                out_str += " ";
        } else if(is_paren( *token ) == OPEN_PAREN){
            symbols.push( *token );
        } else if(is_paren( *token ) == CLOSE_PAREN){
            char top_char = symbols.top();
            symbols.pop(); 
            while(get_precedence(top_char) > CLOSE_PAREN){
                out_str += top_char;
                out_str += " ";
                top_char = symbols.top();
                symbols.pop();
            }
        }  else if(is_op( *token )){
            if(symbols.empty()){
                symbols.push( *token );
            } else {
                char top_char = symbols.top();
                int top_prec = get_precedence(top_char);
                int token_prec = get_precedence( *token );
                while( top_prec >= token_prec ){
                    //go through any tokens with greater than or equal precedence
                    symbols.pop();
                    out_str += top_char;
                    out_str += " ";
                    if(symbols.empty()){
                        break;
                    }
                    top_char = symbols.top();
                    top_prec = get_precedence(top_char);
                }
                symbols.push( *token );
            }
        }
        //increment to the next token
        token = strtok(NULL, " ");
    }
    

    return out_str;
}
string ExpressionManager::postfixEvaluate(string postfixExpression){
    if(!op_num_ratio_check(postfixExpression)){
        return invalid;
    }
    if(strcspn(postfixExpression.c_str(), symbols) 
            != postfixExpression.length()){
        //a postfix expression shouldn't have any paren symbols
        return invalid;
    }

    return "";
}
