#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "HEADER/compiler.h"
#include "HEADER/error.h"

int main(int argc, char *argv[]){

	lexer *l = new_lexer(
		"var led  =3\n"
		"var c\n"
		//"output(led, HIGH)\n"
		"\0" );

	parser *p = new_parser(l);

	ast_l *ast_list = new_ast_list();

	error_list *err_list = new_error_list();

	get_next_token(p);

	while(strncmp(get_current_token(p)->type, "T_NULL", 6) != 0 ){

		if(strncmp(get_current_token(p)->type, "T_NULL", 6) == 0){

			break;

		}
		if( strncmp(get_current_token(p)->type, "T_NEWLINE", 10) == 0 ){

			parse_newline(p, err_list, ast_list);

		}
		if( strncmp(get_current_token(p)->type, "T_KEYWORD", 10) == 0){

			if( strncmp(get_current_token(p)->content, "var", 3) == 0){
	
				ast* node = parse_var_def(p, err_list, ast_list);
			
				if(node != NULL){
				
					add_new_ast(ast_list, node);

				}
			}
		}

		get_next_token(p);

	}

	if(err_list->error_index > 0){

		print_errors(err_list);

	}else{

		print_ast(ast_list);

	}

	return 0;
}
