#include "error.h"
#include <stdlib.h>
#include <stdio.h>


//create new error list
error_list* new_error_list(){

	error_list *err_list = calloc(1,sizeof(error_list));
	err_list->error_index = 0;
	err_list->first_error = NULL;
	err_list->last_error = NULL;
	return err_list;

}

//create new error
error* new_error(char *err_msg, size_t err_line){

	error *err = calloc(1, sizeof(error));
	err->line_number = err_line;
	err->error_msg = err_msg;
	err->next_error = NULL;
	return err;

}

//add new error to array list
void add_new_error(error_list *err_list, error *err){

	if(err_list->error_index == 0){

		err_list->first_error = err;
		err_list->last_error = err;
		err_list->error_index++;

	}else{

		err_list->last_error->next_error = err;
		err_list->last_error = err;
		err_list->error_index++;

	}
}

//print errors
void print_errors(error_list *err_list){

	error *root = err_list->first_error;
	print_error(root);

}

//print single error
void print_error(error *err){

	fprintf(stderr, "ERROR : line %td -> %s \n",
			err->line_number,
			err->error_msg
		);

	while(err->next_error != NULL){

		err = err->next_error;

		fprintf(stderr, "ERROR : line %td -> %s \n",
			err->line_number,
			err->error_msg
		);
	}
}

