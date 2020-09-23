#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "compiler.h"

//visitor
void visitor_evaluate(ast_l *ast_list, error_list *err_list);

#endif
