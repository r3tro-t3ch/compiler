public class Main{

	public static void main( String args[] ){

		lexer l = new lexer(
			"var led = 1  \n" +  
			"var l = led\n" +
			"var a\n" +
			"a = l\n" +
			"output(LED, HIGH)\n" +
			"wait(1)\n" +
			"output(LED, HIGH)\n" +
			"wait(1)\n" +
			'\0');		
		
		parser p = new parser(l);


		errors err_list = new errors();

		ast_l ast_list = new ast_l();

		p.get_next_token();

		while( !p.get_current_token().get_type().equals("T_NULL") ){

			if( p.get_current_token().get_type().equals("T_KEYWORD") ){

				if( p.get_current_token().get_content().equals("var")){

					ast node = p.parse_var_def(err_list, ast_list);

					if(node != null){

						ast_list.add_new_ast(node);

					}

				}

			}else if( p.get_current_token().get_type().equals("T_IDENTIFIER") ){

				token t = p.peek_next_token();

				if( t.get_type().equals("T_EQUAL") ){

					ast node = p.parse_var_assignment(err_list, ast_list);

					if(node != null){

						ast_list.add_new_ast(node);

					}

				}else if( t.get_type().equals("T_LPAREN") ){

					ast node = p.parse_function_call(err_list, ast_list);

					if(node != null){

						ast_list.add_new_ast(node);

					}

				}else{
					p.parse_newline(err_list, ast_list);
				}

			}

			if( p.get_current_token().get_type().equals("T_NULL") ){
				break;
			}

			if( p.get_current_token().get_type().equals("T_NEWLINE" )){

				p.parse_newline(err_list, ast_list);

			}
			
			p.get_next_token();
		
		}

		if(err_list.get_errors_count() > 0){

			err_list.print_errors();

		}else{

			ast_list.print_ast();

		}
	}
}

