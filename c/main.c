#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "HEADER/compiler.h"
#include "HEADER/error.h"
#include "HEADER/symbol_table.h"
#include "HEADER/evaluator.h"

int main(int argc, char *argv[]){

	lexer *l = new_lexer(
		"var c = 1\n"
		"var b = 12\n"
		"var a = c + b * 5 - 50\n"
		"output(a, HIGH)\n"
		"\0" );

	parser *p = new_parser(l);

	error_list *err_list = new_error_list();	
		
	ast_l *ast_list = parse_statements(p, err_list);	

	if(err_list->error_index > 0){

		print_errors(err_list);

	}else{

		//print_ast(ast_list);
		visitor_evaluate(ast_list, err_list);
		//print_symbol_table(table);

	}

	return 0;
}
