#include <iostream>
#include <stack>
using namespace std;

struct State
{
    int c;
    struct State *out;
    struct State *out1;
};

struct Ptrlist{
    struct State **outp;
    struct Ptrlist *next;
};

struct Frag{

    struct State* start;
    struct Ptrlist *out; //outging dangling pointers
};

State* state(int c,State *out,State *out1){
    State* s = (State *)malloc(sizeof(State));
    s->c = c;
    s->out = out;
    s->out1 = out1;
    return s;
}

Ptrlist* list(State **outp){
    Ptrlist *list = (Ptrlist *)malloc(sizeof(Ptrlist));
    list->outp = outp;
    list->next = NULL;
    return list;
}

Frag frag(State *start,Ptrlist *out){
    Frag f;
    f.start = start;
    f.out = out;
    return f;
}


void postToNFA(string postFixExpression){

    stack<Frag> fragments;
    for(char p: postFixExpression){
        switch (p)
        {
        case '*':
            /* code */
            break;
        case '+':
            break;
        case '|':
            break;
        case '.':
            break;
        default: //literal character
            State *s = state(p,NULL,NULL);
            Frag fragment = frag(s,list(&s->out));
            fragments.push(fragment);
        }
    }
}


int getPrecedence(char ch)
{
    switch (ch)
    {

    case '*':
    case '+':
    case '?':
        return 3;
    case '.':
        return 2;
    case '|':
        return 1;
    default:
        return 0;
    }
}

bool checkPriority(char currElement, char topOfStack)
{

    if (getPrecedence(currElement) > getPrecedence(topOfStack))
    {
        return true;
    }
    else
    {
        return false;
    }
}

string getModifiedInputString(string expression)
{
    int strLength = expression.length();
    if (strLength <= 1)
    {
        return " ";
    }

    string resultExpression;
    resultExpression.push_back(expression[0]);

    for (int i = 1; i < strLength; i++)
    {
        char prevCh = expression[i - 1];
        char currCh = expression[i];

        if ((isalnum(prevCh) || prevCh == ')' || prevCh == '*' || prevCh == '?' || prevCh == '+') &&
            (isalnum(currCh) || currCh == '('))
        {

            resultExpression.push_back('.');
        }
        resultExpression.push_back(currCh);
    }
    return resultExpression;
}
string infixtoPstfix(string expr)
{
    stack<char> s;
    string modifiedExpression = getModifiedInputString(expr);
    int strLength = modifiedExpression.length();
    if (strLength <= 1 && isalnum(modifiedExpression[0]))
        return "";
    string result;
    for (int i = 0; i < strLength; i++)
    {

        if (modifiedExpression[i] >= 'a' && modifiedExpression[i] <= 'z')
        {
            result.push_back(modifiedExpression[i]);
        }
        else if (modifiedExpression[i] == '(')
        {
            s.push(modifiedExpression[i]);
        }
        else if (modifiedExpression[i] == ')')
        {

            while (!s.empty() && s.top() != '(')
            {
                char ch = s.top();
                result.push_back(ch);
                s.pop();
            }
            if (!s.empty())
            {
                s.pop();
            }
        }
        else
        {

            while (!s.empty() && (getPrecedence(modifiedExpression[i]) <= getPrecedence(s.top())))
            {
                char ch = s.top();
                result.push_back(ch);
                s.pop();
            }
            s.push(modifiedExpression[i]);
        }
    }

    while (!s.empty())
    {
        char ch = s.top();
        result.push_back(ch);
        s.pop();
    }
    // cout << result << endl;
    return result;
}

int main()
{
    string s = "a|bc";
    string s1 = "a|bc";     // Should be abc.|
    string s2 = "a(b|c)*d"; // Should be abc|*.d.
    string s3 = "ab|c";

    // cout << getModifiedInputString("a.b|c");
    // infixtoPstfix(s);
    // infixtoPstfix(s1);
    // infixtoPstfix(s2);
    // infixtoPstfix(s3);
    string postFixExpression = infixtoPstfix(s);
    if(postFixExpression.length() >1){
        cout << postFixExpression;

    }
    
    return 0;
}
