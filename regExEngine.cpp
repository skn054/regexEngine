#include <iostream>
#include <stack>
using namespace std;

struct state
{
    int c;
    struct state *out;
    struct state *out1;
};

struct ptrlist{
    struct state **out;
    struct ptrlist *next;
};

struct Frag{

    struct state* st;
    struct ptrlist *list;
};

struct Frag* createStateAndFragmentForSymbol(char symbol){
    // create a state
    struct state *stt = (struct state*)malloc(sizeof(struct state));
    stt->c = (int)symbol;
    stt->out =NULL;
    stt->out1 = NULL;
    // create a fragment

    

    struct ptrlist *list = (struct ptrlist*) malloc(sizeof(struct ptrlist));
    list->out = &stt->out;
    list->next = NULL;

    struct Frag *frag = (struct Frag*)malloc(sizeof(struct Frag));
    frag->st =stt;
    frag->list = list;

    // return fragment
    return frag;
}
void createStateFromExpression(string postFixExpression){

    stack<Frag*> fragments;
    int postFixStrLen = postFixExpression.length();
    for(int i=0;i<postFixStrLen;i++){
        if(isalnum(postFixExpression[i])){
            struct Frag *fragment = createStateAndFragmentForSymbol(postFixExpression[i]);
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
