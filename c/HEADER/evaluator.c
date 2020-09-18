#include "evaluator.h"
#include <string.h>
#include "symbol_table.h"
#include <stdio.h>

//visitor
void visitor_evaluate(ast_l *ast_list){

	symbol_table *table = new_symbol_table();

	symbol *s;

	ast *t_ast = ast_list->root_node;

	FILE *f = fopen("code.asm","w+");

	fprintf(f,".include \"./m328Pdef.inc\"\n");

	while(t_ast != NULL){


		if( strncmp(t_ast->type, "AST_VAR_DEF_ASSIGNMENT", 22) == 0){
			
			s = new_var_symbol( t_ast->var_def_var_name,
								t_ast->var_def_var_content,
								"T_CONSTANT");

			add_new_symbol(table, s);

		}else if( strncmp(t_ast->type,
						  "AST_BUILTIN_FUNCTION_CALL",
						  26) == 0 ){

			if(is_builtin_function(t_ast->function_name) == 1){

				if(strncmp(t_ast->function_name,"output",6) == 0){

					function_args *first_arg = t_ast->args_list->first_arg;
					function_args *second_arg = t_ast->args_list->last_arg;
				

					if(strncmp(first_arg->arg_type,"T_IDENTIFIER",12) == 0)
						if(strncmp(second_arg->arg_name,"HIGH", 4) == 0){
						if(search_symbol(table, first_arg->arg_name) != NULL){
							s = search_symbol(table, first_arg->arg_name);


							if(strncmp(s->value,"13", 2) == 0){

								fprintf(f,"sbi DDRB, 5\n");
								fprintf(f, "sbi PortB, 5\n");

							}if(strncmp(s->value,"12", 2) == 0){

								fprintf(f,"sbi DDRB, 4\n");
								fprintf(f, "sbi PortB, 4\n");

							}if(strncmp(s->value,"11", 2) == 0){

								fprintf(f,"sbi DDRB, 3\n");
								fprintf(f, "sbi PortB, 3\n");

							}if(strncmp(s->value,"10", 2) == 0){

								fprintf(f,"sbi DDRB, 2\n");
								fprintf(f, "sbi PortB, 2\n");

							}if(strncmp(s->value,"9", 1) == 0){

								fprintf(f,"sbi DDRB, 1\n");
								fprintf(f, "sbi PortB, 1\n");

							}

						}	

					}

				}

			}

		}


		t_ast = t_ast->next_ast_node;

	}

	fprintf(f, "start:\n\trjmp start\n");

	fclose(f);
}
