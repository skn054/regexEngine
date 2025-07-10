#include <iostream>
#include <stack>
using namespace std;

struct state{
    int c;
    struct state *out;
    struct state *out1;
};

int getPrecedence(char ch){
    switch (ch)
    {
        case '(' || ')':
            return 4;
        
        case '*':
        case '+':
        case '?':
            return 3;
        case '.':
             return 2;
        case '|':
            return 1;
        default:
            break;
    }
}

bool checkPriority(char currElement,char topOfStack){
       
        if(getPrecedence(currElement)>getPrecedence(topOfStack)){
            return true;
        }else{
            return false;
        }
}
void infixtoPstfix(string expr){
    stack<char> s;
    int strLength = expr.length();
    string result;
    for(int i=0;i<strLength;i++){
        // cout << i;
        if(expr[i]>='a' && expr[i]<='z'){
            result.push_back(expr[i]);
            
        }else{
            if(s.empty()){
                s.push(expr[i]);
            }
            else if(checkPriority(expr[i],s.top())){ // priority of current element greater than top of stack, then push current Element
                s.push(expr[i]);
            }else{
                while(!s.empty()  && (getPrecedence(s.top()) <= getPrecedence(expr[i]))){
                char ch = s.top();
                result.push_back(ch);
                s.pop();

            }
        }
       
    }
}

while(!s.empty()){
    char ch = s.top();
    result.push_back(ch);
    s.pop();
}
    cout << result;
}


int main(){
    string s = "a|b.c";
    infixtoPstfix(s);
    return 0;
}

