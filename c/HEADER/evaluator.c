#include "evaluator.h"
#include <string.h>
#include "symbol_table.h"
#include <stdio.h>
#include <ctype.h>
#include "expression.h"

//atmega328p general purpose register set
static char *register_list[] = { 
	"r16",
	"r17",
	"r18",
	"r19",
	"r20",
	"r21",
	"r22",
	"r23",
	"r24",
	"r25",
	"r26",
	"r27",
	"r28",
	"r29",
	"r30",
	"r31",
	"r32"
};

static size_t register_index = 0;

size_t delay_code_flag = 0;

//registers
char* use_register(char *register_list[]){

	if(register_index == GENERAL_PURPOSE_REGISTER_COUNT){
		return NULL;
	}

	char *reg = register_list[register_index];

	register_index++;

	return reg;

}

//calculate delay
/*size_t calculate_delay(size_t delay_parameter){

	size_t delay_time;

	if(delay_parameter == 1){

		if(delay_parameter == 1){
			return 60;
		}

	}else{

	}

}*/

//visitor
void visitor_evaluate(ast_l *ast_list, error_list* err_list){

	symbol_table *table = new_symbol_table();

	symbol *s, *temp_s;

	ast *t_ast = ast_list->root_node;

	char *code_init = calloc(200, sizeof(char));
	char *asm_setup_code = calloc(1000, sizeof(char));
	char *asm_main_code = calloc(2000, sizeof(char));
	char *reset_code = calloc(200, sizeof(char));
	char *delay_function = NULL;
	char *timer_overflow_handler = calloc(200, sizeof(char));

	while(t_ast != NULL){

		if( strncmp(t_ast->type, "AST_VAR_DEF_ASSIGNMENT", 22) == 0){

			temp_s = search_symbol(table, t_ast->var_def_var_name);


			//checking if the give variable name is present or not
			//else raise an error

			if(temp_s == NULL){

				/*                IMPLEMENTING EXPRESSION EVAL                */

				token_list* list = t_ast->var_def_var_expr;

				char* answer = evaluate_expression_ast(list, err_list, table, t_ast->ast_node_index);

				if(answer != NULL){

					printf("ans = %s \n",  answer);

					s = new_var_symbol( t_ast->var_def_var_name,
										answer,
										"T_IDENTIFIER");

					add_new_symbol(table, s);

				}

			}else{

				size_t err_msg_len = strlen(t_ast->var_def_var_name) + ERR_MSG_VAR_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is already declared\n",
						 t_ast->var_def_var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}
			
		}/*else if( strncmp(t_ast->type, "AST_VAR_DEF_ASSIGNMENT_IDENTIFIER", 22) == 0){

			temp_s = search_symbol(table, t_ast->var_def_var_name);

			if(temp_s == NULL){

				symbol *t = search_symbol(table, t_ast->var_def_var_content);

				if(t != NULL){

					s = new_var_symbol( t_ast->var_def_var_name,
										t->value,
										"T_IDENTIFIER");

					add_new_symbol(table, s);

				}else{

					size_t err_msg_len = strlen(t_ast->var_def_var_content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

					char *err_msg = calloc(err_msg_len, sizeof(char));

					snprintf(err_msg, err_msg_len,
							 "variable %s is not declared\n",
							 t_ast->var_def_var_content);

					add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

				}

						
			}else{

				size_t err_msg_len = strlen(t_ast->var_def_var_name) + ERR_MSG_VAR_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is already declared\n",
						 t_ast->var_def_var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}

		}*/else if( strncmp(t_ast->type,"AST_BUILTIN_FUNCTION_CALL",26) == 0 ){

			if(is_builtin_function(t_ast->function_name) == 1){

				if(strncmp(t_ast->function_name,"output",6) == 0){

					function_args *first_arg = t_ast->args_list->first_arg;
					function_args *second_arg = t_ast->args_list->last_arg;
				
					if(strncmp(first_arg->arg_type,"T_IDENTIFIER",12) == 0){
					
						if(strncmp(second_arg->arg_name,"HIGH", 4) == 0){

							s = search_symbol(table, first_arg->arg_name);

							if(s != NULL){
							
								if(strncmp(s->value,"13", 2) == 0){

									strncat(asm_setup_code,"\tsbi DDRB, 5\n", 14);
									strncat(asm_main_code, "\tsbi PortB, 5\n", 15);
				
								}else if(strncmp(s->value,"12", 2) == 0){
								
									strncat(asm_setup_code,"\tsbi DDRB, 4\n", 14);
									strncat(asm_main_code, "\tsbi PortB, 4\n", 15);

								}else if(strncmp(s->value,"11", 2) == 0){

									strncat(asm_setup_code,"\tsbi DDRB, 3\n", 14);
									strncat(asm_main_code, "\tsbi PortB, 3\n", 15);

								}else if(strncmp(s->value,"10", 2) == 0){
								
									strncat(asm_setup_code,"\tsbi DDRB, 2\n", 14);
									strncat(asm_main_code, "\tsbi PortB, 2\n", 15);

								
								}else if(strncmp(s->value,"9", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRB, 1\n", 14);
									strncat(asm_main_code, "\tsbi PortB, 1\n", 15);

								}else if(strncmp(s->value,"8", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRB, 0\n", 14);
									strncat(asm_main_code, "\tsbi PortB, 0\n", 15);

								}else if(strncmp(s->value,"7", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRD, 7\n", 14);
									strncat(asm_main_code, "\tsbi PortD, 7\n", 15);

								}else if(strncmp(s->value,"6", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRD, 6\n", 14);
									strncat(asm_main_code, "\tsbi PortD, 6\n", 15);

								}else if(strncmp(s->value,"5", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRD, 5\n", 14);
									strncat(asm_main_code, "\tsbi PortD, 5\n", 15);

								}else if(strncmp(s->value,"4", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRD, 4\n", 14);
									strncat(asm_main_code, "\tsbi PortD, 4\n", 15);

								}else if(strncmp(s->value,"3", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRD, 3\n", 14);
									strncat(asm_main_code, "\tsbi PortD, 3\n", 15);

								}else if(strncmp(s->value,"2", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRD, 2\n", 14);
									strncat(asm_main_code, "\tsbi PortD, 2\n", 15);

								}else if(strncmp(s->value,"1", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRD, 1\n", 14);
									strncat(asm_main_code, "\tsbi PortD, 1\n", 15);

								}else if(strncmp(s->value,"0", 1) == 0){

									strncat(asm_setup_code,"\tsbi DDRD, 0\n", 14);
									strncat(asm_main_code, "\tsbi PortD, 0\n", 15);

								}else{
									
									char *err_msg = calloc(1,sizeof(char));

									size_t err_msg_len = 31 + strlen(s->value);

									snprintf(err_msg, err_msg_len, "Pin %s not present in atmega328p\n", s->value);

									error *e = new_error(err_msg, t_ast->ast_node_index);

									add_new_error(err_list,e);

								}
							
							}else{

								size_t err_msg_len = 21 + strlen(first_arg->arg_name);
								
								char *err_msg = calloc(err_msg_len,sizeof(char));

								snprintf(err_msg, err_msg_len, "Symbol %s not declared\n", t_ast->args_list->first_arg->arg_name);

								error *e = new_error(err_msg, t_ast->ast_node_index);

								add_new_error(err_list,e);

							}
						}else if(strncmp(second_arg->arg_name,"LOW", 3) == 0){

							//implement LOW

							s = search_symbol(table, first_arg->arg_name);

							if(s != NULL){
							
								if(strncmp(s->value,"13", 2) == 0){

									strncat(asm_main_code, "\tcbi PortB, 5\n", 15);
				
								}else if(strncmp(s->value,"12", 2) == 0){
								
									strncat(asm_main_code, "\tcbi PortB, 4\n", 15);

								}else if(strncmp(s->value,"11", 2) == 0){

									strncat(asm_main_code, "\tcbi PortB, 3\n", 15);

								}else if(strncmp(s->value,"10", 2) == 0){
								
									strncat(asm_main_code, "\tcbi PortB, 2\n", 15);
								
								}else if(strncmp(s->value,"9", 1) == 0){

									strncat(asm_main_code, "\tcbi PortB, 1\n", 15);

								}else if(strncmp(s->value,"8", 1) == 0){

									strncat(asm_main_code, "\tcbi PortB, 0\n", 15);

								}else if(strncmp(s->value,"7", 1) == 0){

									strncat(asm_main_code, "\tcbi PortD, 7\n", 15);

								}else if(strncmp(s->value,"6", 1) == 0){

									strncat(asm_main_code, "\tcbi PortD, 6\n", 15);

								}else if(strncmp(s->value,"5", 1) == 0){

									strncat(asm_main_code, "\tcbi PortD, 5\n", 15);

								}else if(strncmp(s->value,"4", 1) == 0){

									strncat(asm_main_code, "\tcbi PortD, 4\n", 15);

								}else if(strncmp(s->value,"3", 1) == 0){

									strncat(asm_main_code, "\tcbi PortD, 3\n", 15);

								}else if(strncmp(s->value,"2", 1) == 0){

									strncat(asm_main_code, "\tcbi PortD, 2\n", 15);

								}else if(strncmp(s->value,"1", 1) == 0){

									strncat(asm_main_code, "\tcbi PortD, 1\n", 15);

								}else if(strncmp(s->value,"0", 1) == 0){

									strncat(asm_main_code, "\tcbi PortD, 0\n", 15);

								}else{
									
									char *err_msg = calloc(1,sizeof(char));

									size_t err_msg_len = 31 + strlen(s->value);

									snprintf(err_msg, err_msg_len, "Pin %s not present in atmega328p\n", s->value);

									error *e = new_error(err_msg, t_ast->ast_node_index);

									add_new_error(err_list,e);

								}
							
							}else{

								size_t err_msg_len = 21 + strlen(first_arg->arg_name);

								char *err_msg = calloc(err_msg_len,sizeof(char));

								snprintf(err_msg, err_msg_len, "Symbol %s not declared\n", t_ast->args_list->first_arg->arg_name);

								error *e = new_error(err_msg, t_ast->ast_node_index);

								add_new_error(err_list,e);

							}
						}
					}else if(strncmp(first_arg->arg_type,"T_CONSTANT", 10) == 0){

						//first argument CONSTANT
					
						char *s = first_arg->arg_name;

						if(strncmp(second_arg->arg_name,"HIGH", 4) == 0){

							if(strncmp(s,"13", 2) == 0){

								strncat(asm_setup_code,"\tsbi DDRB, 5\n", 14);
								strncat(asm_main_code, "\tsbi PortB, 5\n", 15);
				
							}else if(strncmp(s,"12", 2) == 0){
								
								strncat(asm_setup_code,"\tsbi DDRB, 4\n", 14);
								strncat(asm_main_code, "\tsbi PortB, 4\n", 15);

							}else if(strncmp(s,"11", 2) == 0){

								strncat(asm_setup_code,"\tsbi DDRB, 3\n", 14);
								strncat(asm_main_code, "\tsbi PortB, 3\n", 15);

							}else if(strncmp(s,"10", 2) == 0){
								
								strncat(asm_setup_code,"\tsbi DDRB, 2\n", 14);
								strncat(asm_main_code, "\tsbi PortB, 2\n", 15);
								
							}else if(strncmp(s,"9", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRB, 1\n", 14);
								strncat(asm_main_code, "\tsbi PortB, 1\n", 15);

							}else if(strncmp(s,"8", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRB, 0\n", 14);
								strncat(asm_main_code, "\tsbi PortB, 0\n", 15);

							}else if(strncmp(s,"7", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRD, 7\n", 14);
								strncat(asm_main_code, "\tsbi PortD, 7\n", 15);

							}else if(strncmp(s,"6", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRD, 6\n", 14);
								strncat(asm_main_code, "\tsbi PortD, 6\n", 15);

							}else if(strncmp(s,"5", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRD, 5\n", 14);
								strncat(asm_main_code, "\tsbi PortD, 5\n", 15);

							}else if(strncmp(s,"4", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRD, 4\n", 14);
								strncat(asm_main_code, "\tsbi PortD, 4\n", 15);

							}else if(strncmp(s,"3", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRD, 3\n", 14);
								strncat(asm_main_code, "\tsbi PortD, 3\n", 15);

							}else if(strncmp(s,"2", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRD, 2\n", 14);
								strncat(asm_main_code, "\tsbi PortD, 2\n", 15);

							}else if(strncmp(s,"1", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRD, 1\n", 14);
								strncat(asm_main_code, "\tsbi PortD, 1\n", 15);

							}else if(strncmp(s,"0", 1) == 0){

								strncat(asm_setup_code,"\tsbi DDRD, 0\n", 14);
								strncat(asm_main_code, "\tsbi PortD, 0\n", 15);

							}else{
									
								char *err_msg = calloc(1,sizeof(char));

								size_t err_msg_len = 31 + strlen(s);

								snprintf(err_msg, err_msg_len, "Pin %s not present in atmega328p\n", s);

								error *e = new_error(err_msg, t_ast->ast_node_index);

								add_new_error(err_list,e);

							}
							

						}else if(strncmp(second_arg->arg_name,"LOW", 3) == 0){

							//implement LOW
							if(strncmp(s,"13", 2) == 0){

								strncat(asm_main_code, "\tcbi PortB, 5\n", 15);
			
							}else if(strncmp(s,"12", 2) == 0){
								
								strncat(asm_main_code, "\tcbi PortB, 4\n", 15);

							}else if(strncmp(s,"11", 2) == 0){

								strncat(asm_main_code, "\tcbi PortB, 3\n", 15);

							}else if(strncmp(s,"10", 2) == 0){
								
								strncat(asm_main_code, "\tcbi PortB, 2\n", 15);

							}else if(strncmp(s,"9", 1) == 0){

								strncat(asm_main_code, "\tcbi PortB, 1\n", 15);

							}else if(strncmp(s,"8", 1) == 0){

								strncat(asm_main_code, "\tcbi PortB, 0\n", 15);

							}else if(strncmp(s,"7", 1) == 0){

								strncat(asm_main_code, "\tcbi PortD, 7\n", 15);

							}else if(strncmp(s,"6", 1) == 0){

								strncat(asm_main_code, "\tcbi PortD, 6\n", 15);

							}else if(strncmp(s,"5", 1) == 0){

								strncat(asm_main_code, "\tcbi PortD, 5\n", 15);

							}else if(strncmp(s,"4", 1) == 0){

								strncat(asm_main_code, "\tcbi PortD, 4\n", 15);

							}else if(strncmp(s,"3", 1) == 0){

								strncat(asm_main_code, "\tcbi PortD, 3\n", 15);

							}else if(strncmp(s,"2", 1) == 0){

								strncat(asm_main_code, "\tcbi PortD, 2\n", 15);

							}else if(strncmp(s,"1", 1) == 0){

								strncat(asm_main_code, "\tcbi PortD, 1\n", 15);

							}else if(strncmp(s,"0", 1) == 0){

								strncat(asm_main_code, "\tcbi PortD, 0\n", 15);

							}else{
									
								char *err_msg = calloc(1,sizeof(char));

								size_t err_msg_len = 31 + strlen(s);

								snprintf(err_msg, err_msg_len, "Pin %s not present in atmega328p\n", s);

								error *e = new_error(err_msg, t_ast->ast_node_index);

								add_new_error(err_list,e);

							}
								
						}

					}
				}else if(strncmp(t_ast->function_name,"wait",4) == 0){

					//wait
			
					if(delay_code_flag == 0){
						char *reg = use_register(register_list);

						char *delay_counter = use_register(register_list);

						char *temp = use_register(register_list);

						sprintf(code_init, ".def overflow_counter = %s\n"
										   ".def delay_count = %s\n\n"
										   ".def temp = %s\n"
										   ".org 0x0000\n"
										   "rjmp reset\n\n"
										   ".org 0x0020\n"
										   "rjmp overflow_handler\n", reg, delay_counter, temp);

						reset_code = "\n\nreset:\n" 
									 "\tldi temp, 0b00000101\n"
									 "\tout TCCR0B, temp				;prescaling to 1024\n"
									 "\tldi temp, 0b00000001\n"
									 "\tsts TIMSK0, temp				;enabling timer interrupt\n"
									 "\tsei								;enabling global interrupt\n";


						delay_function = calloc(200, sizeof(char));
					
						delay_function = "\n\ndelay:\n"
										 "\tclr overflow_counter\n"
										 "\tsec_count:\n"
										 "\t\tcp overflow_counter, delay_count\n"
										 "\tbrne sec_count\n"
										 "\tret\n";
						
					//timer_overflow_handler = calloc(20, sizeof(char));

						timer_overflow_handler = "\n\noverflow_handler:\n"
											     "\tinc overflow_counter\n"
 												 "\tcpi overflow_counter, 61\n"
												 "\tbrne PC+2\n"
												 "\tclr overflow_counter\n"
												 "\treti\n";

							delay_code_flag = 1;
					}

					char *arg = (char*) t_ast->args_list->first_arg->arg_name;

					if( isdigit(*arg) ){

						int delay_time = atoi(arg);
						
						if(delay_time <= 1000){
							
							int calc_delay = (delay_time * 60)/1000;

							char *temp_code = calloc(10, sizeof(char));

							sprintf(temp_code,"\tldi delay_count, %d\n", calc_delay);
							strncat(asm_main_code, temp_code, strlen(temp_code));
							free(temp_code);
							strncat(asm_main_code,"\trcall delay\n",14);
						
						}else{

							int calc_delay = (delay_time * 60)/1000;
							
							int calc_delay_count =(int)calc_delay/60;

							strncat(asm_main_code,"\tldi delay_count, 60\n", 22);
							for(int i = 0;i < calc_delay_count;i++){	
								strncat(asm_main_code,"\trcall delay\n", 14);		
							}

						}
					}else{
					
						s = search_symbol(table, arg);

						if(s != NULL){

							if( isdigit(*s->value)){

//debug

								printf("%s\n", s->value);

								int delay_time = atoi(s->value);
						
								printf("int -> %d \n", delay_time);

								if(delay_time <= 1000){
								
									int calc_delay = (delay_time * 60)/1000;
	
									char *temp_code = calloc(10, sizeof(char));
	
									sprintf(temp_code,"\tldi delay_count, %d\n", calc_delay);
									strncat(asm_main_code, temp_code, strlen(temp_code));
									free(temp_code);
									strncat(asm_main_code,"\trcall delay\n",14);
							
								}else{
	
									int calc_delay = (delay_time * 60)/1000;
								
									int calc_delay_count =(int)calc_delay/60;

									strncat(asm_main_code,"\tldi delay_count, 60\n", 22);
									for(int i = 0;i < calc_delay_count;i++){	
										strncat(asm_main_code,"\trcall delay\n", 14);		
									}

								}

							}else{

								size_t err_msg_len = 29 + strlen(s->value);

								char *err_msg = calloc(err_msg_len,sizeof(char));

								snprintf(err_msg, err_msg_len, "%s is not valid wait parameter\n",arg);

								error *e = new_error(err_msg, t_ast->ast_node_index);

								add_new_error(err_list,e);

							}
						}else{

							size_t err_msg_len = 21 + strlen(s->name);

							char *err_msg = calloc(err_msg_len,sizeof(char));

							snprintf(err_msg, err_msg_len, "Symbol %s not declared\n", s->name);

							error *e = new_error(err_msg, t_ast->ast_node_index);

							add_new_error(err_list,e);

						}

					}
				
				}//input
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

		if(delay_function != NULL){
			fprintf(f,"%s", code_init);
			fprintf(f,"%s", reset_code);
		}

		fprintf(f,"\nsetup:\n");

		fprintf(f,"%s", asm_setup_code);

		fprintf(stdout,"%s", asm_setup_code);

		fprintf(f,"\n\n");

		fprintf(f, "main:\n");

		fprintf(f, "%s", asm_main_code);

		fprintf(f,"\n\nend:\n");

		fprintf(f, "\trjmp end\n");
 
		if(delay_function != NULL){
			fprintf(f,"%s",delay_function);
			fprintf(f,"%s", timer_overflow_handler);
		}

		fclose(f);

		free(asm_setup_code);

		free(asm_main_code);

		free(code_init);
		
		//free(reset_code);

		//free(timer_overflow_handler);


	//		free(delay_function);

	}

}


