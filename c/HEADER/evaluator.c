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

//input function call code generation
void input_function_code_gen(char *reg, char *first_arg, code *asm_code, error_list *err_list, ast *t_ast){


	char *temp_reg = use_register(register_list);

	char *input_code = calloc(300, sizeof(char));

	char *s = first_arg;

	if(strncmp(s,"13", 2) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRB, 5\n", 14);
		
		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 32\n"
					"\tandi %s, 32\n"
					"\tsts %s, %s\n"
					, temp_reg, temp_reg, reg , temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));

		register_index--;

	}else if(strncmp(s,"12", 2) == 0){
								
		strncat(asm_code->asm_setup_code,"\tcbi DDRB, 4\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 16\n"
					"\tandi %s, 16\n"
					"\tsts %s, %s\n"
					, temp_reg, temp_reg, reg, temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));

		register_index--;

	}else if(strncmp(s,"11", 2) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRB, 3\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 8\n"
					"\tandi %s, 8\n"
					"\tsts %s, %s\n"
					,temp_reg, temp_reg ,reg, temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));

		register_index--;

	}else if(strncmp(s,"10", 2) == 0){
								
		strncat(asm_code->asm_setup_code,"\tcbi DDRB, 2\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 4\n"
					"\tandi %s, 4\n"
					"\tsts %s, %s\n"
					,temp_reg, temp_reg, reg, temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));
		
		register_index--;
							
	}else if(strncmp(s,"9", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRB, 1\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 2\n"
					"\tandi %s, 2\n"
					"\tsts %s, %s\n"
					,temp_reg, temp_reg, reg, temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));
		
		register_index--;

	}else if(strncmp(s,"8", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRB, 0\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 1\n"
					"\tandi %s, 1\n"
					"\tsts %s, %s\n"
					,temp_reg, temp_reg, reg, temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));
		
		register_index--;

	}else if(strncmp(s,"7", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRD, 7\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 128\n"
					"\tandi %s, 128\n"
					"\tsts %s, %s\n"
					,temp_reg, temp_reg, reg, temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));
		register_index--;

	}else if(strncmp(s,"6", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRD, 6\n", 14);
		register_index--;

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 64\n"
					"\tandi %s, 64\n"
					"\tsts %s, %s\n"
					,temp_reg, temp_reg, reg, temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));
		register_index--;

	}else if(strncmp(s,"5", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRD, 5\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 32\n"
					"\tandi %s, 32\n"
					"\tsts %s, %s\n"
					,temp_reg, temp_reg, reg, temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));
		register_index--;

	}else if(strncmp(s,"4", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRD, 4\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 16\n"
					"\tandi %s, 16\n"
					"\tsts %s, %s\n"
					,temp_reg,temp_reg, reg,temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));
		register_index--;

	}else if(strncmp(s,"3", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRD, 3\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s,  8\n"
					"\tandi %s,  8\n"
					"\tsts %s, %s\n"
					,temp_reg,temp_reg, reg,temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));
		register_index--;

	}else if(strncmp(s,"2", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRD, 2\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 4\n"
					"\tandi %s, 4\n"
					"\tsts %s, %s\n"
					,temp_reg,temp_reg, reg,temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));

		register_index--;
	}else if(strncmp(s,"1", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRD, 1\n", 14);

		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 2\n"
					"\tandi %s, 2\n"
					"\tsts %s, %s\n"
					,temp_reg,temp_reg, reg,temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));

		register_index--;

	}else if(strncmp(s,"0", 1) == 0){

		strncat(asm_code->asm_setup_code,"\tcbi DDRD, 0\n", 14);
		
		sprintf(input_code,
					"\tnop\n"
					"\tin %s, 1\n"
					"\tandi %s, 1\n"
					"\tsts %s, %s\n"
					,temp_reg,temp_reg, reg,temp_reg);	
		
		strncat(asm_code->asm_main_code, input_code, strlen(input_code));

		register_index--;

	}else{
									
		char *err_msg = calloc(1,sizeof(char));

		size_t err_msg_len = 31 + strlen(s);

		snprintf(err_msg, err_msg_len, "Pin %s not present in atmega328p\n", s);

		error *e = new_error(err_msg, t_ast->ast_node_index);

		add_new_error(err_list,e);

	}
}

//evaluate input function call
void visitor_evaluate_input_funtion_call(char *reg,  ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table, symbol_table *parent_symbol_table){

	function_args *first_arg = t_ast->args_list->first_arg;

	symbol *s, *parent_s = NULL;

	if( strncmp(first_arg->arg_type, "T_IDENTIFIER", 12) == 0){

		s = search_symbol(table, first_arg->arg_name);

		if( parent_symbol_table != NULL ){

			parent_s = search_symbol(parent_symbol_table, first_arg->arg_name);

		}

		if( s != NULL && parent_s == NULL){

			input_function_code_gen(reg , s->value, asm_code, err_list, t_ast);

		}else if( parent_s != NULL && s == NULL ){

			input_function_code_gen(reg , parent_s->value, asm_code, err_list, t_ast);

		}else{

			size_t err_msg_len = 21 + strlen(first_arg->arg_name);
							
			char *err_msg = calloc(err_msg_len,sizeof(char));

			snprintf(err_msg, err_msg_len, "Symbol %s not declared\n", t_ast->args_list->first_arg->arg_name);

			error *e = new_error(err_msg, t_ast->ast_node_index);

			add_new_error(err_list,e);

		}

	}else if( strncmp(first_arg->arg_type, "T_CONSTANT", 12) == 0){

		input_function_code_gen(reg , first_arg->arg_name, asm_code, err_list, t_ast);

	}

}

