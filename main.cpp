/*
 BY: MOSTAFA OSMAN
 Shunting yard algorithm using stack and queue, currently only does postfix
 */

#include <iostream>
#include <cstring>
#include "tree.h"

using namespace std;

// Declaring Stack
struct Stack
{
    char StackData;
    
    Stack *StackLink;
};

struct StackT
{
    tree* StackDataT;
    StackT* StackLinkT;
};

tree* peekT();
tree* popT();
void StackPushT(tree* t);
bool isStackEmptyT();
StackT *topT = NULL;
StackT *bottomT = NULL;


bool isStackEmpty();
void StackPush(char value);
char pop();
char peek();
void clearStack();
// stack pointers
Stack *top = NULL;
Stack *bottom=NULL;
// declaring queue
struct Queue
{
    char QueueData;
    
    Queue *QueueLink;
};

bool isQueueEmpty();
void enqueue(int value);
void dequeue();
char showFirst();
void printQueue();
// queue pointers
Queue *front = NULL;
Queue *rear = NULL;

int findPrecedence(char op);

void preFix(tree* n);
void postFix(tree* n);
void inFix(tree* n);
tree* createData();
tree* buildTree();

int main()
{
    //tree* a = new tree("a");
    //tree* data = createData() ;
    //inFix(data);
    
    
    int i = 0;
    char input[50], input2[50], prefix[100];
    cout << "Please input an equation." << endl;
    cin.get(input, 50);
    cin.clear();
    cin.ignore(100000, '\n');
    
    cout << input << endl;
    
    while(input[i] != '\0')
    {
        //cout << input[i];
        if (input[i] == '(')
        {
            // add to stack
            cout<<"\nstack push "<<input[i];
            StackPush(input[i]);
        }
        // if it is an operand
        else if (isalpha(input[i]))
        {
            cout<<"\nqueue "<<input[i];
            enqueue(input[i]);
        }
        // If it is an operator
        //check precedence with top of stack
        //if greater then push into stack
        //if not then pop all the stack into the queue
        else if (input[i] == '+' || input[i] == '-' ||  input[i] == '*' || input[i] == '/' || input[i] == '^')
        {
            if (isStackEmpty())
            {
                cout<<"\nstack push "<<input[i];
                StackPush(input[i]);
            }
            else if (findPrecedence(input[i]) >= findPrecedence(peek()))
                StackPush(input[i]);
            else
            {
                while(!isStackEmpty())
                {
                    enqueue(pop());
                }
                StackPush(input[i]);
            }
            
        }
        // if it closing bracket
        else if (input[i] == ')')
        {
            while (peek() != '(')
            {
                enqueue(pop());
            }
            pop();
        }
        
        //if ((isStackEmpty() == false) && (i == strlen(input)-1))
        i++;
        // if the stack is empty then add to queue
    }
    
    //Now put everything in the queue
    while(!isStackEmpty())
        enqueue(pop());
    
    printQueue();
    
    tree* data = buildTree();
    
    cout << "\nWould you like the output in infix, postfix, or prefix?" <<  endl;
    cin.get(input2, 50);
    cin.clear();
    cin.ignore(100000, '\n');
    cout <<  input2;
    
    if(strcmp(input2, "infix") == 0)
    {
        inFix(data);
    }
    
    if(strcmp(input2, "postfix") == 0)
    {
        postFix(data);
    }
    
    if(strcmp(input2, "prefix") == 0)
    {
        preFix(data);
    }
    else
    {
        cout << "Invalid Input." << endl;
    }
    //Print the queue postfix
    // printQueue();
    
    //Build the binary expression tree
    //tree* data = buildTree() ;
    
    //Print the tree inFix
    // inFix(data);
    
}

//Checks if stack is empty
bool isStackEmpty()
{
    if (top == NULL)
        return true;
    else
    {
        return false;
    }
}

// adds to top  of the stack
void StackPush(char value)
{
    Stack *ptr = new Stack();
    ptr -> StackData = value;
    ptr -> StackLink = top;
    top = ptr;
}

// takes element  off the top of the stack
char pop()
{
    char data;
    if(isStackEmpty() == true)
    {
        cout << "The stack is empty" << endl;
        return ' ';
    }
    else
    {
        Stack *ptr = top;
        top = ptr -> StackLink;
        data = ptr -> StackData;
        delete ptr;
        return data;
    }
    
}
// shows element at the top of the stack
char peek()
{
    char op = ' ';
    if (isStackEmpty() == true)
    {
        cout << "The stack is empty" << endl;
        return op;
    }
    else
    {
        cout << "The element at the top is: " << top -> StackData;
        op = top -> StackData;
        return op;
    }
    
}

