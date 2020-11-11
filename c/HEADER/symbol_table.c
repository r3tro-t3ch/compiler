#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"

//new symbol table
symbol_table* new_symbol_table(){

	symbol_table *st = calloc(1, sizeof(symbol_table));
	st->table_index = 0;
	st->first_symbol = NULL;
	st->last_symbol = NULL;
	return st;

}

//new var symbol
symbol* new_var_symbol(char *var_name, char *value, char *data_type){

	symbol *var = calloc(1, sizeof(symbol));

	var->next_symbol = NULL;

	var->name = var_name;
	var->type = "S_VARIABLE"; // var or function

	//var
	var->value = value;

	if( strncmp(data_type, "T_STRING",8 ) == 0){

		var->data_type = "STRING";

	}else if( strncmp(data_type, "DSEG_VAR", 8) == 0 ){

		var->data_type = "DSEG_VAR";

	}else if( strncmp(data_type, "NA", 8) == 0){

		var->data_type = "NA";

	}else{

		var->data_type = "NUMBER";

	}
	

	//funtion
	var->arg_count = 0;
	var->args  = NULL;
	var->return_type = NULL;

	return var;

}

//add new symbol
void add_new_symbol(symbol_table *table, symbol *s){

	if(table->table_index == 0){

		table->first_symbol = s;
		table->last_symbol = s;
		table->table_index++;

	}else{

		table->last_symbol->next_symbol = s;
		table->last_symbol = s;
		table->table_index++;

	}

}

//print all symbol
void print_symbol_table(symbol_table *table){

	if(table == NULL){
		fprintf(stdout,"table null\n");
	}

	symbol *s = table->first_symbol;

	while(s != NULL){

		fprintf(stdout, "NAME: %s ,TYPE: %s , VALUE: %s, DATA_TYPE: %s\n",
					s->name,
					s->type,
					s->value,
					s->data_type
		);
		s = s->next_symbol;
	}

}

//search symbol
symbol* search_symbol(symbol_table *table, char *name){

	int search_flag = false;
	
	size_t len = strlen(name);

	symbol *temp = table->first_symbol;

	symbol *ret_symbol = calloc(1, sizeof(symbol));

	while(temp != NULL){

		if(strncmp(temp->name, name, len) == 0){

			ret_symbol->name = temp->name;
			ret_symbol->type = temp->type;
			ret_symbol->value = temp->value;
			ret_symbol->data_type = temp->data_type;
			search_flag = true;
			break;

		}

		temp = temp->next_symbol;
	}

	if(search_flag == true){

		return ret_symbol;

	}


	return NULL; 

}

//update symbols on symbol table
int update_symbol(symbol_table *table, symbol *s){

	if(table->first_symbol == NULL){

		return 0;

	}

	size_t len = strlen(s->name);

	symbol *temp = table->first_symbol;

	if(strncmp(temp->name, s->name, len) == 0){

		temp->name = s->name;
		temp->type = s->type;
		temp->value = s->value;
		temp->data_type = s->data_type;
		return 1;

	}

	while(temp->next_symbol != NULL){

		temp = temp->next_symbol;

		if(strncmp(temp->name, s->name, len) == 0){

			temp->name = s->name;
			temp->type = s->type;
			temp->value = s->value;
			temp->data_type = s->data_type;
			return 1;

		}

	}

	return 0;

}
