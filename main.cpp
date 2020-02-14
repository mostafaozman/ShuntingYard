/*
 BY: MOSTAFA OSMAN
 Shunting yard algorithm using stack and queue, currently only does postfix
 */

#include <iostream>
#include <cstring>

using namespace std;

// Declaring Stack
struct Stack
{
    char StackData;
    
    Stack *StackLink;
};

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
void showFirst();
void printQueue();
// queue pointers
Queue *front = NULL;
Queue *rear = NULL;

int findPrecedence(char op);

int main()
{
    int i = 0;
    int j = 0;
    char input[50], input2[50], prefix[100];
    cout << "Please input an equation." << endl;
    cin.get(input, 50);
    cin.clear();
    cin.ignore(100000, '\n');
    
    cout << input << endl;
    
    cout << "\nWould you like the output in infix, postfix, or prefix?" <<  endl;
    cin.get(input2, 50);
    cin.clear();
    cin.ignore(100000, '\n');
    cout <<  input2;
    
    /*
     
     input[0] = '(';
     input[1] = 'a';
     input[2] = '+';
     input[3] = 'b';
     input[4] = ')';
     input[5] = '\0';
     */
    
    if(strcmp(input2, "infix") == 0)
    {
        cout << input;
    }
    
    else if (strcmp(input2, "postfix") == 0)
    {
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
            else if (isdigit(input[i]))
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
                
                /*
                 
                 while (peek() == '+' || peek() == '-' || peek() == '*'|| peek() == '/' || peek() == '^')
                 {
                 if (findPrecedence(peek()) > findPrecedence(input[i]))
                 {
                 enqueue(pop());
                 }
                 else
                 break;
                 }*/
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
        }// if the stack is empty then add to queue
        while(!isStackEmpty())
            enqueue(pop());
        
        
        printQueue();
        
        return 0;
    }
    else if(strcmp(input2, "prefix") == 0)
    {
        
    }
    
    else
    {
        cout << "invalid command, check spelling" << endl;
    }
}

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
} // delete from queue
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
} // show front of the queue
void showFirst()
{
    if (isQueueEmpty() == true)
    {
        cout << "The queue is empty." << endl;
    }
    else
    {
        cout << front -> QueueData;
    }
} // prints queue
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
void clearStack()
{
    while (isStackEmpty() == false)
    {
        pop();
    }
}
// assigns precidence to each of the operators
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
