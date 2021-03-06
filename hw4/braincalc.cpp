/*
  Programmer: Innocent Niyibizi
  File: braincalc.cpp
  Date: 3/5/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Main to read in brain input and output the corresponding value
*/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "astack.h"
#include <string>
#include <cctype>

using namespace std;

struct Operator
{
    string op;
    int precedence;
};

const short MAXSIZE = 5;
const string OPENING[MAXSIZE] = {"(","[","{"};
const string CLOSING[MAXSIZE] = {")","]","}"};
const Operator OPERATORS[MAXSIZE] = {{"+",0},{"-", 0},{"*", 1},{"/", 1},{"%", 1}};

int findPos(const string val, const string arr[])
{
  for(int i=0; i<MAXSIZE; i++)
  {
    if(arr[i]==val)
    {
      return i;
    }
  }
  return -1;
}

bool findPos(const string val, const Operator arr[])
{
  for(int i=0; i<MAXSIZE; i++)
  {
    if(arr[i].op == val)
      return true;
  }
  return false;
}

Operator findOperator(const string opCurr)
{
  for(int i=0; i<MAXSIZE; i++)
  {
    if(OPERATORS[i].op == opCurr)
    {
      return OPERATORS[i];
    }
  }
  return OPERATORS[0];
}

bool arePair(char opening, char closing)
{
  if(opening =='(' && closing ==')')
    return true;
  else if(opening == '[' && closing ==']')
    return true;
  else if(opening == '{' && closing == '}')
    return true;
  else
    return false;
}

int calculate(const int left, const int right, string op)
{
  int result = 0;
  switch(op[0])
  {
    case '+':
      result = left+right;
      break;
    case '-':
      result = left-right;
      break;
    case '*':
      result = left*right;
      break;
    case '/':
      if(right==0)
        throw Oops("INVALID!");
      else
        result = left/right;
      break;
    case '%':
      if(right==0)
        throw Oops("INVALID!");
      else
        result = left%right;
      break;
  }
  return result;
}

void AreBalance(string express)
{
  AStack<char> brackets;
  for(unsigned int i =0; i < express.length(); i++)
  {
    if(express[i] == '(' || express[i] == '{' || express[i] == '[')
      brackets.push(express[i]);
    else if(express[i] == ')' || express[i] == '}' || express[i] == ']')
    {
      if(!brackets.isEmpty() && arePair(brackets.top(), express[i]))
        brackets.pop();
    }
  }
  if(!brackets.isEmpty())
    throw Oops(": INVALID!");
  return;
}

string convert(string equation)
{
  AStack<string> operators;
  AStack<string> tokens;
  bool opUsed = false;
  string expression, tempStr, newExpression ="", prev;
  istringstream inputstr(equation);

  while (inputstr.peek()!=-1)
  {
    inputstr>>tempStr;
    if(findPos(tempStr, OPENING) != -1)
    {
      if(isdigit(prev[0]))
      {
        throw Oops(": INVALID!");
      }
      else
      {
        tokens.push(tempStr);
        prev = tempStr;
        opUsed = false;
      }
    }
    else if(findPos(tempStr, CLOSING) != -1)
    {
      if(!opUsed)
      {
        throw Oops(": INVALID!");
      }
      if(findPos(tokens.top(), OPENING) != -1)
      {
        tokens.pop();
      }
      else
      {
        while(findPos(tokens.top(), OPENING) == -1)
        {
         if(findPos(tokens.top(), OPENING) == -1 &&
            findPos(tokens.top(), CLOSING) == -1)
            {
              newExpression+=tokens.top()+" ";
              tokens.pop();
            }
        }
        tokens.pop();
      }
    }
    else if(findPos(tempStr, OPERATORS))
    {
      Operator curr = findOperator(tempStr);
      if(findPos(prev, OPERATORS))
      {
        throw Oops(": INVALID!");
      }
      else if(curr.precedence < findOperator(tokens.top()).precedence)
      {
        newExpression+=tokens.top()+" ";
        tokens.pop();
      }
      tokens.push(curr.op);
      prev = curr.op;
      opUsed = true;
    }
    else
    {
      if(isdigit(prev[0]))
      {
        throw Oops(": INVALID!");
      }
      if(tempStr.length()>=2)
      {
        if(isdigit(tempStr[0]) && isdigit(tempStr[1]))
        {
          newExpression+=tempStr+" ";
          prev = tempStr;
        }
      }
      else if(isdigit(tempStr[0]))
      {
        newExpression+=tempStr+" ";
        prev = tempStr;
      }
      else
      {
        throw Oops(": INVALID!");
      }
    }
  }
  //Clearing operators stack
  while(!operators.isEmpty())
  {
    newExpression+=operators.top()+" ";
    operators.pop();
  }
  if(tokens.isEmpty())
    return newExpression;
  else
    throw Oops (": INVALID!");

}

void compute(string expression, const int count)
{
  AStack<int> nums;
  string tempStr;
  int num1, num2;
  istringstream input(expression);
  while(input.peek()!=-1)
  {
    input>>tempStr;
    if(findPos(tempStr, OPERATORS))
    {
      num1 = nums.top();
      nums.pop();
      if(nums.isEmpty())
      {
        nums.push(num1);
      }
      else
      {
        num2 = nums.top();
        nums.pop();
        nums.push(calculate(num2, num1, tempStr));
      }
    }
    else if(tempStr!=" ")
    {
      nums.push(atoi(tempStr.c_str()));
    }
  }
  cout<<"#"<<count<<" : "<<nums.top()<<endl;
  return;
}

int main()
{
  AStack<int> nums;
  string expression, tempStr, newExpression;
  int counter = 1;
  char temp = cin.peek();
  while (temp!='.')
  {
    try
    {
      getline(cin, expression);
      AreBalance(expression);
      newExpression = convert(expression);
      compute(newExpression, counter);
    }
    catch(...)
    {
      cout<<"#"<<counter<<" : INVALID!"<<endl;
    }
    counter++;
    temp = cin.peek();
  }

  return 0;
}
