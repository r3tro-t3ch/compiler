package compiler_class;

import compiler_class.*;
import java.io.*; 
import java.util.*;
import java.lang.*;


public class Main{

	public static void main( String args[] ){

		keywords k = new keywords();
		lexer l = new lexer(
			"var led = (5 + 7 - 4) * 3\n" +  
    	    "loop(true){\n" +
	        "output(led, HIGH)\n" +
        	"output(serial, \"On\")\n" + 
    	    "wait(1)\n" +
	        "output(led, LOW)\n" +
        	"output(serial, \"Off\")\n" +
    	    "wait(1)\n" +
	        "}\0" );		
	
		ArrayList<token> token_array = new ArrayList<token>();

		while( l.get_current_char() != '\0' ){

			if( l.get_current_char() == ' ' || l.get_current_char() == '\n' ){

				l.next_char();

			}
			
			if( l.is_alpha_numeric(l.get_current_char()) ){

				String identifier = l.get_identifier();

				if( k.is_num(identifier) ){
					
					token_array.add(new token("T_CONSTANT", identifier));

				}else if( k.is_keyword(identifier) ){

					token_array.add(new token("T_KEYWORD", identifier));

				}else{
					
					token_array.add(new token("T_IDENTIFIER", identifier));

				}
			
			}
			
			l.next_char();

		}

		for(var token : token_array){
			System.out.println(token.get_type() + " --> " + token.get_content());
		}

	}

}