//output function call code generation
void output_function_code_gen(char *value, char *second_arg, code *asm_code, error_list *err_list, ast *t_ast){

	if(strncmp(second_arg,"HIGH", 4) == 0){

		if(strncmp(value,"13", 2) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRB, 5\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortB, 5\n", 15);
				
		}else if(strncmp(value,"12", 2) == 0){
								
			strncat(asm_code->asm_setup_code,"\tsbi DDRB, 4\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortB, 4\n", 15);

		}else if(strncmp(value,"11", 2) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRB, 3\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortB, 3\n", 15);

		}else if(strncmp(value,"10", 2) == 0){
								
			strncat(asm_code->asm_setup_code,"\tsbi DDRB, 2\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortB, 2\n", 15);

								
		}else if(strncmp(value,"9", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRB, 1\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortB, 1\n", 15);

		}else if(strncmp(value,"8", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRB, 0\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortB, 0\n", 15);

		}else if(strncmp(value,"7", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRD, 7\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortD, 7\n", 15);

		}else if(strncmp(value,"6", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRD, 6\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortD, 6\n", 15);

		}else if(strncmp(value,"5", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRD, 5\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortD, 5\n", 15);

		}else if(strncmp(value,"4", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRD, 4\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortD, 4\n", 15);

		}else if(strncmp(value,"3", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRD, 3\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortD, 3\n", 15);

		}else if(strncmp(value,"2", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRD, 2\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortD, 2\n", 15);

		}else if(strncmp(value,"1", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRD, 1\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortD, 1\n", 15);

		}else if(strncmp(value,"0", 1) == 0){

			strncat(asm_code->asm_setup_code,"\tsbi DDRD, 0\n", 14);
			strncat(asm_code->asm_main_code, "\tsbi PortD, 0\n", 15);

		}else{
									
			char *err_msg = calloc(1,sizeof(char));

			size_t err_msg_len = 31 + strlen(value);

			snprintf(err_msg, err_msg_len, "Pin %s not present in atmega328p\n", value);

			error *e = new_error(err_msg, t_ast->ast_node_index);

			add_new_error(err_list,e);

		}
							
	}else if(strncmp(second_arg,"LOW", 3) == 0){

		//implement LOW
							
		if(strncmp(value,"13", 2) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortB, 5\n", 15);
				
		}else if(strncmp(value,"12", 2) == 0){
								
			strncat(asm_code->asm_main_code, "\tcbi PortB, 4\n", 15);

		}else if(strncmp(value,"11", 2) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortB, 3\n", 15);

		}else if(strncmp(value,"10", 2) == 0){
								
			strncat(asm_code->asm_main_code, "\tcbi PortB, 2\n", 15);
								
		}else if(strncmp(value,"9", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortB, 1\n", 15);

		}else if(strncmp(value,"8", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortB, 0\n", 15);

		}else if(strncmp(value,"7", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortD, 7\n", 15);

		}else if(strncmp(value,"6", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortD, 6\n", 15);

		}else if(strncmp(value,"5", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortD, 5\n", 15);

		}else if(strncmp(value,"4", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortD, 4\n", 15);

		}else if(strncmp(value,"3", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortD, 3\n", 15);

		}else if(strncmp(value,"2", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortD, 2\n", 15);

		}else if(strncmp(value,"1", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortD, 1\n", 15);

		}else if(strncmp(value,"0", 1) == 0){

			strncat(asm_code->asm_main_code, "\tcbi PortD, 0\n", 15);

		}else{
									
			char *err_msg = calloc(1,sizeof(char));

			size_t err_msg_len = 31 + strlen(value);

			snprintf(err_msg, err_msg_len, "Pin %s not present in atmega328p\n", value);

			error *e = new_error(err_msg, t_ast->ast_node_index);

			add_new_error(err_list,e);

		}
								
	}
}

//evaluate output function call
void visitor_evaluate_output_function_call( ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table, symbol_table *parent_symbol_table){

	function_args *first_arg = t_ast->args_list->first_arg;
	function_args *second_arg = t_ast->args_list->last_arg;

	if( strncmp(first_arg->arg_type, "T_IDENTIFIER", 12) == 0 ){

		symbol *s = search_symbol(table, first_arg->arg_name);
		
		symbol *parent_s = NULL;
		
		if( parent_symbol_table != NULL ){

			parent_s = search_symbol(parent_symbol_table, first_arg->arg_name);

		}

		if( s != NULL && parent_s == NULL){

			output_function_code_gen(s->value, second_arg->arg_name, asm_code, err_list, t_ast);

		}else if( parent_s != NULL && s == NULL ){

			output_function_code_gen(parent_s->value, second_arg->arg_name, asm_code, err_list, t_ast);

		}else{

			//variable not present error
	
			size_t err_msg_len = 21 + strlen(first_arg->arg_name);
								
			char *err_msg = calloc(err_msg_len,sizeof(char));

			snprintf(err_msg, err_msg_len, "Symbol %s not declared\n", t_ast->args_list->first_arg->arg_name);

			error *e = new_error(err_msg, t_ast->ast_node_index);

			add_new_error(err_list,e);

		}

	}else if( strncmp(first_arg->arg_type,"T_CONSTANT", 10) == 0 ){

		output_function_code_gen(first_arg->arg_name, second_arg->arg_name, asm_code, err_list, t_ast);

	}else if( strncmp(first_arg->arg_type, "T_KEYWORD", 9) == 0 ){

		if( strncmp(first_arg->arg_name,"serial", 6) == 0 ){

			if( strncmp(second_arg->arg_type, "T_CONSTANT", 10) == 0 ||
				strncmp(second_arg->arg_type, "T_STRING", 8) == 0 ){

				//implement for constant or string value


			}else if( strncmp(second_arg->arg_type, "T_IDENTIFIER", 12) == 0){

				symbol *s = search_symbol(table, second_arg->arg_name);

				//implement symbol search in parent symbol table

				if(s != NULL){

					//implement for identifier


				}else{

					//error


				}


			}


		}else{

			//error

		}
	}
}

//wait function call code generation
void wait_function_code_gen(char *value, code *asm_code, error_list *err_list, ast *t_ast){


	//wait
			
	if(delay_code_flag == 0){
	
		char *reg = use_register(register_list);

		char *delay_counter = use_register(register_list);

		char *temp = use_register(register_list);

		sprintf(asm_code->code_init,  ".def overflow_counter = %s\n"
						 			  ".def delay_count = %s\n\n"
									  ".def temp = %s\n"
									  ".org 0x0000\n"
									  "rjmp reset\n\n"
									  ".org 0x0020\n"
        							  "rjmp overflow_handler\n", reg, delay_counter, temp);

		asm_code->reset_code = "\n\nreset:\n" 
					 "\tldi temp, 0b00000101\n"
					 "\tout TCCR0B, temp				;prescaling to 1024\n"
					 "\tldi temp, 0b00000001\n"
					 "\tsts TIMSK0, temp				;enabling timer interrupt\n"
					 "\tsei								;enabling global interrupt\n";

		asm_code->delay_function = calloc(200, sizeof(char));
					
		asm_code->delay_function = "\n\ndelay:\n"
						 "\tclr overflow_counter\n"
						 "\tsec_count:\n"
						 "\t\tcp overflow_counter, delay_count\n"
						 "\tbrne sec_count\n"
						 "\tret\n";
						
					//timer_overflow_handler = calloc(20, sizeof(char));

		asm_code->timer_overflow_handler = "\n\noverflow_handler:\n"
									     "\tinc overflow_counter\n"
										 "\tcpi overflow_counter, 61\n"
										 "\tbrne PC+2\n"
										 "\tclr overflow_counter\n"
										 "\treti\n";

		delay_code_flag = 1;

	}

	if( isdigit(*value) ){

		int delay_time = atoi(value);
						
		if(delay_time <= 1000){
							
			int calc_delay = (delay_time * 60)/1000;

			char *temp_code = calloc(10, sizeof(char));

			sprintf(temp_code,"\tldi delay_count, %d\n", calc_delay);
			strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));
			free(temp_code);
			strncat(asm_code->asm_main_code,"\trcall delay\n",14);
					
		}else{

			int calc_delay = (delay_time * 60)/1000;
							
			int calc_delay_count =(int)calc_delay/60;

			strncat(asm_code->asm_main_code,"\tldi delay_count, 60\n", 22);
			for(int i = 0;i < calc_delay_count;i++){	
				strncat(asm_code->asm_main_code,"\trcall delay\n", 14);		
			}
	
		}

	}else{

		size_t err_msg_len = 29 + strlen(value);

		char *err_msg = calloc(err_msg_len,sizeof(char));

		snprintf(err_msg, err_msg_len, "%s is not valid wait parameter\n",value);

		error *e = new_error(err_msg, t_ast->ast_node_index);

		add_new_error(err_list,e);

	}

}

//evaluate wait function call
void visitor_evaluate_wait_function_call( ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table, symbol_table *parent_symbol_table){

	function_args *first_arg = t_ast->args_list->first_arg;

	if( strncmp(first_arg->arg_type, "T_CONSTANT", 10) == 0 ){

		wait_function_code_gen(first_arg->arg_name, asm_code, err_list, t_ast);

	}else if( strncmp(first_arg->arg_type, "T_IDENTIFIER", 12) == 0 ){

		symbol *s = search_symbol(table, first_arg->arg_name);

		symbol *parent_s = NULL;
		
		if( parent_symbol_table != NULL ){

			parent_s = search_symbol(parent_symbol_table, first_arg->arg_name);

		}

		if( s != NULL && parent_s == NULL ){

			wait_function_code_gen(s->value, asm_code, err_list, t_ast);

		}else if( parent_s != NULL && s == NULL){

			wait_function_code_gen(parent_s->value, asm_code, err_list, t_ast);

		}else{
		
			size_t err_msg_len = 21 + strlen(first_arg->arg_name);

			char *err_msg = calloc(err_msg_len,sizeof(char));

			snprintf(err_msg, err_msg_len, "Symbol %s not declared\n", first_arg->arg_name);

			error *e = new_error(err_msg, t_ast->ast_node_index);

			add_new_error(err_list,e);
	
		}

	}

}

//evaluate function calls
void visitor_evaluate_function_call(ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table, symbol_table *parent_symbol_table){

	if(is_builtin_function(t_ast->function_name) == 1){

		if(strncmp(t_ast->function_name,"output",6) == 0){

			visitor_evaluate_output_function_call(t_ast, err_list, asm_code, table, parent_symbol_table);

		}else if(strncmp(t_ast->function_name,"wait",4) == 0){

			//wait

			visitor_evaluate_wait_function_call(t_ast, err_list, asm_code, table, parent_symbol_table);

		}else if( strncmp(t_ast->function_name, "input", 6) == 0){

			//input
			visitor_evaluate_input_funtion_call("NA", t_ast, err_list, asm_code, table, parent_symbol_table);

		}

	}//user defined function call

}

//create new code structure
code* new_asm_code(){

	code *c = calloc(1, sizeof(code));
	c->asm_main_code = NULL;
	c->asm_setup_code = NULL;
	c->code_init = NULL;
	c->delay_function = NULL;
	c->reset_code = NULL;
	c->serial_output_function = NULL;
	c->timer_overflow_handler = NULL;
	c->DSEG = NULL;

	c->DSEG_FLAG = 0;

	return c;

}

//evaluate conditional if statements
void visitor_evaluate_conditional_if_statements(ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table){

	token_list *logical_expr = t_ast->conditional_statement_expr;

	//check if true block and false block can be predetermined
	//and only that block of code is generated

	if( is_DSEG(logical_expr, table) == 1 ){

		// cannot be predetermined	
		

	}else{

		//can be predetermined
		char* answer = evaluate_predetermined_logical_expression(t_ast->conditional_statement_expr, err_list, table, t_ast->ast_node_index, NULL);			
		if( answer != NULL ){
			printf("condition ans = %s\n",  answer);

			if( strncmp(answer, "true", 4) == 0 ){

				visitor_evaluate_code_block(t_ast->true_block, err_list, table, asm_code);

			}
		}

	}

}

//evaluate conditional if else statements
void visitor_evaluate_conditional_if_else_statements(ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table){

	token_list *logical_expr = t_ast->conditional_statement_expr;

	//check if true block and false block can be predetermined
	//and only that block of code is generated

	if( is_DSEG(logical_expr, table) == 1 ){

		// cannot be predetermined	
		

	}else{

		//can be predetermined
		char* answer = evaluate_predetermined_logical_expression(t_ast->conditional_statement_expr, err_list, table, t_ast->ast_node_index, NULL);			
		if( answer != NULL ){
			printf("condition ans = %s\n",  answer);

			if( strncmp(answer, "true", 4) == 0 ){

				visitor_evaluate_code_block(t_ast->true_block, err_list, table, asm_code);

			}else{

				visitor_evaluate_code_block(t_ast->false_block, err_list, table, asm_code);

			}

		}

	}

}
//evaluation of block of code
void visitor_evaluate_code_block(ast_l *ast_list, error_list *err_list, symbol_table *parent_symbol_table, code *asm_code){

	symbol_table *table = new_symbol_table();
	symbol *s, *temp_s;
	symbol *parent_table_s = NULL;
	
	ast *t_ast = ast_list->root_node;

	while(t_ast != NULL){

		if( strncmp(t_ast->type, "AST_VAR_DEF_ASSIGNMENT_FUNCTION", 31) == 0){

			temp_s = search_symbol(table, t_ast->var_def_var_name);

			parent_table_s = search_symbol(parent_symbol_table, t_ast->var_def_var_name);

			if( parent_table_s == NULL ){
		
				if(temp_s == NULL){

					char *temp_code = calloc(100, sizeof(char));

					sprintf(temp_code,
							"\t%s: .BYTE 1\n",
							t_ast->var_def_var_name);

					strncat(asm_code->DSEG, temp_code, strlen(temp_code));

					asm_code->DSEG_FLAG = 1;

					add_new_symbol(table, new_var_symbol(t_ast->var_def_var_name,t_ast->var_def_var_name, "DSEG_VAR"));

					visitor_evaluate_input_funtion_call(t_ast->var_def_var_name, t_ast, err_list, asm_code, table, parent_symbol_table);

				}else{

					size_t err_msg_len = strlen(t_ast->var_def_var_name) + ERR_MSG_VAR_PRESENT_LEN;

					char *err_msg = calloc(err_msg_len, sizeof(char));

					snprintf(err_msg, err_msg_len,
							 "variable %s is already declared\n",
							 t_ast->var_def_var_name);

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

		}else if( strncmp(t_ast->type, "AST_VAR_DEF_ASSIGNMENT", 22) == 0){

			temp_s = search_symbol(table, t_ast->var_def_var_name);

			if(parent_symbol_table != NULL){

				parent_table_s = search_symbol(parent_symbol_table, t_ast->var_def_var_name);

			}
			//checking if the give variable name is present or not
			//else raise an error

			if( parent_table_s == NULL){

				if(temp_s == NULL){

					/*                IMPLEMENTING EXPRESSION EVAL                */

					token_list* list = t_ast->var_def_var_expr;

					int FLAG = 0;
					int *STRING_FLAG = &FLAG;

					if( is_DSEG(list, table) == 1 ){

						/******************************************/
						/*     ADD VARIABLE NOT PRESENT ERROR	  */
						/******************************************/

						char *temp_expr = calloc(100, sizeof(char));
					
						//check for undeclared variables
					
						if( is_undeclared_var_present(list, table, err_list, t_ast->ast_node_index) == 0 && 
							is_undeclared_var_present(list, parent_symbol_table, err_list, t_ast->ast_node_index) == 0	){

	//					print_token_list(list);

							token_list* infix = postfix_to_infix(list);

							token *t = infix->first_token;

							/****************************/
							/*raise string present error*/
							/****************************/

							strncat(temp_expr, "(", 2);

							while(t != NULL){

								if(strncmp(t->type, "T_IDENTIFIER", 12) == 0){

									strncat(temp_expr,"$",2 );

								}

								strncat(temp_expr, t->content, strlen(t->content));

								t = t->next_token;

							}

							strncat(temp_expr, ")", 2);

							char *temp_reg = use_register(register_list);

							char *temp_code = calloc(100, sizeof(char));
					
							//declaring variable in asm
							sprintf(temp_code,
									"\t%s: .BYTE 1\n",
									t_ast->var_def_var_name);

							strncat(asm_code->DSEG, temp_code, strlen(temp_code));

							asm_code->DSEG_FLAG = 1;

							//defining variable
							free(temp_code);

							temp_code = calloc(100, sizeof(char));

							sprintf(temp_code, 
									"\tldi %s, %s\n"
									"\tsts %s, %s\n",
									temp_reg, temp_expr, t_ast->var_def_var_name, temp_reg);

							strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));

							//updating symbol table
							symbol *s = new_var_symbol( t_ast->var_def_var_name,
														t_ast->var_def_var_name,
														"DSEG_VAR");

							add_new_symbol(table, s);
	
							free(temp_expr);
							free(temp_code);

					
						}

					}else{

//						printf("******************TOKEN LIST*******************\n");
//						print_token_list(list);
//						printf("\n");

						char* answer = evaluate_expression_ast(list, err_list, table, t_ast->ast_node_index, STRING_FLAG, parent_symbol_table);

						if(answer != NULL){

							printf("ans = %s \n",  answer);

							if(*STRING_FLAG == 0){
	
								char *temp_code = calloc(100, sizeof(char));
					
								//declaring variable in asm
								sprintf(temp_code,
										"\t%s: .BYTE 1\n",
										t_ast->var_def_var_name);

								strncat(asm_code->DSEG, temp_code, strlen(temp_code));

								asm_code->DSEG_FLAG = 1;

								//defining variable in asm
						
								free(temp_code);
	
								temp_code = calloc(100, sizeof(char));

								char *temp_reg = use_register(register_list);

								sprintf(temp_code,
										"\tldi %s, %s\n"
										"\tsts %s, %s\n",
										temp_reg, answer, t_ast->var_def_var_name, temp_reg);

								strncat(asm_code->asm_main_code,temp_code, strlen(temp_code));
				
								//reuse the same register for another operation
								register_index--;

								free(temp_code);

								s = new_var_symbol( t_ast->var_def_var_name,
													answer,
													"T_IDENTIFIER");

							}else{
					
								s = new_var_symbol( t_ast->var_def_var_name,
													answer,
													"T_STRING");
				
							}

							add_new_symbol(table, s);
					
						}
	
					}
				}else{

					size_t err_msg_len = strlen(t_ast->var_def_var_name) + ERR_MSG_VAR_PRESENT_LEN;

					char *err_msg = calloc(err_msg_len, sizeof(char));

					snprintf(err_msg, err_msg_len,
							 "variable %s is already declared\n",
							 t_ast->var_def_var_name);

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
			
		}else if( strncmp(t_ast->type, "AST_VAR_DEF", 11) == 0 ){

			temp_s = search_symbol(table, t_ast->var_def_var_name);

			parent_table_s = search_symbol(parent_symbol_table, t_ast->var_def_var_name);

			//checking if the give variable name is present or not
			//else raise an error

			if(parent_table_s == NULL){

				if(temp_s == NULL){

					/*                IMPLEMENTING EXPRESSION EVAL                */

					char *temp_code = calloc(100, sizeof(char));
					
					//declaring variable in asm
					sprintf(temp_code,
							"\t%s: .BYTE 1\n",
							t_ast->var_def_var_name);

					strncat(asm_code->DSEG, temp_code, strlen(temp_code));

					asm_code->DSEG_FLAG = 1;

					s = new_var_symbol( t_ast->var_def_var_name,
										"NA",
										"NA");
				
					add_new_symbol(table, s);

				}else{

					size_t err_msg_len = strlen(t_ast->var_def_var_name) + ERR_MSG_VAR_PRESENT_LEN;

					char *err_msg = calloc(err_msg_len, sizeof(char));

					snprintf(err_msg, err_msg_len,
							 "variable %s is already declared\n",
							 t_ast->var_def_var_name);

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
		
		}else if( strncmp(t_ast->type, "AST_VAR_ASSIGNMENT_FUNCTION", 28) == 0 ){

			temp_s = search_symbol(table, t_ast->var_name);

			parent_table_s = search_symbol(parent_symbol_table, t_ast->var_def_var_name);

			if(parent_table_s != NULL && temp_s == NULL){
		
				char *temp_code = calloc(100, sizeof(char));

				sprintf(temp_code,
						"\t%s: .BYTE 1\n",
						t_ast->var_name);

				strncat(asm_code->DSEG, temp_code, strlen(temp_code));

				asm_code->DSEG_FLAG = 1;

				update_symbol(parent_symbol_table, new_var_symbol(t_ast->var_name, t_ast->var_name, "DSEG_VAR"));

				visitor_evaluate_input_funtion_call(t_ast->var_name, t_ast, err_list, asm_code, table, NULL);
		
			}else if( temp_s != NULL && parent_table_s == NULL){

				char *temp_code = calloc(100, sizeof(char));

				sprintf(temp_code,
						"\t%s: .BYTE 1\n",
						t_ast->var_name);

				strncat(asm_code->DSEG, temp_code, strlen(temp_code));

				asm_code->DSEG_FLAG = 1;

				update_symbol(table, new_var_symbol(t_ast->var_name, t_ast->var_name, "DSEG_VAR"));

				visitor_evaluate_input_funtion_call(t_ast->var_name, t_ast, err_list, asm_code, table, parent_symbol_table);
			
			}else{

				size_t err_msg_len = strlen(t_ast->var_name) + ERR_MSG_VAR_NOT_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is not declared\n",
						 t_ast->var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}


		}else if( strncmp(t_ast->type, "AST_VAR_ASSIGNMENT", 18) == 0){

			temp_s = search_symbol(table, t_ast->var_name);

			if(parent_symbol_table != NULL){

				parent_table_s = search_symbol(parent_symbol_table, t_ast->var_name);

			}

			//checking if the give variable name is present or not
			//else raise an error

			if(temp_s != NULL && parent_table_s == NULL){

				/*                IMPLEMENTING EXPRESSION EVAL                */

				token_list* list = t_ast->var_expr;

				int FLAG = 0;
				int *STRING_FLAG = &FLAG;

				if( is_DSEG(list, parent_symbol_table) == 1 || is_DSEG(list, table) == 1 ){

					/******************************************/
					/*     ADD VARIABLE NOT PRESENT ERROR	  */
					/******************************************/

					if( is_undeclared_var_present(list, table, err_list, t_ast->ast_node_index) == 0 ){
		
						char *temp_expr = calloc(100, sizeof(char));

	//					print_token_list(list);

						token_list* infix = postfix_to_infix(list);
						token *t = infix->first_token;

						/****************************/
						/*raise string present error*/
						/****************************/

						strncat(temp_expr, "(", 2);

						while(t != NULL){

							if(strncmp(t->type, "T_IDENTIFIER", 12) == 0){

								strncat(temp_expr,"$",2 );

							}
						
							strncat(temp_expr, t->content, strlen(t->content));

							t = t->next_token;

						}

						strncat(temp_expr, ")", 2);

						char *temp_reg = use_register(register_list);

						char *temp_code = calloc(100, sizeof(char));
					
						//defining variable
						free(temp_code);

						temp_code = calloc(100, sizeof(char));

						sprintf(temp_code, 
								"\tldi %s, %s\n"
								"\tsts %s, %s\n",
								temp_reg, temp_expr, t_ast->var_name, temp_reg);

						//reuse register for other operations
						register_index--;

						strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));

						//updating symbol table
						symbol *s = new_var_symbol( t_ast->var_name,
													t_ast->var_name,
													"DSEG_VAR");
	
						update_symbol(table, s);
	
						free(temp_expr);
						free(temp_code);

					}

				}else{

					char* answer = evaluate_expression_ast(list, err_list, table, t_ast->ast_node_index, STRING_FLAG, parent_symbol_table);

					if(answer != NULL){

						printf("ans = %s \n",  answer);

						if(*STRING_FLAG == 0){

							//number
							
							char *temp_code = calloc(100, sizeof(char));

							char *temp_reg = use_register(register_list);

							sprintf(temp_code, 
									"\tldi %s, %s\n"
									"\tsts %s, %s\n",
									temp_reg, answer, t_ast->var_name, temp_reg);

							//reusing the register for other operations
							register_index--;

							strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));

							free(temp_code);

							//updating the symbol table
							temp_s->value = answer;

							update_symbol( 	table,
										 	temp_s);


						}else{
					
							//string
							temp_s->value = answer;
	
							update_symbol( 	table,
										 	temp_s);

						}

					}

				}
			}else if( parent_table_s != NULL  && temp_s == NULL ){

				/*                IMPLEMENTING EXPRESSION EVAL                */

				token_list* list = t_ast->var_expr;

				int FLAG = 0;
				int *STRING_FLAG = &FLAG;

				if( is_DSEG(list, parent_symbol_table) == 1 || is_DSEG(list, table) == 1 ){

					/******************************************/
					/*     ADD VARIABLE NOT PRESENT ERROR	  */
					/******************************************/

					if( is_undeclared_var_present(list, parent_symbol_table, err_list, t_ast->ast_node_index) == 0 && 
						is_undeclared_var_present(list, table, err_list, t_ast->ast_node_index) == 0 ){
		
						char *temp_expr = calloc(100, sizeof(char));

	//					print_token_list(list);

						token_list* infix = postfix_to_infix(list);
						token *t = infix->first_token;

						/****************************/
						/*raise string present error*/
						/****************************/

						strncat(temp_expr, "(", 2);

						while(t != NULL){

							if(strncmp(t->type, "T_IDENTIFIER", 12) == 0){

								strncat(temp_expr,"$",2 );

							}
						
							strncat(temp_expr, t->content, strlen(t->content));

							t = t->next_token;

						}

						strncat(temp_expr, ")", 2);

						char *temp_reg = use_register(register_list);

						char *temp_code = calloc(100, sizeof(char));
					
						//defining variable
						free(temp_code);

						temp_code = calloc(100, sizeof(char));

						sprintf(temp_code, 
								"\tldi %s, %s\n"
								"\tsts %s, %s\n",
								temp_reg, temp_expr, t_ast->var_name, temp_reg);

						//reuse register for other operations
						register_index--;

						strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));

						//updating symbol table
						symbol *s = new_var_symbol( t_ast->var_name,
													t_ast->var_name,
													"DSEG_VAR");
	
						update_symbol(parent_symbol_table, s);
	
						free(temp_expr);
						free(temp_code);

					}

				}else{

					char* answer = evaluate_expression_ast(list, err_list, table, t_ast->ast_node_index, STRING_FLAG, parent_symbol_table);

					if(answer != NULL){

						printf("ans = %s \n",  answer);

						if(*STRING_FLAG == 0){

							//number
							
							char *temp_code = calloc(100, sizeof(char));

							char *temp_reg = use_register(register_list);

							sprintf(temp_code, 
									"\tldi %s, %s\n"
									"\tsts %s, %s\n",
									temp_reg, answer, t_ast->var_name, temp_reg);

							//reusing the register for other operations
							register_index--;

							strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));

							free(temp_code);

							//updating the symbol table
							parent_table_s->value = answer;

							update_symbol( 	parent_symbol_table,
										 	parent_table_s);


						}else{
					
							//string
							temp_s->value = answer;
	
							update_symbol( 	parent_symbol_table,
										 	temp_s);

						}

					}

				}
			}else{

				size_t err_msg_len = strlen(t_ast->var_name) + ERR_MSG_VAR_NOT_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is not declared\n",
						 t_ast->var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}

		}else if( strncmp(t_ast->type,"AST_BUILTIN_FUNCTION_CALL",26) == 0 ){

			visitor_evaluate_function_call(t_ast, err_list, asm_code, table, parent_symbol_table);			

		}else if( strncmp(t_ast->type, "AST_CONDITIONAL_IF", 18) == 0 ){

			visitor_evaluate_conditional_if_statements(t_ast, err_list, asm_code, table);

		}else if( strncmp(t_ast->type, "AST_CONDITIONAL_IF_ELSE", 23) == 0 ){

			visitor_evaluate_conditional_if_else_statements(t_ast, err_list, asm_code, table);

		}//other asts

		t_ast = t_ast->next_ast_node;

	}
	
	free(table);

}

//visitor
void visitor_evaluate(ast_l *ast_list, error_list* err_list){

	symbol_table *table = new_symbol_table();

	symbol *s, *temp_s;

	ast *t_ast = ast_list->root_node;

	code *asm_code = new_asm_code();

	asm_code->code_init = calloc(200, sizeof(char));
	asm_code->asm_setup_code = calloc(1000, sizeof(char));
	asm_code->asm_main_code = calloc(2000, sizeof(char));
	asm_code->reset_code = calloc(200, sizeof(char));
	asm_code->delay_function = NULL;
	asm_code->timer_overflow_handler = calloc(200, sizeof(char));
	asm_code->serial_output_function = NULL;
	asm_code->DSEG = calloc(300 , sizeof(char));

	while(t_ast != NULL){

		if( strncmp(t_ast->type, "AST_VAR_DEF_ASSIGNMENT_FUNCTION", 31) == 0){

			temp_s = search_symbol(table, t_ast->var_def_var_name);

			if(temp_s == NULL){

				char *temp_code = calloc(100, sizeof(char));

				sprintf(temp_code,
						"\t%s: .BYTE 1\n",
						t_ast->var_def_var_name);

				strncat(asm_code->DSEG, temp_code, strlen(temp_code));

				asm_code->DSEG_FLAG = 1;

				add_new_symbol(table, new_var_symbol(t_ast->var_def_var_name,t_ast->var_def_var_name, "DSEG_VAR"));

				visitor_evaluate_input_funtion_call(t_ast->var_def_var_name, t_ast, err_list, asm_code, table, NULL);

			}else{

				size_t err_msg_len = strlen(t_ast->var_def_var_name) + ERR_MSG_VAR_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is already declared\n",
						 t_ast->var_def_var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}

		}else if( strncmp(t_ast->type, "AST_VAR_DEF_ASSIGNMENT", 22) == 0){

			temp_s = search_symbol(table, t_ast->var_def_var_name);

			//checking if the give variable name is present or not
			//else raise an error

			if(temp_s == NULL){

				/*                IMPLEMENTING EXPRESSION EVAL                */

				token_list* list = t_ast->var_def_var_expr;

				int FLAG = 0;
				int *STRING_FLAG = &FLAG;

				if( is_DSEG(list, table) == 1 ){

					/******************************************/
					/*     ADD VARIABLE NOT PRESENT ERROR	  */
					/******************************************/

					char *temp_expr = calloc(100, sizeof(char));
					
					//check for undeclared variables
					
					if( is_undeclared_var_present(list, table, err_list, t_ast->ast_node_index) == 0 ){

	//					print_token_list(list);

						token_list* infix = postfix_to_infix(list);

						token *t = infix->first_token;

						/****************************/
						/*raise string present error*/
						/****************************/

						strncat(temp_expr, "(", 2);

						while(t != NULL){

							if(strncmp(t->type, "T_IDENTIFIER", 12) == 0){

								strncat(temp_expr,"$",2 );

							}

							strncat(temp_expr, t->content, strlen(t->content));

							t = t->next_token;

						}

						strncat(temp_expr, ")", 2);

						char *temp_reg = use_register(register_list);

						char *temp_code = calloc(100, sizeof(char));
					
						//declaring variable in asm
						sprintf(temp_code,
								"\t%s: .BYTE 1\n",
								t_ast->var_def_var_name);

						strncat(asm_code->DSEG, temp_code, strlen(temp_code));

						asm_code->DSEG_FLAG = 1;

						//defining variable
						free(temp_code);

						temp_code = calloc(100, sizeof(char));

						sprintf(temp_code, 
								"\tldi %s, %s\n"
								"\tsts %s, %s\n",
								temp_reg, temp_expr, t_ast->var_def_var_name, temp_reg);

						strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));

						//updating symbol table
						symbol *s = new_var_symbol( t_ast->var_def_var_name,
													t_ast->var_def_var_name,
													"DSEG_VAR");

						add_new_symbol(table, s);
	
						free(temp_expr);
						free(temp_code);

					
					}

				}else{

//					printf("******************TOKEN LIST*******************\n");
//					print_token_list(list);
//					printf("\n");

					char* answer = evaluate_expression_ast(list, err_list, table, t_ast->ast_node_index, STRING_FLAG, NULL);

					if(answer != NULL){

						printf("ans = %s \n",  answer);

						if(*STRING_FLAG == 0){

							char *temp_code = calloc(100, sizeof(char));
					
							//declaring variable in asm
							sprintf(temp_code,
									"\t%s: .BYTE 1\n",
									t_ast->var_def_var_name);

							strncat(asm_code->DSEG, temp_code, strlen(temp_code));

							asm_code->DSEG_FLAG = 1;

							//defining variable in asm
						
							free(temp_code);
	
							temp_code = calloc(100, sizeof(char));

							char *temp_reg = use_register(register_list);

							sprintf(temp_code,
									"\tldi %s, %s\n"
									"\tsts %s, %s\n",
									temp_reg, answer, t_ast->var_def_var_name, temp_reg);

							strncat(asm_code->asm_main_code,temp_code, strlen(temp_code));
				
							//reuse the same register for another operation
							register_index--;

							free(temp_code);

							s = new_var_symbol( t_ast->var_def_var_name,
												answer,
												"T_IDENTIFIER");

						}else{
					
							s = new_var_symbol( t_ast->var_def_var_name,
												answer,
												"T_STRING");
				
						}

						add_new_symbol(table, s);
					
					}

				}
			}else{

				size_t err_msg_len = strlen(t_ast->var_def_var_name) + ERR_MSG_VAR_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is already declared\n",
						 t_ast->var_def_var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}
			
		}else if( strncmp(t_ast->type, "AST_VAR_DEF", 11) == 0 ){

			temp_s = search_symbol(table, t_ast->var_def_var_name);

			//checking if the give variable name is present or not
			//else raise an error

			if(temp_s == NULL){

				/*                IMPLEMENTING EXPRESSION EVAL                */

				char *temp_code = calloc(100, sizeof(char));
					
				//declaring variable in asm
				sprintf(temp_code,
						"\t%s: .BYTE 1\n",
						t_ast->var_def_var_name);

				strncat(asm_code->DSEG, temp_code, strlen(temp_code));

				asm_code->DSEG_FLAG = 1;

				s = new_var_symbol( t_ast->var_def_var_name,
									"NA",
									"NA");
				
				add_new_symbol(table, s);

			}else{

				size_t err_msg_len = strlen(t_ast->var_def_var_name) + ERR_MSG_VAR_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is already declared\n",
						 t_ast->var_def_var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}
		
		}else if( strncmp(t_ast->type, "AST_VAR_ASSIGNMENT_FUNCTION", 28) == 0 ){

			temp_s = search_symbol(table, t_ast->var_name);

			if( temp_s != NULL ){

				char *temp_code = calloc(100, sizeof(char));

				sprintf(temp_code,
						"\t%s: .BYTE 1\n",
						t_ast->var_name);

				strncat(asm_code->DSEG, temp_code, strlen(temp_code));

				asm_code->DSEG_FLAG = 1;

				update_symbol(table, new_var_symbol(t_ast->var_name, t_ast->var_name, "DSEG_VAR"));

				visitor_evaluate_input_funtion_call(t_ast->var_name, t_ast, err_list, asm_code, table, NULL);
			
			}else{

				size_t err_msg_len = strlen(t_ast->var_name) + ERR_MSG_VAR_NOT_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is not declared\n",
						 t_ast->var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}


		}else if( strncmp(t_ast->type, "AST_VAR_ASSIGNMENT", 18) == 0){

			temp_s = search_symbol(table, t_ast->var_name);

			//checking if the give variable name is present or not
			//else raise an error

			if(temp_s != NULL){

				/*                IMPLEMENTING EXPRESSION EVAL                */

				token_list* list = t_ast->var_expr;

				int FLAG = 0;
				int *STRING_FLAG = &FLAG;

				if( is_DSEG(list, table) == 1 ){

					/******************************************/
					/*     ADD VARIABLE NOT PRESENT ERROR	  */
					/******************************************/

					if( is_undeclared_var_present(list, table, err_list, t_ast->ast_node_index) == 0 ){
		
						char *temp_expr = calloc(100, sizeof(char));

	//					print_token_list(list);

						token_list* infix = postfix_to_infix(list);
						token *t = infix->first_token;

						/****************************/
						/*raise string present error*/
						/****************************/

						strncat(temp_expr, "(", 2);

						while(t != NULL){

							if(strncmp(t->type, "T_IDENTIFIER", 12) == 0){

								strncat(temp_expr,"$",2 );

							}
						
							strncat(temp_expr, t->content, strlen(t->content));

							t = t->next_token;

						}

						strncat(temp_expr, ")", 2);

						char *temp_reg = use_register(register_list);

						char *temp_code = calloc(100, sizeof(char));
					
						//defining variable
						free(temp_code);

						temp_code = calloc(100, sizeof(char));

						sprintf(temp_code, 
								"\tldi %s, %s\n"
								"\tsts %s, %s\n",
								temp_reg, temp_expr, t_ast->var_name, temp_reg);

						//reuse register for other operations
						register_index--;

						strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));

						//updating symbol table
						symbol *s = new_var_symbol( t_ast->var_name,
													t_ast->var_name,
													"DSEG_VAR");
	
						update_symbol(table, s);
	
						free(temp_expr);
						free(temp_code);

					}

				}else{

					char* answer = evaluate_expression_ast(list, err_list, table, t_ast->ast_node_index, STRING_FLAG, NULL);

					if(answer != NULL){

						printf("ans = %s \n",  answer);

						if(*STRING_FLAG == 0){

							//number
							
							char *temp_code = calloc(100, sizeof(char));

							char *temp_reg = use_register(register_list);

							sprintf(temp_code, 
									"\tldi %s, %s\n"
									"\tsts %s, %s\n",
									temp_reg, answer, t_ast->var_name, temp_reg);

							//reusing the register for other operations
							register_index--;

							strncat(asm_code->asm_main_code, temp_code, strlen(temp_code));

							free(temp_code);

							//updating the symbol table
							temp_s->value = answer;

							update_symbol( 	table,
										 	temp_s);


						}else{
					
							//string
							temp_s->value = answer;
	
							update_symbol( 	table,
										 	temp_s);

						}

					}

				}
			}else{

				size_t err_msg_len = strlen(t_ast->var_name) + ERR_MSG_VAR_NOT_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is not declared\n",
						 t_ast->var_name);

				add_new_error(err_list, new_error(err_msg, t_ast->ast_node_index));

			}

		}else if( strncmp(t_ast->type,"AST_BUILTIN_FUNCTION_CALL",26) == 0 ){

			visitor_evaluate_function_call(t_ast, err_list, asm_code, table, NULL);			

		}else if( strncmp(t_ast->type, "AST_CONDITIONAL_IF", 18) == 0 ){

			visitor_evaluate_conditional_if_statements(t_ast, err_list, asm_code, table);

		}else if( strncmp(t_ast->type, "AST_CONDITIONAL_IF_ELSE", 23) == 0 ){

			visitor_evaluate_conditional_if_statements(t_ast, err_list, asm_code, table);

		}//other asts

		t_ast = t_ast->next_ast_node;

	}

	if(err_list->error_index > 0){
		print_errors(err_list);
		exit(0);
	}else{

		//printing symbol table for drbugging process only
		fprintf(stdout, "\n SYMBOL TABLE \n");
		print_symbol_table(table);

		FILE *f = fopen("./code.asm","w+");

		fprintf(f,";**************************************************\n"
				  ";*                                                *\n"
				  ";*     THIS IS CODE GENERATED AUTOMATICALLY       *\n"
				  ";*                 BY COMPILER                    *\n"
				  ";*                                                *\n"
				  ";**************************************************\n\n\n");

		fprintf(f,".include \"./m328Pdef.inc\"\n\n\n");

		if(asm_code->DSEG_FLAG == 1){

			fprintf(f,
					";************************************\n"
					";*             variables            *\n"
					";************************************\n\n");
			fprintf(f, ".DSEG\n");
			fprintf(f, "%s", asm_code->DSEG);
			fprintf(f, ".CSEG\n\n\n");

		}

		if(asm_code->delay_function != NULL){
			fprintf(f,"%s", asm_code->code_init);
			fprintf(f,"%s", asm_code->reset_code);
		}

		fprintf(f,"\nsetup:\n");

		fprintf(f,"%s", asm_code->asm_setup_code);

		fprintf(f,"\n\n");

		fprintf(f, "main:\n");

		fprintf(f, "%s", asm_code->asm_main_code);

		fprintf(f,"\n\nend:\n");

		fprintf(f, "\trjmp end\n");
 
		if(asm_code->delay_function != NULL){
			fprintf(f,"%s",asm_code->delay_function);
			fprintf(f,"%s", asm_code->timer_overflow_handler);
		}

		fclose(f);

		free(asm_code->asm_setup_code);

		free(asm_code->asm_main_code);

		free(asm_code->code_init);
		
		//free(reset_code);

		//free(timer_overflow_handler);


	//		free(delay_function);

	}

}


