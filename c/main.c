#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "HEADER/compiler.h"
#include "HEADER/error.h"
#include "HEADER/symbol_table.h"


int main(int argc, char *argv[]){

	lexer *l = new_lexer(
		//"var led 12\n"
		"var l=  1\n"
		"var a \n"
		"a = l\n"
		//"led = \n" 
		//"output(led, HIGH)\n"
		//"wait(1)\n"
		//"output(led, LOW)\n"
		//"wait(1)\n"
		"\0" );

	parser *p = new_parser(l);

	ast_l *ast_list = new_ast_list();

	error_list *err_list = new_error_list();

	//symbol_table *table = new_symbol_table();

	get_next_token(p);

	while(strncmp(get_current_token(p)->type, "T_NULL", 6) != 0 ){


		if( strncmp(get_current_token(p)->type, "T_KEYWORD", 10) == 0){

			if( strncmp(get_current_token(p)->content, "var", 3) == 0){
	
				ast* node = parse_var_def(p, err_list, ast_list);
			
				if(node != NULL){
				
					add_new_ast(ast_list, node);


				}
			}
		}else if(strncmp(get_current_token(p)->type, "T_IDENTIFIER", 12) == 0){

			token *t = peek_next_token(p);

			if( strncmp(t->type, "T_EQUAL", 7) == 0 ){

				ast *node = parse_var_assignment(p, err_list, ast_list);
	
				if(node != NULL){
				
					add_new_ast(ast_list, node);
			
				}

			}else if( strncmp(t->type, "T_LPAREN", 8) == 0 ){

				ast *node = parse_function_call(p, err_list, ast_list);

				if( node != NULL ){

					add_new_ast(ast_list, node);

				}

			}else{
				parse_newline(p, err_list, ast_list);
			}

			

		}

		if(strncmp(get_current_token(p)->type, "T_NULL", 6) == 0){

			break;

		}

		if( strncmp(get_current_token(p)->type, "T_NEWLINE", 10) == 0 ){

			parse_newline(p, err_list, ast_list);

		}

		get_next_token(p);

	}

	if(err_list->error_index > 0){

		print_errors(err_list);

	}else{

		print_ast(ast_list);
//		print_symbol_table(table);

	}

	return 0;
}
