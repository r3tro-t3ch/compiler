#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "error.h"
#include "symbol_table.h"
#include "compiler.h" 

//semantic analyzer
void run_semantic_analysis(ast_l *ast_list, error_list *err_list, symbol_table *table);

#endif
