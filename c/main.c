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
		"var a = 13\n"
		"var b = 12\n"
		"var c = 11\n"
		"var d = 10\n"

		"output(a, HIGH)\n"
		"wait(500)\n"
		"output(a, LOW)\n"
		"wait(500)\n"

		"output(b, HIGH)\n"
		"wait(1000)\n"
		"output(b, LOW)\n"
		"wait(1000)\n"

		"output(c, HIGH)\n"
		"wait(2000)\n"
		"output(c, LOW)\n"
		"wait(500)\n"


		"output(d, HIGH)\n"
		"wait(3000)\n"
		"output(d, LOW)\n"
		"wait(3000)\n"


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
