#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>

#define ERR_MSG_LEN 37
#define ERR_MSG_VAR_PRESENT_LEN 30 
#define ERR_MSG_VAR_NOT_PRESENT_LEN 28

typedef struct ERROR{

	char *error_msg;
	size_t line_number;
	struct ERROR *next_error;

} error;

typedef struct ERROR_LIST{

	size_t error_index;
	error *last_error;
	error *first_error;

} error_list;


//create new error list
error_list* new_error_list();

//create new error
error* new_error(char *err_msg, size_t err_line );

//add new error to array list
void add_new_error(error_list *err_list, error *err);

//print errors
void print_errors(error_list *err_list);

//print single error
void print_error(error *err);

#endif
