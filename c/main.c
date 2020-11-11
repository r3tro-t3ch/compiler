#include <stdlib.h>
#include <string.h>
#include "HEADER/compiler.h"
#include "HEADER/error.h"
#include "HEADER/symbol_table.h"
#include "HEADER/evaluator.h"
#include <stdio.h>


int main(int argc, char *argv[]){

	if( argc == 2 ){

		char *code;
		size_t code_len;
		int i;
		FILE *file = fopen(argv[1], "r");

		if( file ){

			fseek(file, 0, SEEK_END);
			code_len = ftell(file);
			fseek(file, 0, SEEK_SET);


			code = calloc(code_len, sizeof(char) + 1);
/*
			fread(code, sizeof(char), code_len, file);

			code[code_len] = '\0';
	
			fclose(file);

		*/
			
			i = 0;
			char c;

			while((c = fgetc(file)) != EOF){

				if(c == '\n'){

					code [i] = '\n';
					i++;
					continue;

				}

				code[i] = (char)c;
				i++;

			}

			code[i] = '\0';

		}else{

			fprintf(stderr, "error reading file %s \n", argv[1]);
			exit(1);

		}

		printf("%s \n", code);
		printf("code size -> %d\n", i);
		lexer *l = new_lexer(code);

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

	}else{

		fprintf(stdout, "usage : %s <file>\n", argv[0]);

	}
	return 0;
}
