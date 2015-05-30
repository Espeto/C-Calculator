//Calculator that operates and returns values with one decimal place.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib_org.h"

void tokenList(char *list, char *string);
int analiser(char *string);
void inToPos(celula *stack, celula *headQueue, celula *tailQueue, char *list);
void calculate(celula *stack, celula *headQueue);

int main(){
	char str[41], list[41];
	celula *stack, *headQueue, *tailQueue;
	int verify, i;
	
	do{
		//Start Stack, headQueue, tailQueue
		stack = start();
		headQueue = start();
		tailQueue = start();
		
		//Puts '/0' in each space of the vectors
		for (i = 0; i < 41; i++)
		{
			list[i] = '\0';
			str[i] = '\0';
		}
		
		
		printf(" === Enter the expression === \n");
		fflush(stdin);
		fgets(str, 41, stdin);
		
		//Transfer each token to array whithout space
		tokenList(list, str);
		
		verify = analiser(list);
		
		//Checks the validity of expression
		if(verify == -1){  
			printf("Invalid expression.\n");
		}
		
		else{
			//Transform infix expression to posfix expression
			printf("Change infix expression to posfix expression\n");
			printf("Press ENTER...");
			getchar();
			inToPos(stack,headQueue, tailQueue, list);
			
			//Start the calculation
			printf("Starting calculation\n");
			printf("Press ENTER...");
			getchar();
			calculate(stack, headQueue);
		}
	}while(str != '\0');

return 0;

}



int analiser(char *string){
	int i=0;
	
	//Only checks if the token is different from letter
	while(string[i] != '\0'){
		if((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z')){
				return -1;
		}
		
		i++;
	}
	
	return 1;
}

int checkDigit(char token){
	

	//Gives a precedence number to token
	if(token == '(') return 2;
	
	else if(token == ')') return 5;
	
	else if(token == '+' || token == '-') return 3;
	
	else if(token == '*' || token == '/') return 4;
	
	else return 1;
}

void tokenList(char *list, char *string){
	char *token;
	int i=0;
	
	//Takes the first token
	token = strtok(string, " ");
	
	while(token != NULL){
		list[i] =(char) *token; //Puts the token in a character vector at position [i]
		token = strtok(NULL, " ");//Pass to the second token
		i++;
	}
}

void inToPos(celula *stack, celula *headQueue, celula *tailQueue, char *list){
		int i=0;
		celula *topStack, *hQueue;
		
		
		
			//( = 2 / num = 1 / + AND - = 3 / * AND / = 4 , ) = 5
			while(list[i] != '\0'){
			//If token is an operator and is not parentheses
				if((checkDigit(list[i]) != 1) && (checkDigit(list[i]) != 2 && checkDigit(list[i]) != 5)){
					//While not empty stack and precedence of top stack > precedence of caracter in list
					while(stack->prox != NULL && (checkDigit(top(stack)) >= checkDigit(list[i]))){
						
						//Enqueue top stack
						enqueue(headQueue,tailQueue, top(stack));
						pop(stack);//Remove it from the top
						
					}
					
					
					push(stack, list[i]);//Puts the caracter on the top of stack
					
				}
				
				else{
					//If operator is parentheses
					if(checkDigit(list[i]) == 2 || checkDigit(list[i]) == 5){
						if(checkDigit(list[i]) == 5){//If operator is closes parentheses
							while(checkDigit(top(stack)) != 2){//While top stack is not open parentheses
								enqueue(headQueue,tailQueue, top(stack));//Enqueue top stack
								pop(stack);//Remove it from the top
							
							}
							pop(stack);//Just discard the open parentheses
						}
						
						else{//If not closes parentheses put it on the stack
							push(stack, list[i]);
						}
					
					}
				
					else{//If not parentheses enqueue the caracter
						enqueue(headQueue,tailQueue, list[i]);
					}
				}
				
				i++;//Increment control vector variable
				
			}
	
	//Removes the last operand from the stack
	enqueue(headQueue,tailQueue, top(stack));
	pop(stack);
	
	topStack = stack->prox;
	hQueue = headQueue -> prox;
	
	printf("Heap\n");
	
	while(topStack != NULL){
				printf("%c ", topStack -> cont);
				topStack = topStack->prox;
			}
			
	printf("\n");
	printf("Queue\n");
			
	while(hQueue != NULL){
				printf("%c ", hQueue->cont);
				hQueue = hQueue->prox;
			}
			
	printf("\n");
}

void calculate(celula *stack, celula *headQueue){
	char token, z, y, x;
	int a, b, c;
	
	while (headQueue -> prox != NULL){
		token = dequeue(headQueue);
		
		if (checkDigit(token) == 1){//If token is operand
			push(stack, token);
		}
			
		else{  
			//If token is operator
			x = top(stack);
			pop(stack);
			y = top(stack);
			pop(stack);
			
			a = (int) (y) - 48;//Transform caracter to int
			b = (int) (x) - 48;
				
			if(token == '+') c = (a + b);
				
			else if(token == '-') c = (a - b);
				
			else if(token == '*') c = (a * b);
				
			else if(token == '/') {
				if(b != 0){
					c = (a / b);
				}
			}
			
			z = (char) (c+48);//Put the result as caracter in stack
			
			push(stack, z);
			
			
			}
	}
		
	printf("\n");
	printf ("Result = %c\n", top(stack)); 
}
