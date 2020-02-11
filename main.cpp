#include <iostream>
#include <cstring>

using namespace std;


struct Stack
{
  int StackData; 

  Stack *StackLink; 
};

bool isStackEmpty();
void StackPush(int value);
void pop();
void peak(); 

Stack *top = NULL; 

struct Queue
{
  int QueueData;

  Queue *QueueLink; 
};

bool isQueueEmpty();
void enqueue(int value);
void dequeue();
void showFirst();
void printQueue(); 
  
Queue *front = NULL;
Queue *rear = NULL;

int main()
{
  char input[50]; 
  cout << "Please input an equation." << endl;
  cin.get(input, 50);
  cin.clear();
  cin.ignore(100000, '\n');

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

void StackPush(int value)
{
  Stack *ptr = new Stack();
  ptr -> StackData = value;
  ptr -> StackLink = top;
  top = ptr;
}

void pop()
{
  if(isStackEmpty() == true)
    {
      cout << "The stack is empty" << endl;
    }
  else
    {
      Stack *ptr = top;
      top = top -> StackLink;
      delete(ptr);
    }
}

void peak()
{
  if (isStackEmpty() == true)
    {
      cout << "The stack is empty" << endl;
    }
  else
    {
      cout << "The element at the top is: " << top -> StackData;
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
}
void PrintQueue()
{
  if (isQueueEmpty() == true)
    {
      cout << "The queue is empty." << endl;
    }
  else
    {
      Queue *ptr = front;
      while(ptr != NULL)
        {
          cout << ptr -> QueueData << " ";
          ptr = ptr -> QueueLink;
        }
    }
}

