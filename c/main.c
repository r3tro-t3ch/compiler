#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "HEADER/compiler.h"


int main(int argc, char *argv[]){

	lexer *l = new_lexer(
		"var led = (5 + 7 - 4) * 3\n"
		"loop(true){\n"
        "output(led, HIGH)\n"
		"output(serial, \"On\")\n"
        "wait(1)\n"
        "output(led, LOW)\n"
		"output(serial, \"Off\")\n"
		"wait(1)\n"
		"}\0" );

	token **token_array = NULL;
	size_t token_count = 0;

	while(l->current_char != '\0'){

		if(l->current_char == SPACE || l->current_char == NEWLINE ){
		
			next_char(l);
		
		}

		if( isalnum( l-> current_char) ){

			char *identifier = get_identifier(l);

			if( isdigit(*identifier) ){
				
				token_array = realloc(token_array, (token_count + 1) * sizeof(token));
				token_array[token_count] = new_token("T_CONSTANT", identifier);
				token_count++;

			}else if( is_keyword(identifier) ){

				token_array = realloc(token_array, (token_count + 1) * sizeof(token));
				token_array[token_count] = new_token("T_KEYWORD", identifier);
				token_count++;

			}
			else{

				token_array = realloc(token_array, (token_count + 1) * sizeof(token));
				token_array[token_count] = new_token("T_IDENTIFIER", identifier);
				token_count++;

			}

		}

		switch(l->current_char){

			case '(':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_LPAREN", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case ')':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_RPAREN", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '{':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_LBRACE", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '}':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_RBRACE", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '+':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_PLUS", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '-':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_MINUS", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '*':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_ASTERIX", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '/':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_FSLASH", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '%':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_MOD", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '=':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_EQUAL", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '>':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_GREATER", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '<':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_LESSER", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case ',':{
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_COMMA", char_to_str(l->current_char));
						token_count++;
						break;
					 }
			case '"':{

						char *identifier = get_string(l);
											
						token_array = realloc(token_array, (token_count + 1) * sizeof(token));
						token_array[token_count] = new_token("T_STRING", identifier);
						token_count++;

					 }
		}

		next_char(l);

	}

	for(int i = 0; i < token_count; i++){
        fprintf(stdout," TOKEN    %s --> %s   \n",token_array[i]->type,token_array[i]->content);
    }


	return 0;
}