//Checks if queue is empty
bool isQueueEmpty()
{
    if (front == NULL && rear == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// add to queue
void enqueue(int value)
{
    Queue *ptr = new Queue();
    ptr -> QueueData = value;
    ptr -> QueueLink = NULL;
    
    if (front == NULL)
    {
        front = ptr;
        rear = ptr;
    }
    else
    {
        rear -> QueueLink = ptr;
        rear = ptr;
    }
}

// delete from queue
void dequeue()
{
    if (isQueueEmpty() == true)
    {
        cout << "The queue is empty." << endl;
    }
    else
    {
        if (front == rear)
        {
            free(front);
            front = rear = NULL;
        }
        else
        {
            Queue *ptr = front;
            front = front -> QueueLink;
            free(ptr);
        }
    }
}

// show front of the queue
char showFirst()
{
    if (isQueueEmpty() == true)
    {
        cout << "The queue is empty." << endl;
        return 0;
    }
    else
    {
        cout << front -> QueueData;
        return front ->  QueueData;
    }
}

// prints queue
void printQueue()
{
    if (isQueueEmpty() == true)
    {
        cout << "The queue is empty." << endl;
    }
    else
    {
        Queue *ptr = front;
        cout<<"\n";
        while(ptr != NULL)
        {
            cout << ptr -> QueueData;
            ptr = ptr -> QueueLink;
        }
        cout<<"\n";
    }
}

//Purge stack
void clearStack()
{
    while (isStackEmpty() == false)
    {
        pop();
    }
}

//Assigns opaerator precedence
int findPrecedence(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '/':
        case '*':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

//Print Tree in Prefix
void preFix(tree* n)
{
    if (n == NULL)
    {
        return;
    }
    else
    {
        cout << n -> getData();
        preFix(n -> getLeft());
        preFix(n -> getRight());
    }
}

//Print Tree in Postfix
void postFix(tree* n)
{
    if (n == NULL)
    {
        return;
    }
    else
    {
        postFix(n -> getLeft());
        postFix(n -> getRight());
        cout << n -> getData();
    }
}

//Print tree inFix
void inFix(tree* n)
{
    if (n == NULL)
    {
        return;
    }
    else
    {
        inFix(n -> getLeft());
        cout << n -> getData();
        inFix(n -> getRight());
    }
}

//Determines if tree stack is empty
bool isStackEmptyT()
{
    if (topT == NULL)
        return true;
    else
    {
        return false;
    }
}

//Pop tree stack
tree* popT()
{
    tree* data = NULL;
    if(isStackEmptyT() == true)
    {
        cout << "The stack is empty" << endl;
        return data;
    }
    else
    {
        StackT *ptr = topT;
        topT = ptr -> StackLinkT;
        data = ptr -> StackDataT;
        delete ptr;
        return data;
    }
}

//Push in tree stack
void StackPushT(tree* t)
{
    StackT *ptr = new StackT();
    ptr -> StackDataT = t;
    ptr -> StackLinkT = topT;
    topT = ptr;
}
/*void StackPushT(tree* t)
 {
 tree* ptr;
 ptr -> getData() = t;
 ptr -> getNext() = topT;
 topT = ptr;
 }*/


tree* peekT()
{
    tree* op = NULL; //= new tree(" ");
    if (isStackEmptyT() == true)
    {
        cout << "The stack is empty" << endl;
        return op;
    }
    else
    {
        cout << "The element at the top is: " << topT -> StackDataT -> getData();
        op = (tree *) topT;
        //op = op -> getData();
        //op -> setLeft(op -> getLeft());
        //op -> setRight(op -> getRight());
        return op;
    }
    
}

//Test function for debugging
tree* createData()
{
    tree* a = new tree("a");
    tree* b = new tree("b");
    tree* c = new tree("c");
    tree* d = new tree("d");
    tree* e = new tree("e");
    tree* f = new tree("f");
    tree* g = new tree("g");
    
    a -> setLeft(b);
    a -> setRight(g);
    b -> setLeft(c);
    b -> setRight(d);
    c -> setLeft(e);
    e -> setRight(f);
    
    return a;
}

//Build a binary expression tree from the postfix queue
tree* buildTree()
{
    // build tree
    Queue* position;
    position = front;
    
    //Traverse the queue left to right
    while (position != rear->QueueLink)
    {
        char treeData = position -> QueueData;
        //if it is  an operand, push it in the stack
        if (isalpha(treeData))
        {
            char* dataptr = &treeData;
            tree* operand = new tree(dataptr);
            StackPushT(operand);
            cout << "Pushed" << endl;
        }
        //if it is an operator, then assign the left and right to be the two top stack nodes
        else if (treeData == '+' || treeData == '-' || treeData == '/' || treeData == '*' || treeData == '^')
        {
            // tree* r = popT();
            // tree* l = popT();
            tree* t = new tree(&treeData);
            tree* right = peekT();
            popT();
            tree* left = peekT();
            popT();
            cout << "Pushed" << endl;
            // Right branch = pop
            t -> setRight(right);
            // left branch = pop
            t -> setLeft(left);
            StackPushT(t);
        }
        //Move forward in the queue
        position = position -> QueueLink;
    }
    
    //tree* root = new tree(peekT());
    return (tree *) topT;
}
