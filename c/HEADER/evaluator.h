#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "compiler.h"

#define GENERAL_PURPOSE_REGISTER_COUNT 16

//registers
char* use_register(char *register_list[]);

//calculate delay
size_t calculate_delay(size_t delay_parameter);

//visitor
void visitor_evaluate(ast_l *ast_list, error_list *err_list);

#endif
