#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "HEADER/compiler.h"


int main(int argc, char *argv[]){

	lexer *l = new_lexer(
		"var led  13\n"
		//"output(led, HIGH)\n"
		"\0" );

	parser *p = new_parser(l);
	ast *root = new_ast("AST_HEAD");

	p->current_token = get_next_token(p); 
	
	token *t = get_current_token(p);

	if( strncmp(p->current_token->type, "T_KEYWORD", 10) == 0){

		parser_eat(t, "T_KEYWORD");

		if( strncmp(t->content, "var", 3) == 0){

			root->next = new_ast("AST_VAR_DEF_ASSIGNMENT");
	
			t = get_next_token(p);
			p->current_token = t; 
			parser_eat(t, "T_IDENTIFIER");
			root->next->var_def_var_name = t->content;
				
			t = get_next_token(p);
			p->current_token = t; 
			fprintf(stdout, "%s", t->type);
			parser_eat(t, "T_EQUAL");
	
			t = get_next_token(p);
			p->current_token = t; 
			parser_eat(t, "T_CONSTANT");
			root->next->var_def_var_content = t->content;
			root->code_size++;

		}
	}

	fprintf(stdout, "%ld, %s", root->code_size, root->type);

	return 0;
}
