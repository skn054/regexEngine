#include <iostream>
#include <stack>
using namespace std;

int listid =0;
struct State
{
    int c;
    struct State *out;
    struct State *out1;
    int lastlist;
};

struct Ptrlist
{
    struct State **outp;
    struct Ptrlist *next;
};

struct Frag
{

    struct State *start;
    struct Ptrlist *out; // outging dangling pointers
};

struct List
{

    struct State **s;
    int n; // keeptrack of no of states in list.
};


struct List l1;
struct List l2;
int match(State *start,char *s){
      
    List *clist,*nlist,*t;
    clist = startList(start,&l1);
    nlist = &l2;
    for(;*s;s++){
        step(clist,*s,nlist);
        t = clist;
        clist = nlist;
        nlist = t;
    }
    return ismatch(clist);
}

int ismatch(List *nlist){
    for(int i=0;i<nlist->n;i++){
        if(nlist->s[i]->c == 257){
            return 1;
        }
    }
    return 0;
}

void step(List *clist,int c,List *nlist){
    int i;
    listid++;
    nlist->n = 0;
    for(i=0;i<clist->n;i++){
        if(clist->s[i]->c == c){
            addState(nlist,clist->s[i]->out);
        }
    }
}

// ad start state to list
void addState(List *l1, State *s)
{
    if(s == NULL || s->lastlist == listid){
        return;
    }
    if (s->c == 256)
    {
        addState(l1,s->out);
        addState(l1,s->out1);
    }

    // add start state to list
    l1->s[l1->n++] = s;
}
List* startList(State *start, List *l1)
{

    listid++;
    l1->n = 0;
    addState(l1, start);
    return l1;
}

State *state(int c, State *out, State *out1)
{
    State *s = (State *)malloc(sizeof(State));
    s->c = c;
    s->out = out;
    s->out1 = out1;
    s->lastlist = 0;
    return s;
}

Ptrlist *list(State **outp)
{
    Ptrlist *list = (Ptrlist *)malloc(sizeof(Ptrlist));
    list->outp = outp;
    list->next = NULL;
    return list;
}

Frag frag(State *start, Ptrlist *out)
{
    Frag f;
    f.start = start;
    f.out = out;
    return f;
}

void patch(Ptrlist *list1, State *state)
{

    while (list1 != NULL)
    {
        *(list1->outp) = state;
        list1 = list1->next;
    }
}

Ptrlist *append(Ptrlist *list1, Ptrlist *list2)
{
    if (list1 == NULL)
        return list2;
    Ptrlist *newList = list1;
    while (list1 != NULL)
    {
        list1 = list1->next;
    }
    list1->next = list2;
    return newList;
}

State *postToNFA(string postFixExpression)
{

    stack<Frag> fragments;
    State *matchstate = state(257, NULL, NULL);
    for (char p : postFixExpression)
    {
        switch (p)
        {
        case '*':
            /* code */
            Frag first = fragments.top();
            fragments.pop();
            State *newState = state(256, first.start, NULL);
            patch(first.out, newState);
            fragments.push(frag(newState, list(&newState->out1)));
            break;
        case '+':
            Frag first = fragments.top();
            fragments.pop();
            State *newState = state(256, first.start, NULL);
            patch(first.out, newState);
            fragments.push(frag(first.start, list(&newState->out1)));
            break;
        case '|':
            Frag second = fragments.top();
            fragments.pop();
            Frag first = fragments.top();
            fragments.pop();
            State *newState = state(256, first.start, second.start);
            fragments.push(frag(newState, append(first.out, second.out)));
            break;
        case '?':
            Frag first = fragments.top();
            fragments.pop();
            State *newState = state(256, first.start, NULL);
            fragments.push(frag(newState, append(first.out, NULL)));
            break;
        case '.':
            Frag second = fragments.top();
            fragments.pop();
            Frag first = fragments.top();
            fragments.pop();
            patch(first.out, second.start);
            fragments.push(frag(first.start, second.out));
            break;
        default: // literal character
            State *s = state(p, NULL, NULL);
            Frag fragment = frag(s, list(&s->out));
            fragments.push(fragment);
        }
    }

    Frag start = fragments.top();
    fragments.pop();
    patch(start.out, matchstate);
    return start.start;
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
    // string postFixExpression = infixtoPstfix(s);
    // if (postFixExpression.length() > 1)
    // {
    //     cout << postFixExpression;
    // }
    //test
    string postfix =  infixtoPstfix("a.b|c");
    State * start = postToNFA(postfix);
    cout << match(start,"ac");
    cout << match(start,"bc");
    cout << match(start,"abc");

    return 0;
}
