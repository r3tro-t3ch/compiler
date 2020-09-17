#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN{

	struct TOKEN *next_token;
	struct TOKEN *prev_token;

    char *type;
    char *content;
    
} token;
    
//creating a new token
token* new_token(char *type, char *content);
#endif
