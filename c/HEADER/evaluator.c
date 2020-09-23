#include "evaluator.h"
#include <string.h>
#include "symbol_table.h"
#include <stdio.h>

//visitor
void visitor_evaluate(ast_l *ast_list, error_list* err_list){

	symbol_table *table = new_symbol_table();

	symbol *s;

	ast *t_ast = ast_list->root_node;

	char *asm_code = calloc(1000, sizeof(char));

	//char *temp_asm_code = calloc(1, sizeof(char));

	while(t_ast != NULL){

		if( strncmp(t_ast->type, "AST_VAR_DEF_ASSIGNMENT", 22) == 0){
			
			s = new_var_symbol( t_ast->var_def_var_name,
								t_ast->var_def_var_content,
								"T_IDENTIFIER");

			add_new_symbol(table, s);
			
		}else if( strncmp(t_ast->type,"AST_BUILTIN_FUNCTION_CALL",26) == 0 ){

			if(is_builtin_function(t_ast->function_name) == 1){

				if(strncmp(t_ast->function_name,"output",6) == 0){

					function_args *first_arg = t_ast->args_list->first_arg;
					function_args *second_arg = t_ast->args_list->last_arg;
				
					if(strncmp(first_arg->arg_type,"T_IDENTIFIER",12) == 0){
						
						if(strncmp(second_arg->arg_name,"HIGH", 4) == 0){

							s = search_symbol(table, first_arg->arg_name);

							if(s != NULL){
							
								if(strncmp(s->value,"13", 2) == 0){

									strncat(asm_code,"\tsbi DDRB, 5\n", 14);
									strncat(asm_code, "\tsbi PortB, 5\n", 15);
				
								}else if(strncmp(s->value,"12", 2) == 0){
								
									strncat(asm_code,"\tsbi DDRB, 4\n", 14);
									strncat(asm_code, "\tsbi PortB, 4\n", 15);

								}else if(strncmp(s->value,"11", 2) == 0){

									strncat(asm_code,"\tsbi DDRB, 3\n", 14);
									strncat(asm_code, "\tsbi PortB, 3\n", 15);

								}else if(strncmp(s->value,"10", 2) == 0){
								
									strncat(asm_code,"\tsbi DDRB, 2\n", 14);
									strncat(asm_code, "\tsbi PortB, 2\n", 15);

								
								}else if(strncmp(s->value,"9", 1) == 0){

									strncat(asm_code,"\tsbi DDRB, 1\n", 14);
									strncat(asm_code, "\tsbi PortB, 1\n", 15);

								}else{
									
									char *err_msg = calloc(1,sizeof(char));

									size_t err_msg_len = 31 + strlen(s->value);

									snprintf(err_msg, err_msg_len, "Pin %s not present in atmega328p\n", s->value);

									error *e = new_error(err_msg, t_ast->ast_node_index);

									add_new_error(err_list,e);

								}
							
							}else{

								char *err_msg = calloc(1,sizeof(char));

								size_t err_msg_len = 21 + strlen(s->name);

								snprintf(err_msg, err_msg_len, "Symbol %s not declared\n", t_ast->args_list->first_arg->arg_name);

								error *e = new_error(err_msg, t_ast->ast_node_index);

								add_new_error(err_list,e);

							}
						}//implement LOW
					}//first argument CONSTANT
				}//input //wait
			}//user defined funciton
		}//other asts

		t_ast = t_ast->next_ast_node;

	}

	if(err_list->error_index > 0){
		print_errors(err_list);
		exit(0);
	}else{
		
		FILE *f = fopen("code.asm","w+");

		fprintf(f,";**************************************************\n"
				  ";*                                                *\n"
				  ";*     THIS IS CODE GENERATED AUTOMATICALLY       *\n"
				  ";*                 BY COMPILER                    *\n"
				  ";*                                                *\n"
				  ";**************************************************\n\n\n");

		fprintf(f,".include \"./m328Pdef.inc\"\n\n\n");

		fprintf(f, "start:\n");

		fprintf(f, "%s", asm_code);

		fprintf(f,"\trjmp start\n");

		fclose(f);

		free(asm_code);

	}

}
