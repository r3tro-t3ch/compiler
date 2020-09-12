#include "error.h"
#include "symbol_table.h"
#include "compiler.h" 

#include <stdio.h>


//semantic analyzer
//void run_semantic_analysis(ast_l *ast_list, error_list *err_list, symbol_table *table){

/*
//var def assignment
	symbol *search;

	if(table->first_symbol != NULL){

		search = search_symbol(table, a->var_def_var_name);

		if(search != NULL){

			size_t err_msg_len = ERR_MSG_VAR_PRESENT_LEN + strlen(a->var_def_var_name);

			char *err_msg = calloc(1, err_msg_len);

			snprintf( err_msg, err_msg_len,
					"var %s cannot be declared again\n"	,
					a->var_def_var_name
					);

			error* e = new_error(err_msg, ast_list->line_count);

			add_new_error(err_list, e);

			return NULL;

		}

	}


	symbol *s = new_var_symbol( a->var_def_var_name,
									a->var_def_var_content,
									"T_CONSTANT");

		
		add_new_symbol(table, s);



*/
/*

var assignment
symbol *s = search_symbol(table, get_current_token(p)->content);

	if(s == 0){

		size_t err_msg_len = ERR_MSG_VAR_NOT_PRESENT_LEN + strlen(get_current_token(p)->content);

		char *err_msg = calloc(1, err_msg_len);

		snprintf( err_msg, err_msg_len,
				"var %s is not declared\n"	,
				get_current_token(p)->content
				);

		error* e = new_error(err_msg, ast_list->line_count);

		add_new_error(err_list, e);

		return NULL;

	}

s = search_symbol(table, get_current_token(p)->content);

		if(s == 0){

			size_t err_msg_len = ERR_MSG_VAR_NOT_PRESENT_LEN + strlen(get_current_token(p)->content);

			char *err_msg = calloc(1, err_msg_len);

			snprintf( err_msg, err_msg_len,
					"var %s is not declared\n"	,
					get_current_token(p)->content
					);

			error* e = new_error(err_msg, ast_list->line_count);

			add_new_error(err_list, e);

			return NULL;

		}

		node->var_content = s->value;

symbol *new_s = new_var_symbol(node->var_name, node->var_content,"T_CONSTANT");

	if(update_symbol(table, new_s) == 0){
	
		return NULL;

	}


*/

//}
