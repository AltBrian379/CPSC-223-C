//
//  main.c
//  rpn
//
//  Created by William McCarthy on 192//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP   100    /* max size of operand/operator */
#define NUMBER '0'     /* signal that a number was found */
#define MATH '2'
#define MAXVAL  100
#define VARIABLE '3'

#define ENGLISHALPHA 26 // only 26 alphabetical letters
size_t sp = 0;   // aka unsigned long -- printf using %zu
double val[MAXVAL];   // stack of values
double variables[ENGLISHALPHA]; // where we will store our variables

char buf[BUFSIZ];
size_t bufp = 0;

int getch_(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch_(int c) {
  if (bufp >= BUFSIZ) { fprintf(stderr, "ungetch: too many characters\n");  return; }
  buf[bufp++] = c;
}



int getop(char* s) {
  int i, c;
  while ((s[0] = c = getch_()) == ' ' || c == '\t') { }  // skip whitespace
  s[1] = '\0';

  i = 0;
  if (isalpha(c)) // is it a character
  {
      while (islower(s[++i] = c = getch_())) {} // we get all the characters in the string available as long as its lower
      s[i] = '\0'; // ending flag
      if (c != EOF) // if its not the eof, get rid of a character since we took 1 too many
          ungetch_(c);
      if (strlen(s) > 1) // If its a string, we know it is a mathmatical operations (sin, cos, pow, exp)
          return MATH;
      else if (strlen(s) == 1) //if it is just a character, then we return the flag for it as a variable
          return VARIABLE;
      else
          return c; // otherwise return what we have
  }
  if (!isdigit(c) && c != '.' && c != '-') { return c; }  // if not a digit, return
  if (c == '-')
  {
      if (isdigit(c = getch_()) || c == '.')
          s[++i] = c;
      else {
          if (c != EOF)
              ungetch_(c);
          return '-';
      }
  }

  
  if (isdigit(c)) {  // get digits before '.'
    while (isdigit(s[++i] = c = getch_())) { }
  }
  if (c == '.') {    // get digits after decimal (if any)
    while (isdigit(s[++i] = c = getch_())) { }
  }
  s[i] = '\0';
  if (c != EOF) { ungetch_(c); }
  return NUMBER;      // return type is NUMBER, number stored in s
}

double pop(void) {
  if (sp == 0) { fprintf(stderr, "stack underflow\n");  return 0.0; }
  return val[--sp];
}

void push(double f) {
  if (sp == MAXVAL) { fprintf(stderr, "stack overflow -- can't push %g\n", f);  return; }
  val[sp++] = f;
}

void mathlib(char s[]) // uses std library to perform math functions
{
    double op2;
    if (strcmp(s, "sin") == 0) // checks to make sure that the string given is equal to the string established
    {
        push(sin(pop()));
    }
    else if (strcmp(s, "cos") == 0)
    {
        push(cos(pop()));
    }
    else if (strcmp(s, "exp") == 0)
    {
        push(exp(pop()));
    }
    else if (strcmp(s, "pow") == 0)
    {
        op2 = pop();
        push(pow(pop(), op2));
    }
    else
        printf("error: %s is not valid\n", s);
}
void variable(char* s) // Upper case stores, lower case retrieves it.
{
    if (isupper(*s))
    {
        variables[*s - 'A'] = pop(); // if uppercase, we store it
    }
    else if (islower(*s))
    {
         push(variables[toupper(*s) - 'A']); // if lowercase we use it
    }
   
}

void rpn(void) {
  int type, i, var = 0;
  double op2, op3, v;
  char s[BUFSIZ];

  
  while ((type = getop(s)) != EOF) {
      switch (type) {
      case '\n':
         
          printf("\t%.8g\n", pop());  break;
      case NUMBER:  push(atof(s));              break;
      case '+':     push(pop() + pop());        break;
      case '*':     push(pop() * pop());        break;
      case '-':     push(-(pop() - pop()));     break;
      case '/':
          if ((op2 = pop()) == 0.0) { fprintf(stderr, "divide by zero\n");  break; }
          push(pop() / op2);
          break;
      case '%': // modulous
          if ((op2 = pop()) == 0.0) { fprintf(stderr, "divide by zero\n"); break; }
          push((int)pop() % (int)op2);
          break;
      case '?': // prints without popping
          op2 = pop();
          printf("\t%.8g\n", op2);
          push(op2); 
          break;
      case '@': //clears the stack
          sp = 0;
          break;
      case '&': // Duplicates
          op2 = pop();
          push(op2); push(op2);
          break;
      case '^': // Swaps the top 2
          op2 = pop();
          op3 = pop();
          push(op2); push(op3);
          break;
      case MATH: // if this flag is activated we call the mathlib function
          mathlib(s);
          break;
      case VARIABLE: // if this flag is activated we call the variable function
          variable(s);
          break;

      default:

              fprintf(stderr, "unknown command %s\n", s); 
              break;
          
      }

  }
}



int main(int argc, const char * argv[]) {
  rpn();

  return 0;
}
