#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cel {
	char cont;
	struct cel *prox;
	};

typedef struct cel celula;

void push(celula *h, char v);
void pop(celula *h);
char top(celula *h);
void enqueue (celula *h, celula *t, char v);
char dequeue(celula *h);
celula *start(void);

celula *start(void){
	celula *start;
	
	start = malloc(sizeof(celula));
	start->prox = NULL;
	
	return start;
}

void push(celula *h, char v){
	celula *nova, *ini;
	
	ini = h;
	
	nova = malloc(sizeof(celula));
	nova -> cont = v;
	
	nova->prox = ini->prox;
	ini->prox = nova;
	
}

void pop(celula *h){
	celula *f;
	
	f = h->prox;
	
	if(f != NULL){
		h -> prox = f -> prox;
		free(f);
	}	
}

char top(celula *h){
	celula *n;
	
	n = h->prox;
	
	return n -> cont;
}

void enqueue (celula *h, celula *t, char v){
	celula *new, *aux;
	
	new=malloc(sizeof(celula));
	new->cont=v;
	
	if(t->prox != NULL){
		aux=t->prox;
		aux->prox=new;
		new->prox=NULL;
		t->prox=new;
	}
	else{
		t->prox=new;
		new->prox = NULL;
	}
	
	if(h->prox == NULL){
		h->prox=new;
	}
}

char dequeue(celula *h){
	celula *f;
	char token;
	
	f = h -> prox;
	token = f->cont;	
	
	if(f != NULL){
		h -> prox = f -> prox;
		free(f);
	}
	
	return token;	
}
