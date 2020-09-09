#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "HEADER/compiler.h"
#include "HEADER/error.h"

int main(int argc, char *argv[]){

	lexer *l = new_lexer(
		"var led = 13\n"
		"var l = 12\n"
		//"output(led, HIGH)\n"
		"\0" );

	parser *p = new_parser(l);
	ast *root = new_ast("AST_HEAD");

	error_list *err_list = new_error_list();

	get_next_token(p);

	while( strncmp(get_current_token(p)->type, "T_NULL", 6) != 0){


		if(strncmp(get_current_token(p)->type, "T_NULL", 6) == 0){

			break;

		}

		if( strncmp(get_current_token(p)->type, "T_NEWLINE", 10) == 0 ){

			get_next_token(p);
			root->code_size++;

		}
		if( strncmp(get_current_token(p)->type, "T_KEYWORD", 10) == 0){

			parser_eat(get_current_token(p), "T_KEYWORD", err_list, root);

			if( strncmp(get_current_token(p)->content, "var", 3) == 0){
	
				root->next = new_ast("AST_VAR_DEF");
		
				get_next_token(p);
	
				parser_eat(get_current_token(p), "T_IDENTIFIER", err_list, root);
				root->next->var_def_var_name = get_current_token(p)->content;
				
				token *t = peek_next_token(p);
				if( strncmp(t->type, "T_EQUAL", 7) == 0){
					get_next_token(p);
					root->next->type = "AST_VAR_DEF_ASSIGNMENT";
					parser_eat(get_current_token(p), "T_EQUAL", err_list, root);
	
					get_next_token(p);
					parser_eat(get_current_token(p), "T_CONSTANT", err_list, root);
					root->next->var_def_var_content = get_current_token(p)->content;
					get_next_token(p);
				}else{

					get_next_token(p);

				}
			}

			continue;

		}

	}

	if(err_list->error_index > 0){

		print_errors(err_list);

	}else{
	
		fprintf(stdout,"%s \n", root->next->type);
		fprintf(stdout, "%ld, %s", root->code_size, root->type);

	}


	return 0;
}
