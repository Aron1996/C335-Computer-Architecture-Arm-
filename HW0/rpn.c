/**********************************************************
* rpn.c
*
* rpn calculator act like post-fix calculator
*
* Author: Yaokun Zhang
* Date Created: Sep 2, 2017
* Last Modified by: Yaokun Zhang
* Date Last Modified: Sep 2, 2017
* Assignment: HW0
* Part of: C335 assignment
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct CELL* LIST;

struct CELL {
  int val;
  LIST next;
};

LIST stack;

void push(int val) {
  LIST c = (LIST) malloc(sizeof(struct CELL));
  if (c) {
    c->val = val;
    c->next = stack;
    stack = c;
  } else { exit(1); }
}

int pop(){
  LIST c = stack;
  int value;
  if(c){
    stack = stack->next;
    value = c->val;
    free(c);
    return value;
  }else {exit(1);}
}

int main(){
  stack = NULL;
  LIST temp;
  char input[300];
  while( *input != EOF && *input != 'q'){
    scanf("%s", input);
    int number = atoi(input);
    if( isdigit(input[0])){
    push(atoi(input));
    }else{
      switch(*input){
      case '+':
	if((stack != NULL) &&(stack->next != NULL)){
	  int first = pop();
	  int second = pop();
	  push(first + second);
	}else{
	  printf("dc: stack empty\n");
	}
	break;
	
      case '-':
	if((stack != NULL) &&(stack->next != NULL)){
	  int second = pop();
	  int first = pop();
	  push(first - second);
	}else{
	  printf("dc: stack empty\n");
	}break;

      case '*':
	if ((stack != NULL) &&(stack->next != NULL)){
	  int second = pop();
	  int first = pop();
	  push(first * second);
	} else {
	  printf("dc: stack empty\n");
	}
	break;
	
      case '/':
	if ((stack != NULL) &&(stack->next != NULL)) {
	  int second = pop();
	  int first = pop();
	  push(first / second);
	} else {
	  printf("dc: stack empty\n");
	}
	break;
       
      case 'p':
	if(stack != NULL){
	  printf("%d\n", stack->val);
	}else{
	  printf("dc: stack empty\n");
	}
	break;
	
      case 'f':
        temp = stack;
	while (temp != NULL){
	  printf("%d\n", temp->val);
	  temp = temp->next;
	}
	break;
	
      case 'c':
	while(stack != NULL){
	  pop();
	}	
	break;
      
      case 'q':
	break;
      }
    }
  }
}
