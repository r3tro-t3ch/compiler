#include "error.h"
#include <stdlib.h>
#include <stdio.h>


//create new error list
error_list* new_error_list(){

	error_list *err_list = calloc(1,sizeof(error_list));
	err_list->error_index = 0;
	err_list->err_list = NULL;
	return err_list;

}

//create new error
error* new_error(char *err_msg, size_t err_line){

	error *err = calloc(1, sizeof(error));
	err->line_number = err_line;
	err->error_msg = err_msg;
	return err;

}

//add new error to array list
void add_new_error(error_list *err_list, error *err){

	size_t count = err_list->error_index+1;
	err_list->err_list = realloc(err_list->err_list ,
					count * sizeof(error*));
	if(err_list->err_list == NULL){

		fprintf(stdout, "realloc failed");
		exit(1);

	}
	err_list->err_list[err_list->error_index] = err;
	err_list->error_index++;

}

//print errors
void print_errors(error_list *list){

	for(size_t i = 0; i < list->error_index ;i++){
	
		fprintf(stderr, "ERROR : line %td -> %s \n",
			list->err_list[i]->line_number,
			list->err_list[i]->error_msg
		);

	}	

}

