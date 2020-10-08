#include <stdlib.h>
#include "token.h"

//creating a new token
token* new_token(char *type, char *content){

	token *t = calloc(1, sizeof(token));
	
	t->next_token = NULL;
	t->prev_token = NULL;
    t->type = type;
    t->content = content;
    
	return t;
}

