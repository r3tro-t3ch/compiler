#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>

#define ERR_MSG_LEN 27

typedef struct ERROR{

	char *error_msg;
	size_t line_number;

} error;

typedef struct ERROR_LIST{

	size_t error_index;
	error **err_list;

} error_list;


//create new error list
error_list* new_error_list();

//create new error
error* new_error(char *err_msg, size_t err_line );

//add new error to array list
void add_new_error(error_list *err_list, error *err);

//print errors
void print_errors(error_list *err_list);

#endif
