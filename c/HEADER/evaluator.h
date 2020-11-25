#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "compiler.h"
#include "symbol_table.h"

#define GENERAL_PURPOSE_REGISTER_COUNT 16

//registers
char* use_register(char *register_list[]);

//calculate delay
size_t calculate_delay(size_t delay_parameter);

typedef struct CODE{

	char *code_init;
	char *asm_setup_code;
	char *asm_main_code;
	char *reset_code;
	char *delay_function;
	char *timer_overflow_handler;
	char *serial_output_function;
	char *DSEG;


	//flags
	int DSEG_FLAG;

} code;

//create new code structure
code* new_asm_code();

//input function call code generation
void input_function_code_gen(char *reg,char *first_arg, code *asm_code, error_list *err_list, ast *t_ast);

//evaluate input function call
void visitor_evaluate_input_funtion_call(char *reg, ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table, symbol_table *parent_symbol_table);

//evaluate output function call
void visitor_evaluate_output_function_call( ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table, symbol_table *parent_symbol_table);

//output function call code generation
void output_function_code_gen(char *value,char *second_arg, code *asm_code, error_list *err_list, ast *t_ast);

//evaluate wait function call
void visitor_evaluate_wait_function_call( ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table, symbol_table *parent_symbol_table);

//wait function call code generation
void wait_function_code_gen(char *value, code *asm_code, error_list *err_list, ast *t_ast);

//evaluate function calls
void visitor_evaluate_function_call(ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table, symbol_table *parent_symbol_table);

//evaluate conditional if statements
void visitor_evaluate_conditional_if_statements(ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table);

//evaluate conditional if else statements
void visitor_evaluate_conditional_if_else_statements(ast *t_ast, error_list *err_list, code *asm_code, symbol_table *table);

//evaluation of block of code
void visitor_evaluate_code_block(ast_l *ast_list, error_list *err_list, symbol_table *parent_symbol_table,code *asm_code);

//visitor
void visitor_evaluate(ast_l *ast_list, error_list *err_list);

#endif
