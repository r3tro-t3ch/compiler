#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>

typedef struct SYMBOL{
	
	struct SYMBOL *next_symbol;

	char *name;
	char *type; // var or function

	//var
	char *value;
	char *data_type;

	//funtion
	size_t arg_count;
	char **args;
	char *return_type;

} symbol;

typedef struct SYMBOL_TABLE{

	size_t table_index;
	symbol *first_symbol;
	symbol *last_symbol;

} symbol_table;

//new symbol table
symbol_table* new_symbol_table();

//new var symbol
symbol* new_var_symbol(char *var_name, char *value, char *data_type);

//add new symbol
void add_new_symbol(symbol_table *table, symbol *s);

//print all symbol
void print_symbol_table(symbol_table *table);

//search symbol
symbol* search_symbol(symbol_table *table, char *s);

//update symbols on symbol table
int update_symbol(symbol_table *table, symbol *s );

#endif
